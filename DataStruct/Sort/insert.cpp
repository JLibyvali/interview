#include "sort.hpp"

#include <cstring>
#include <utility>
#include <vector>

/**
 * @brief select sort, the most simple sort.
 * Time complexity O(n^2)
 * non-stable.
 * @param _vec
 */
void sort::select_sort(sort::num_t &_vec)
{

    int len = _vec.size();
    for (int i = 0; i < len - 1; i++)
    {
        int ith = i;

        for (int j = i + 1; j < len; j++)
        {
            if (_vec[j].first < _vec[ith].first)
            {
                ith = j;
            }
        }

        if (ith != i)
            std::swap(_vec[ith], _vec[i]);
    }
}

/**
 * @brief bubble sort, element will like a bubble to the queue head
 * Time complexity: O(n) ~ O(n^2)
 * Stable sort
 * @param _vec
 */
void sort::bubble_sort(sort::num_t &_vec)
{

    int  len     = _vec.size();
    bool changed = false;

    for (int i = 0; i < len; i++)
    {
        changed = false;
        for (int j = 1; j < len - i; j++)
        {
            if (_vec[j - 1].first > _vec[j].first)
            {
                changed = true;
                std::swap(_vec[j - 1], _vec[j]);
            }
        }

        if (!changed)
            break;
    }
}

/**
 * @brief very best in small sequence
 * Time complexity: O(n) ~ O(n^2)
 * Stable sort
 * @param _vec
 */
void sort::insert_sort(sort::num_t &_vec)
{

    int len = _vec.size();
    if (len < 2)
        return;

    // for (int i = 1; i < len; i++)  // [0,1] is the beginning sort.
    // {
    //     for (int j = i; j > 0; j--)
    //     {
    //         if (_vec[j - 1] > _vec[j])
    //         {
    //             std::swap(_vec[j - 1], _vec[j]);
    //         }
    //     }
    // }

    // ######################### Optimization
    // Using Binary search the insert position.
    for (int i = 1; i < len; i++)
    {
        int left = 0, right = i - 1;  // Binary only in sorted sequence, so [l,i-1] is right.

        while (left <= right)
        {
            // int mid = l + ((r - l) >> 1);   // Maybe overed
            int mid = (left & right) + ((left ^ right) >> 1);
            
            if (_vec[i].first < _vec[mid].first)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        // Faster than for-loop to insert at right position.
        auto tmp = _vec[i];
        memmove(&_vec[left + 1], &_vec[left], (i - left) * sizeof(int));
        _vec[left] = tmp;
    }
}
