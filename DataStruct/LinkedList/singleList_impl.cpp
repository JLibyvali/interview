#include "singleList_impl.h"

#include "singleList.h"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

using namespace sList;

std::uint32_t SList_impl::getLen(const SList &list) const
{
    std::uint32_t res = 0;

    if (*(list.m_head) == *(list.m_tail))
        return 1;

    auto tmp = list.m_head;

    while (tmp)
    {
        res++;
        tmp = tmp->m_next;
    }

    return res;
}

bool SList_impl::insert(SList &list, std::uint32_t _pos, const node &_node)
{
    bool res      = false;
    auto tmp_node = std::make_shared<node>(_node);

    switch (_pos)
    {
        case 1:
            {

                tmp_node->m_next = list.m_head;
                list.m_head      = tmp_node;
                res              = true;
                break;
            }
        case 0:
            {
                list.m_tail->m_next = tmp_node;
                tmp_node->m_next    = nullptr;
                list.m_tail         = tmp_node;
                res                 = true;
                break;
            }
        default:
            {
                std::uint32_t index = 1;
                auto          tmp   = list.m_head;

                if (_pos == getLen(list))
                {
                    list.m_tail->m_next = tmp_node;
                    tmp_node->m_next    = nullptr;
                    list.m_tail         = tmp_node;
                    break;
                }

                for (; tmp != nullptr; tmp = tmp->m_next, index++)
                {
                    if (index == (_pos - 1))
                    {
                        tmp_node->m_next = tmp->m_next;
                        tmp              = tmp_node;
                        res              = true;
                        break;
                    }
                }
            }
    }

    return res;
}

void SList_impl::print(const SList &list) const
{
    auto ss{std::stringstream()};
    ss << "######### Output List: \n";

    auto tmp = list.m_head;
    auto now = 1;

    while (tmp)
    {
        ss << std::setw(4) << "{id" << tmp->m_id << " |idx" << now << " |addr" << tmp << "}->";
        if (!(now % 4))
        {
            ss << "\n";
        }

        tmp = tmp->m_next;
        now++;
    }

    std::cout << ss.str() << std::endl;
}

node SList_impl::del(SList &_list, std::uint32_t _pos)
{
    auto res{std::make_shared<node>(-1)};
    if (*(_list.m_head) == *(_list.m_tail) && _pos == 1)
    {
        res = _list.m_head;
        clean(_list);
    }
    auto len = getLen(_list);
    switch (_pos)
    {
        case 1:
            {
                auto tmp             = _list.m_head->m_next;
                _list.m_head->m_next = nullptr;
                _list.m_head         = tmp;
            }
        default:
            {
                if (_pos < len)
                {
                    int  cur   = 0;
                    auto tmp_p = _list.m_head;
                    while (tmp_p)
                    {
                        cur++;
                        if (cur == _pos - 1)
                        {
                            res                   = tmp_p->m_next->m_next;
                            tmp_p->m_next->m_next = nullptr;
                            tmp_p->m_next         = res;
                            break;
                        }
                        tmp_p = tmp_p->m_next;
                    }
                }
                else
                {
                    throw myException(err::BadOptions);
                }
            }
    }

    return *res;
}

void SList_impl::clean(SList &_slist)
{
    if (*(_slist.m_head) == *(_slist.m_tail))
    {
        _slist.m_tail = nullptr;
        _slist.m_head = nullptr;
    }

    auto                  len  = getLen(_slist);
    auto                  tmp  = _slist.m_head;
    std::shared_ptr<node> next = nullptr;
    while (tmp)
    {
        next        = tmp->m_next;
        tmp->m_next = nullptr;
        tmp         = next;
    }

    _slist.m_head = nullptr;
    _slist.m_tail = nullptr;
}