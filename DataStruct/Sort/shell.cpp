#include "sort.hpp"

#include <utility>

// UnStable sort
// Time Complexity: O(nlogn), Very Fast

void _shell_sort(sort::num_t &_vec)
{
    int len = _vec.size();
    int gap = len / 2;

    while (gap >= 1)
    {
        for (int i = gap; i < len; i++)
        {
            for (int j = i - gap; j >= 0 && _vec[j].first > _vec[j + gap].first; j -= gap)
            {
                std::swap(_vec[j], _vec[j + gap]);
            }
        }
        gap /= 2;
    }
}

void sort::shell_sort(sort::num_t &_vec) { _shell_sort(_vec); }