#include "solution.h"

#include <utility>

int maxSubarrayLength(const std::vector<int>& nums, int maxReplacements)
{
    const int* left = nums.data();
    const int* end = nums.data() + nums.size();
    const int* right = left;

    int result = 0;
    int usedReplacements = 0;
    while (right < end)
    {
        if (*right != 1)
        {
            ++usedReplacements;
        }
        if (usedReplacements <= maxReplacements)
        {
            result = std::max<int>(result, right - left + 1);
        }
        else
        {
            while (left <= right)
            {
                if (*(left++) != 1)
                {
                    --usedReplacements;
                    break;
                }
            }
        }
        ++right;
    }

    return result;
}
