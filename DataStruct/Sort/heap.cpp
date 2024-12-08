#include "sort.hpp"

#include <iterator>
#include <vector>

void _merge(
    sort::num_t::iterator _begin1, sort::num_t::iterator _end1, sort::num_t::iterator _begin2,
    sort::num_t::iterator _end2, sort::num_t &_res
)
{

    auto a = _begin1, b = _begin2;
    auto it = _res.begin();

    while (a != _end1 && b != _end2)
    {
        if ((*a).first < (*b).first)
        {
            *it = *a;
            ++it;
            ++a;
        }
        else
        {
            *it = *b;
            ++it;
            ++b;
        }
    }

    if (a == _end1)
    {
        _res.insert(_res.end(), b, _end2);
    }

    if (b == _end2)
    {
        _res.insert(_res.end(), a, _end1);
    }
}

void _merge_sort(sort::num_t &_vec, sort::num_t::iterator _low, sort::num_t::iterator _high)
{
    if ((_high - _low) <= 1)
        return;

    auto mid = _low + std::distance(_low, _high) / 2;
    _merge_sort(_vec, _low, mid);
    _merge_sort(_vec, mid, _high);

    // merge
    sort::num_t temp;
    temp.reserve(_vec.capacity());

    _merge(_low, mid, mid, _high, temp);
    _vec.assign(temp.begin(), temp.end());
}

// Stable sort
// Time Complexity: O(nlogn)
void sort::merge_sort(sort::num_t &_vec) { _merge_sort(_vec, _vec.begin(), _vec.end()); }

// Unstable sort
// Time Complexity: O(nlogn)
void sort::heap_sort(sort::num_t &_vec) {


    
}