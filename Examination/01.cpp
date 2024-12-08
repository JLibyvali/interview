#include <cstdio>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

/**
 * @brief
 一个整数数组 nums ，请计算数组的 中心下标 。

数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

如果中心下标位于数组最左端，那么左侧数之和视为 0
，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。

如果数组有多个中心下标，应该返回 最靠近左边 的那一个。如果数组不存在中心下标，返回 -1 。
示例 1：

输入：nums = [1, 7, 3, 6, 5, 6]
输出：3
解释：
中心下标是 3 。
左侧数之和 sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11 ，
右侧数之和 sum = nums[4] + nums[5] = 5 + 6 = 11 ，二者相等。
 *
 */

int pivotIndex(std::vector<int> &nums)
{
    std::priority_queue<int, std::vector<int>, std::greater<>> res;
    bool                                                       none_res = false;
    int                                                        len      = nums.size();
    int                                                        mid      = 0 + (len >> 1);
    int                                                        prev = 0, behind = 0;

    for (int i = mid; i < len; i++)
    {

        if (i == len - 1)
        {
            prev   = std::accumulate(nums.begin(), nums.begin() + i, 0);
            behind = 0;
        }
        else
        {
            prev   = std::accumulate(nums.begin(), nums.begin() + i, 0);
            behind = std::accumulate(nums.begin() + i + 1, nums.end(), 0);
        }

        if (prev == behind)
        {
            res.push(i);
        }
    }

    for (int i = mid; i >= 0; i--)
    {
        if (i == 0)
        {
            prev   = 0;
            behind = std::accumulate(nums.begin() + i + 1, nums.end(), 0);
        }
        else
        {
            prev   = std::accumulate(nums.begin(), nums.begin() + i, 0);
            behind = std::accumulate(nums.begin() + i + 1, nums.end(), 0);
        }

        if (prev == behind)
        {
            res.push(i);
        }
    }

    if (res.empty())
        return -1;
    else
        return res.top();
}

int main()
{
    std::vector<int> nums = {1, 2, 3};
    int              res  = pivotIndex(nums);
    std::cout << "RES: " << res << std::endl;
}
