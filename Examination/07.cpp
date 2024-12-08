#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

struct list
{
    int   m_id;
    list *m_next;

    list() : m_id(-1), m_next(nullptr) {}

    list(int _id) : m_id(_id), m_next(nullptr) {}

    // copy
    list(const list &_src)            = default;
    list &operator=(const list &_lhs) = default;
};

// 面试题6：从尾到头打印链表
// 题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。
void print_reversely(list *_head, std::stringstream &_ss)
{
    // Use recursive to print reverse.
    if (_head != nullptr)
    {
        if (_head->m_next != nullptr)
        {
            print_reversely(_head->m_next, _ss);
        }

        _ss << "{Id Number: " << _head->m_id << " | Address: " << _head << " \n";
    }
    return;
}

int main()
{

    std::stringstream ss;

    // Create list
    list              head;
    std::vector<list> nodes(20, list(1));

    for (int i = 0; i < 19; i++)
    {
        nodes[i].m_next = &nodes[i + 1];
    }
    head.m_next = &nodes.front();

    print_reversely(&head, ss);
    std::cout << "############### Output: \nTail: " << ss.str() <<" :Head.\n" <<std::endl;

    return 0;
}