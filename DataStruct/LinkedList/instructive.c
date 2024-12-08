#include "instructive.h"

void ins_init(list_head *_list) { _list->m_next = _list->m_prev = _list; }

void insert_after(list_head *_list, list_head *_node)
{

    // doubly list building link.
    _list->m_next->m_prev = _node;
    _node->m_next         = _list->m_next;

    _list->m_next         = _node;
    _node->m_prev         = _list;
}

void insert_before(list_head *_list, list_head *_node)
{
    _list->m_prev->m_next = _node;
    _node->m_prev         = _list->m_prev;

    _list->m_prev         = _node;
    _node->m_next         = _list;
}

void ins_remove(list_head *_node)
{
    _node->m_prev->m_next = _node->m_next;
    _node->m_next->m_prev = _node->m_prev;

    // Isolated node
    _node->m_next = _node->m_prev = _node;
}

int isempty(list_head *_list) { return (_list->m_next == _list); }

int getlen(list_head *_list)
{
    int              len = 0;
    const list_head *cur = _list;

    while (cur->m_next != _list)
    {
        cur = cur->m_next;
        len++;
    }

    return len;
}

void ins_clear(list_head *_list)
{

    if (isempty(_list))
        return;

    list_head *cur = _list;
    
}