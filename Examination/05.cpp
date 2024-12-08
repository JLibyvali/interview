#include <iostream>
#include <vector>

// 面试题4：二维数组中的查找
// 题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按
// 照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个
// 整数，判断数组中是否含有该整数。

bool is_duplicate(std::vector<std::vector<int>> &_nums, int target)
{
    bool existed = false;

    int  rows    = _nums.size();
    int  cols    = _nums[0].size();

    // Choose Right-Up corner num
    int  x = 0, y = cols - 1;
    int  s;

    while (x < rows && y > 0)
    {
        s = _nums[x][y];
        std::cout << "TEST: " << s << std::endl;

        if (s == target)
        {
            existed = true;
            break;
        }
        else if (s < target)
        {
            x++;
        }
        else if (s > target)
        {
            y--;
        }
    }

    return existed;
}

int main()
{

    std::vector<std::vector<int>> nums = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    bool                          res  = is_duplicate(nums, 7);
    bool                          res2 = is_duplicate(nums, 88);
    std::cout << std::boolalpha << "Is 7 duplicated: " << res << "\nAnd 88: " << res2 << std::endl;

    return 0;
}