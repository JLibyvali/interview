#pragma once

#include <utility>

namespace slist
{

struct node;
class SList;

class SList_impl
{

public:

    SList_impl()  = default;
    ~SList_impl() = default;

    // Enable copy and move sematic

    // Implements of options to Single List

    int                   getLen(const SList &m_list) const;
    void                  print(const SList &m_list) const;
    bool                  reverse(SList &m_list) const;
    node                  del(const SList &m_list, int _pos);

    // Use value parameter, case don't need to overload `lvalue &` and `rvalue &&` version
    bool                  insert(SList &m_list, int _pos, node &_node);

    /**
     * @brief  chang "_src" node to "_dst" node
     */

    std::pair<node, node> change(int _pos, node _src, node _dst);

    slist::node           search(int _id);

private:

    /**
     * @brief This is Deprecated, I wanna use Interface Class(SList) `this pointer ` to initialize a member simplify
     * the impl method parameter list. But It will case undefine behavior,segmentation fault,illegal hardware
    instructions.
     * Case In
            `SList(): m_Pimplptr(new Pimple(*this)){}`
    * The `this` pointer is undefined when the constructor unfinished.
     *
     */
    // SList *m_list;
};

}  // namespace slist