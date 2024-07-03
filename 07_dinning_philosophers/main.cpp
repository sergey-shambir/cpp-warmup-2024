#include <chrono>
#include <format>
#include <functional>
#include <iostream>
#include <mutex>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>

#include <signal.h>

using namespace std::chrono;

const auto DINNER_DEADLINE = 2000ms;
const auto TAKE_FORK_DEADLINE = 100ms;

const auto DINNER_MIN_TIME = 200ms;
const auto DINNER_MAX_TIME = 400ms;

const auto THINKING_MIN_TIME = 300ms;
const auto THINKING_MAX_TIME = 500ms;

bool g_stopped = false;

void handleStopSignal(int signal)
{
    g_stopped = true;
    return;
}

class DinningTable
{
public:
    size_t ForkCount() const
    {
        return forks.size();
    }

    bool TryTakeForkFor(size_t index, milliseconds deadline)
    {
        return forks[index].try_lock_for(deadline);
    }

    void FreeFork(size_t index)
    {
        forks[index].unlock();
    }

private:
    std::array<std::timed_mutex, 5> forks;
};

using LoggerFn = std::function<void(std::string_view)>;

class LogStream
{
public:
    explicit LogStream(std::ostream& stream)
        : stream(stream)
    {
    }

    LogStream(const LogStream&) = delete;
    LogStream& operator=(const LogStream&) = delete;

    LoggerFn CreateLogger(std::string name)
    {
        return [this, prefix = name + ": "](std::string_view message) {
            std::string formattedMessage = prefix;
            std::lock_guard g(mutex);
            stream << prefix << message << std::endl;
        };
    }

private:
    std::ostream& stream;
    std::mutex mutex;
};

class Philosopher
{
public:
    explicit Philosopher(DinningTable& table, size_t index)
        : table(table)
        , firstForkIndex(index)
        , secondForkIndex((index + 1) % table.ForkCount())
    {
        if (index % 2)
        {
            std::swap(firstForkIndex, secondForkIndex);
        }
    }

    void StartDinner()
    {
        const auto maxAttempts = DINNER_DEADLINE / (2 * TAKE_FORK_DEADLINE);
        for (auto attemptsLeft = maxAttempts; attemptsLeft > 0; --attemptsLeft)
        {
            if (TryStartDinner())
            {
                return;
            }
        }
        throw std::logic_error(std::format("failed to start dinner with forks {} and {}", firstForkIndex, secondForkIndex));
    }

    // NOTE: In real project, it's better to use RAII (like std::lock_guard)
    bool TryStartDinner()
    {
        if (!table.TryTakeForkFor(firstForkIndex, TAKE_FORK_DEADLINE))
        {
            return false;
        }
        if (!table.TryTakeForkFor(secondForkIndex, TAKE_FORK_DEADLINE))
        {
            table.FreeFork(firstForkIndex);
            return false;
        }
        return true;
    }

    void StopDinner()
    {
        table.FreeFork(firstForkIndex);
        table.FreeFork(secondForkIndex);
    }

private:
    DinningTable& table;
    size_t firstForkIndex = 0;
    size_t secondForkIndex = 0;
};

using DurationGeneratorFn = std::function<milliseconds()>;

DurationGeneratorFn GetRandomDurationGenerator(milliseconds minValue, milliseconds maxValue)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<milliseconds::rep> distrib(minValue.count(), maxValue.count());

    return [=]() mutable {
        return milliseconds(distrib(gen));
    };
}

void DrivePhilosopher(DinningTable& table, LogStream& logStream, size_t index)
{
    const auto log = logStream.CreateLogger(std::format("Phil {}", index));
    const auto getDinnerDuration = GetRandomDurationGenerator(DINNER_MIN_TIME, DINNER_MAX_TIME);
    const auto getThinkingDuration = GetRandomDurationGenerator(THINKING_MIN_TIME, THINKING_MAX_TIME);

    log("starting");

    Philosopher phil(table, index);
    while (!g_stopped)
    {
        phil.StartDinner();
        log("dinner started");
        std::this_thread::sleep_for(getDinnerDuration());
        phil.StopDinner();
        log("dinner ended");

        if (g_stopped)
        {
            break;
        }

        log("thinking started");
        std::this_thread::sleep_for(getThinkingDuration());
        log("thinking ended");
    }

    log("terminating");
}

int main()
{
    signal(SIGINT, handleStopSignal);
    signal(SIGTERM, handleStopSignal);

    LogStream logStream(std::cerr);
    DinningTable table;

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back(std::bind(&DrivePhilosopher, std::ref(table), std::ref(logStream), i));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
