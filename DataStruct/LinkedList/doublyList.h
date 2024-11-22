// List node
#pragma once

#include <memory>
#include <utility>

namespace dlist
{

struct node
{
    int   m_id;
    node *m_next, *m_prev;

    node() : node(-1) {}

    node(int _id) : m_id(_id), m_next(nullptr), m_prev(nullptr) {}

    ~node()                = default;

    // Copy sematics
    node(const node &_src) = default;

    node &operator=(const node &_lhs)
    {
        if (this == &_lhs)
            return *this;

        node tmp{_lhs};
        this->moveFrom(tmp);
        return *this;
    }

    // move sematics
    node(node &&_src) noexcept { this->moveFrom(_src); }

    node &operator=(node &&_lhs) noexcept
    {
        this->moveFrom(_lhs);
        return *this;
    }

private:

    void moveFrom(node &_another) noexcept
    {
        this->m_id   = std::exchange(_another.m_id, 0);
        this->m_next = std::exchange(_another.m_next, nullptr);
        this->m_prev = std::exchange(_another.m_prev, nullptr);
    }
};

class DoubleList
{

public:

    DoubleList() : DoubleList(0) {}

    DoubleList(int _id) : m_head(std::make_shared<node>(_id)), m_tail(m_head) {}

    ~DoubleList() = default;

    /**
     * @brief Inset node at position with given _id
     *
     * @param _id
     * @param pos
     * @return bool  insert success or not.
     */
    bool cinsert(int _id, int pos);

    /**
     * @brief Reverse Doubly linked list
     *
     * @return bool
     */
    bool reverse();

    /**
     * @brief Delete give id node, if fail throw exception.
     *
     * @param _id
     * @return node
     */
    node del(int _id);

    /**
     * @brief Print all linked list nodes.
     */
    void print() const;
    int  clearList() const;
    node change_node(int _id, int _new);
    node get_node(int _id);
    int  getLen() const;

private:

    DoubleList(const DoubleList &_src)            = delete;
    DoubleList &operator=(const DoubleList &_lhs) = delete;

    void        moveFrom(DoubleList &_another) noexcept
    {
        this->m_head.swap(_another.m_head);
        this->m_tail.swap(_another.m_tail);
    }

    std::shared_ptr<node> m_head, m_tail;
};

}  // namespace dlist