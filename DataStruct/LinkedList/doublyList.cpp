#include "doublyList.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>

using namespace dlist;

int DoubleList::getLen() const
{
    auto cur = m_head.get();
    int  idx = 0;

    while (cur)
    {
        idx++;
        cur = cur->m_next;
    }

    return idx;
}

bool DoubleList::reverse()
{
    node *cur = m_head.get(), *next = cur->m_next;

    while (cur)
    {
        // reverse every node from begining.
        cur->m_next = cur->m_prev;
        cur->m_prev = next;

        // movement
        cur         = next;
        if (next != nullptr)
            next = next->m_next;
    }

    auto tmp = m_tail;
    m_tail   = m_head.release();
    m_head.reset(tmp);

    return true;
}

void DoubleList::print() const
{
    int               idx = 0;
    std::stringstream ss;

    node             *cur = m_head.get();

    while (cur)
    {
        ss << "{List index: " << idx++ << " | ID: " << cur->m_id << " | node Address: " << cur << " }";
        ss << "-->";

        if (idx % 3 == 0)
            ss << "\n";

        cur = cur->m_next;
    }

    std::cout << "##########Output Print: \n" << ss.str() << std::endl;
}

bool DoubleList::insert(node &_node, int _pos)
{
    node *cur = m_head.get();

    int   len = getLen();

    if (_pos < 1 || _pos > len)
        return false;

    // unique_ptr initialize problem.
    if (m_tail == nullptr)
    {
        int len = getLen();
        if (len > 1)
        {
            auto cur = m_head->m_next;

            while (cur->m_next)
            {
                cur = cur->m_next;
            }

            m_tail = cur;
        }
    }

    if (_pos == 1)
    {
        _node.m_next = m_head.release();
        cur->m_prev  = &_node;

        m_head.reset(&_node);
    }
    else if (_pos == len)
    {
        m_tail->m_next = &_node;
        _node.m_prev   = m_tail;

        m_tail         = &_node;
    }
    else
    {
        int idx = 0;
        while (cur)
        {

            if (idx == _pos)
            {
                _node.m_next        = cur;
                _node.m_prev        = cur->m_prev;

                cur->m_prev->m_next = &_node;
                cur->m_prev         = &_node;
            }

            cur = cur->m_next;
            idx++;
        }
    }

    return true;
}

bool DoubleList::del(int _pos)
{

    int len = getLen();
    if (_pos < 1 || _pos > len)
        return false;

    node *cur = m_head->m_next;
    if (_pos == 1)
    {
        auto t    = m_head.release();
        t->m_next = nullptr;
        delete t;
        t = nullptr;

        m_head.reset(cur);

        return true;
    }
    else if (_pos == len)
    {
        auto prev      = m_tail->m_prev;
        m_tail->m_prev = nullptr;
        delete m_tail;
        m_tail = prev;

        return true;
    }
    else
    {
        int  idx = 1;
        auto cur = m_head.get();
        while (cur)
        {
            if (idx == _pos)
            {
                auto prev           = cur->m_prev;
                prev->m_next        = cur->m_next;
                cur->m_next->m_prev = prev;

                cur->m_next         = nullptr;
                cur->m_prev         = nullptr;
                delete cur;

                return true;
            }

            idx++;
            cur = cur->m_next;
        }
    }

    return false;
}
