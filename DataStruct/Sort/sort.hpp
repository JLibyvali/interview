#pragma once

#include <utility>
#include <vector>

namespace sort
{

// To verify is stable or not
// pair<value, init index>

using num_t = std::vector<std::pair<int, int>>;

extern num_t random_num, nearly_num, reverse_num, unique_num;
void         nums_init();
void         nums_print();
void         select_sort(num_t &_vec);
void         bubble_sort(num_t &_vec);
void         insert_sort(num_t &_vec);

void         quick_sort(num_t &_vec);
void         quick_sort3(num_t &_vec);
void         quick_sort3_optimized(num_t &_vec);
void         quick_sort_intro(num_t &_vec);

void         heap_sort(num_t &_vec);
void         merge_sort(num_t &_vec);
void         shell_sort(num_t &_vec);

}  // namespace sort