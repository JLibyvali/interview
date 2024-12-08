#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

/**
 * @brief 字符串map
 *
 * Input: "effe", "good bad bad good"
 * Output: true
 */

int main()
{

    std::string                 pattern = "feef";
    std::string                 input   = "good bad bad good ";
    std::map<char, std::string> Fir_map, Sec_map;

    // split input and pattern
    std::vector<char>           pat_vec;
    pat_vec.reserve(15);
    for (const auto &ele : pattern)
        pat_vec.push_back(ele);

    std::regex reg{"\\b[a-zA-Z]+\\b", std::regex_constants::optimize};
    // Can't use regex_search() to traverse all elements.
    auto       matched_begin = std::sregex_iterator(input.begin(), input.end(), reg);
    auto       matched_end   = std::sregex_iterator();
    std::cout << "################### Test for regular expression #######################" << std::endl;

    std::for_each(
        matched_begin, matched_end, [&](const std::smatch &_m) { std::cout << "Matched: " << _m.str() << std::endl; }
    );

    // also can use the regex_token_iterator<> to tokenize work
    // more safe way that C: strtok(,);
    std::regex               split{R"(\s+)", std::regex_constants::optimize};
    std::vector<std::string> words_vec;
    words_vec.reserve(15);
    auto start = std::sregex_token_iterator{input.begin(), input.end(), split, -1};
    auto tail  = std::sregex_token_iterator();
    for (auto it = start; it != tail; ++it)
        words_vec.push_back(it->str());

    // map detect
    if (pat_vec.size() != words_vec.size())
    {
        std::cout << __LINE__ << " Failed" << std::endl;
        return -1;
    }

    int  idx = 0;
    char First, Second;
    for (auto it = pat_vec.begin(); it != pat_vec.end(); ++it)
    {
        if (Fir_map.empty())
        {
            if (!idx)
            {
                Fir_map[*it] = words_vec[idx];
                First        = *it;
                idx++;
                continue;
            }
        }

        if (Sec_map.empty() && First != *it)
        {
            Sec_map[*it] = words_vec[idx];
            Second       = *it;
            idx++;
            continue;
        }

        // Traverse and compare
        if (First == *it)
        {
            std::map<char, std::string> temp = {{*it, words_vec[idx]}};

            if (!temp[*it].compare(Fir_map[First]))
            {
                idx++;
                continue;
            }
            else
            {

                std::cout << __LINE__ << " Failed" << std::endl;
                return -1;
            }
        }
        else if (Second == *it)
        {
            std::map<char, std::string> temp = {{*it, words_vec[idx]}};

            if (!temp[*it].compare(Sec_map[Second]))
            {
                idx++;
                continue;
            }
            else
            {
                std::cout << __LINE__ << " Failed: " << idx << std::endl;
                return -1;
            }
        }
        else
        {
            std::cout << __LINE__ << " Unknow value: " << *it << std::endl;
            return -1;
        }
    }
    std::cout << "Right." << std::endl;
    return 0;
}