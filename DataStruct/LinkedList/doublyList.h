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

    ~node()
    {
        delete m_next;
        m_next = nullptr;
    }

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

    DoubleList(int _id) : m_head(std::make_unique<node>(_id)), m_tail(nullptr) {}

    ~DoubleList() = default;

    // Move sematics
    DoubleList(DoubleList &&_src) { this->moveFrom(_src); }

    DoubleList &operator=(DoubleList &&_lhs)
    {

        this->moveFrom(_lhs);

        return *this;
    }

    /**
     * @brief Inset node at position with given _id
     *
     * @param _id
     * @param pos
     * @return bool  insert success or not.
     */
    bool insert(node &_node, int pos);

    /**
     * @brief Reverse Doubly linked list
     *
     * @return bool
     */
    bool reverse();

    /**
     * @brief Delete give id node, if fail throw exception.
     *
     * @param  postion
     * @return bool
     */
    bool del(int _pos);

    /**
     * @brief Print all linked list nodes.
     */
    void print() const;
    int  getLen() const;

private:

    DoubleList(const DoubleList &_src)            = delete;
    DoubleList &operator=(const DoubleList &_lhs) = delete;

    void        moveFrom(DoubleList &_another) noexcept
    {
        this->m_head.swap(_another.m_head);
        // Release original pointer value.
        _another.m_head.release();

        this->m_tail = std::exchange(_another.m_tail, nullptr);
    }

    std::unique_ptr<node> m_head;
    node                 *m_tail;
};

}  // namespace dlist