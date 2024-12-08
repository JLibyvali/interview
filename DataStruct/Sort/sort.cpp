#include "sort.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

sort::num_t sort::random_num(100);
sort::num_t sort::nearly_num(100);
sort::num_t sort::reverse_num(100);
sort::num_t sort::unique_num(100);

void        sort::nums_init()
{
    std::random_device rd_device;
    const long         seed{
        rd_device.entropy() ? rd_device() : std::chrono::high_resolution_clock::now().time_since_epoch().count()
    };

    std::mt19937_64                 rd_engine(seed);
    std::uniform_int_distribution<> rd_dis(1, 100);

    for (int i = 0; i < 100; i++)
    {
        int temp_rd           = rd_dis(rd_engine);

        // random num
        random_num[i].first   = temp_rd;
        random_num[i].second  = i;

        // reverse num
        reverse_num[i].first  = 100 - i;
        reverse_num[i].second = i;

        // unique num
        int t                 = i / 20;
        switch (t)
        {
        case 0:
            {
                unique_num[temp_rd].first  = 1;
                unique_num[temp_rd].second = temp_rd;
                break;
            }
        default:
            {
                unique_num[temp_rd].first  = 10 * t;
                unique_num[temp_rd].second = temp_rd;
                break;
            }
        }

        // nearly_num
        if (i / 10)
        {
            nearly_num[i].first  = temp_rd;
            nearly_num[i].second = i;
        }
        else
        {
            nearly_num[i].first  = i;
            nearly_num[i].second = i;
        }
    }
}

void sort::nums_print()
{
    std::stringstream ss;
    ss << "Output nums:\n";
    ss << "Random_num: {";
    for (const auto &[value, index] : sort::random_num)
    {
        ss << "[" << value << "," << index << "]";
    }
    ss << " }\n";

    ss << "Reverse_num: {";
    for (const auto &[value, index] : sort::reverse_num)
    {
        ss << "[" << value << "," << index << "]";
    }
    ss << " }\n";

    ss << "Unique num: {";
    for (const auto &[value, index] : sort::unique_num)
    {
        ss << "[" << value << "," << index << "]";
    }
    ss << " }\n";

    ss << "Nearly num: {";
    for (const auto &[value, index] : sort::nearly_num)
    {
        ss << "[" << value << "," << index << "]";
    }
    ss << " }\n";
    std::cout << ss.str() << std::endl;
}