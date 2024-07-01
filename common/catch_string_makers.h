#pragma once

#include <catch2/catch_tostring.hpp>
#include <optional>

namespace Catch
{

template<class T>
struct StringMaker<std::optional<T>>
{
    static std::string convert(const std::optional<T>& value)
    {
        if (value.has_value())
        {
            return StringMaker<T>::convert(*value);
        }
        return "<nullopt>";
    }
};

template<>
struct StringMaker<std::nullopt_t>
{
    static std::string convert(const std::nullopt_t&)
    {
        return "<nullopt>";
    }
};

} // namespace Catch
