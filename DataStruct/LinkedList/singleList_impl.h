#pragma once

#include "singleList.h"

#include <utility>

namespace sList
{

class SList_impl
{

public:

    explicit SList_impl()  = default;

    // Implements of options to Single List

    std::uint32_t         getLen(const SList &list) const;

    bool                  insert(SList &list,std::uint32_t _pos, const node &_node);

    void                  print(const SList &list) const;

    node del(SList &_list,std::uint32_t _pos);

    /**
     * @brief  chang "_src" node to "_dst" node
     */

    std::pair<node, node> change(uint32_t _pos, node _src, node _dst);

    node                  search(int _id);

    void                  print(SList &_slist);
    SList                 reverse(SList &_slist);
    void                  clean(SList &_slist);
};

}  // namespace sList