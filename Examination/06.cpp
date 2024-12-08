#include <iostream>
#include <regex>
#include <string>
#include <string_view>

// 面试题5：替换空格
// 题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入“We are happy.”，
// 则输出“We%20are%20happy.”。

std::string replace_blank(std::string_view _str)
{
    std::string res;
    std::string input{_str.data()};
    std::regex  blank_reg{R"(\s+)", std::regex_constants::optimize};
    try
    {
        res = std::regex_replace(input, blank_reg, "%20");
    }
    catch (const std::regex_error &ex)
    {
        std::cout << "exceptions: " << ex.what() << std::endl;
    }

    return res;
}

int main()
{
    std::string b_mid = " Hello World! We are Happy. ";
    std::string b_n   = "";
    auto        res   = replace_blank(b_mid);
    auto        res2  = replace_blank(b_n);
    std::cout << "Test: " << res << "\nAnd: " << res2 << std::endl;
    return 0;
}