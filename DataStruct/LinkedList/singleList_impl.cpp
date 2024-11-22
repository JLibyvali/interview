#include "singleList_impl.h"

#include "singleList.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

using namespace slist;

// constructor

int SList_impl::getLen(const SList &m_list) const
{
    int  res       = 1;
    auto head_node = m_list.m_head.get();

    while (head_node)
    {
        res++;
        head_node = head_node->m_next;
    }

    return res;
}

bool SList_impl::insert(SList &m_list, int _pos, node &_node)
{
    bool res = false;

    if (_pos == 1)
    {
        _node.m_next = m_list.m_head.release();
        m_list.m_head.reset(&_node);

        return true;
    }

    if (_pos > 1 && _pos <= getLen(m_list))
    {
        int   idx  = 1;
        node *prev = nullptr, *cur = m_list.m_head.get();
        while (cur)
        {
            if (idx == _pos)
            {
                prev->m_next = &_node;
                _node.m_next = cur;
                return true;
            }
            idx++;

            prev = cur;
            cur  = cur->m_next;
        }
    }

    return res;
}

void SList_impl::print(const SList &m_list) const
{
    auto ss{std::stringstream()};

    ss << "######### Output List: \n";
    auto temp_node = m_list.m_head.get();
    auto now       = 0;

    while (temp_node)
    {
        ss << std::setw(4) << "{id" << temp_node->m_id << " |List Index: " << now << " |addr" << temp_node << "}->";
        if (!(now % 4))
        {
            ss << "\n";
        }

        temp_node = temp_node->m_next;
        now++;
    }

    std::cout << ss.str() << std::endl;
}

slist::node SList_impl::del(const SList &m_list, int _pos)
{
    slist::node res{-1};
    int         len = getLen(m_list);

    if (_pos < 1 && _pos > len)
        return res;

    node *cur = m_list.m_head.get(), *prev = nullptr;
    int   idx = 1;

    // Simple delete node
    if (_pos == 1)
    {
        res = *cur;
        cur = cur->m_next;
        return res;
    }
    else if (_pos == len)
    {
        while (cur)
        {
            prev = cur;
            cur  = cur->m_next;
        }

        res = *prev;
        return res;
    }
    else
    {
        while (cur)
        {

            if (_pos == idx)
            {
                prev->m_next = cur->m_next;
                cur->m_next  = nullptr;
            }

            idx++;
            prev = cur;
            cur  = cur->m_next;
        }

        res = *cur;
        return res;
    }
}

bool SList_impl::reverse(SList &m_list) const
{
    int   res = false;
    node *cur = m_list.m_head.get(), *prev = nullptr, *next = cur->m_next;

    while (cur)
    {
        // reverse from begin
        cur->m_next = prev;

        // movement
        prev        = cur;
        cur         = next;
        if (next != nullptr)
            next = next->m_next;
    }
    m_list.m_head.release();
    m_list.m_head.reset(prev);

    return res;
}