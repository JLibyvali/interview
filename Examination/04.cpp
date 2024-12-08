#include <iostream>
#include <vector>

// 面试题3（一）：找出数组中重复的数字
// 题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
// 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，
// 那么对应的输出是重复的数字2或者3。

// hash sol
int duplicate_num(std::vector<int> &_nums)
{

    int              res = -1;
    int              len = _nums.size();
    std::vector<int> digits(len, 0);

    for (const auto &ele : _nums)
    {
        digits[ele] += 1;

        if (digits[ele] == 2)
            res = digits[ele];
    }

    return res;
}

// specific sol, will modify input array
// Case input array: value 0~n-1, size is n;
int duplicate_num2(std::vector<int> &_nums)
{

    int res = -1;
    int len = _nums.size();
    for (int i = 0; i < len; i++)
    {
        if (_nums[i] == i)
        {
            continue;
        }
        else
        {
            while (_nums[i] != i)
            {
                if (_nums[i] == _nums[_nums[i]])
                {
                    res = _nums[i];
                    return res;
                }

                int tmp    = _nums[i];
                _nums[i]   = _nums[tmp];
                _nums[tmp] = tmp;
            }
        }
    }

    return res;
}

int main()
{

    std::vector<int> nums = {2, 3, 5, 4, 3, 2, 6, 7};
    int              res  = duplicate_num(nums);
    int              res2 = duplicate_num2(nums);
    std::cout << "Duplicated num: " << res << std::endl;
    std::cout << "Duplicated num 2 : " << res2 << std::endl;

    return 0;
}