#include "sort.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>

// Unstable sort
// Time Complexity: O(nlogn) ~ O(n^2)
int _partition(sort::num_t &_vec, int _low, int _high)
{

    auto pivot = _vec[_low];  // Not always fast, If input sequence already sorted, this pivot selection is slow.

    while (_low < _high)
    {

        while (_low < _high && _vec[_high].first >= pivot.first)
            _high--;

        _vec[_low] = _vec[_high];

        while (_low < _high && _vec[_low].first <= pivot.first)
            _low++;

        _vec[_high] = _vec[_low];
    }

    // placed pivot in correct position.
    _vec[_low] = pivot;
    return _low;
}

void _quick_sort(sort::num_t &_vec, int _low, int _high)
{

    if (_low < _high)
    {
        /**
         * @brief _low, _high represents that Is number placed in correct position.
         */
        int pivot = _partition(_vec, _low, _high);

        _quick_sort(_vec, _low, pivot - 1);
        _quick_sort(_vec, pivot + 1, _high);
    }
}

void sort::quick_sort(sort::num_t &_vec) { _quick_sort(_vec, 0, _vec.size() - 1); }

// 3 way Radix QuickSort
// Time Complexity O(n)
// Unstable sorted, better in duplicated nums
/**
 * @brief Split sequence to 3 part, less than/greater than/equal with pivot value.
 *
 * @param _vec input sequence
 * @param len sequence size()
 */
void _quick_sort_3(sort::num_t &_vec, int _start, int _len)
{
    if (_len <= 1)
        return;

    // i current number
    // [0,_low) < pivot,
    // [_high,len) > pivot
    int i = _start, _low = _start;
    int _high = _start + _len - 1;

    // random pivot
    std::srand((unsigned)(time(NULL)));
    int pivot = rand() % (_len - _start) + _start;

    while (i <= _high)
    {
        if (_vec[i].first > pivot)
        {
            std::swap(_vec[i], _vec[_high]);
            _high--;
            i++;
        }
        else if (_vec[i].first < pivot)
        {
            std::swap(_vec[i], _vec[_low]);
            _low++;
            i++;
        }
        else
        {
            i++;
        }
    }

    // less than pivot part
    _quick_sort_3(_vec, _start, _low - _start);

    // greater than pivot part.
    _quick_sort_3(_vec, _high, _len - _high);
}

void sort::quick_sort3(sort::num_t &_vec) { _quick_sort_3(_vec, 0, _vec.size()); }

void _quick_sort_3_optimized(sort::num_t &_vec, int _start, int _len)
{

    if (_len <= 1)
        return;

    // When less than 15, using insert sort
    if (_len <= 15)
    {
        sort::insert_sort(_vec);
        return;
    }

    // median of (2*n-1)
    int d_100 = _len / 100, nums_len;
    if (d_100)
        nums_len = 2 + d_100;
    else
        nums_len = 3;

    std::vector<int> nums(nums_len);

    if (nums_len > 3)
    {
        for (int i = 1; i < nums_len - 1; i++)
            nums[i] = _vec[100 * i].first;
    }
    else
    {
        nums[0]            = _vec[_start].first;
        nums[1]            = _vec[50].first;
        nums[nums_len - 1] = _vec[_len - 1].first;
    }
    std::sort(nums.begin(), nums.end());
    int pivot = nums[(nums_len - 1) >> 1];

    // Keep num equaled with pivot togethere.
    int i = _start, _low = _start, _high = _len - 1;
    while (i <= _high)
    {
        if (_vec[i].first < pivot)
        {
            std::swap(_vec[i], _vec[_low]);
            i++;
            _low++;
        }
        else if (_vec[i].first > pivot)
        {
            std::swap(_vec[i], _vec[_high]);
            _high--;
        }
        else
        {
            i++;
        }
    }

    // partition sub sequence
    _quick_sort_3_optimized(_vec, _start, _low - _start);
    _quick_sort_3_optimized(_vec, _high, _len - _high);
}

// Using General Optimization
// Median of (2*n-1)
// When sequence size less than 15,  using insert sort
// Keep nums equaled with pivot together.
void sort::quick_sort3_optimized(sort::num_t &_vec) { _quick_sort_3_optimized(_vec, 0, _vec.size()); }

// Time Complexity: O(nlogn)
// Is the version of combined quick_sort and heap_sort
void sort::quick_sort_intro(sort::num_t &_vec) {}