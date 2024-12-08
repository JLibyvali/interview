#include "sort.hpp"

#include <iostream>
#include <sstream>

int main()
{

    auto print_num = [&](const sort::num_t &_num)
    {
        std::stringstream ss;
        ss << "NUM: ";
        for (const auto [value, index] : _num)
        {
            ss << "[" << value << "," << index << "] ";
        }

        std::cout << ss.str() << std::endl;
    };

    std::cout << "##################### Beginning Test #################" << std::endl;
    sort::nums_init();
    sort::nums_print();

    std::cout << "##################### Insertion Sort #################" << std::endl;
    // sort::insert_sort(sort::random_num);
    // sort::insert_sort(sort::reverse_num);
    // sort::insert_sort(sort::nearly_num);
    // sort::insert_sort(sort::unique_num);

    std::cout << "##################### Quick Sort #################" << std::endl;
    sort::shell_sort(sort::random_num);
    sort::shell_sort(sort::reverse_num);
    sort::shell_sort(sort::unique_num);
    sort::shell_sort(sort::nearly_num);
    sort::nums_print();

    return 0;
}