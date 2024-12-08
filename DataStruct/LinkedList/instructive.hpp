#pragma once

#include <iostream>
#include <sstream>
#include <utility>

namespace ins_list
{

/**
 * @brief CPP-style combine with OOP
 *
 * @tparam T
 */
template <typename T>
class List
{
public:

    // Initialize as circular doubly list.
    List() : m_previous(this), m_next(this) {}

    List(List<T> *_prev, List<T> *_next) : m_previous(_prev), m_next(_next) {}

    virtual ~List()     = default;

    // copy sematics
    List(List<T> &_src) = default;

    List<T> &operator=(List<T> &_lhs)
    {
        if (this == &_lhs)
            return *this;

        List<T> temp{_lhs};
        std::swap(temp.m_next, this->m_next);
        std::swap(temp.m_previous, this->m_previous);
        return *this;
    }

    // move sematic
    List(List<T> &&_src) noexcept { moveFrom(_src); }

    List<T> &operator=(List<T> &&_lhs) noexcept
    {
        moveFrom(_lhs);
        return *this;
    }

    /**
     * @brief insert this before _list;
     *
     * @param _node
     */
    void insert_before(List<T> *_list)
    {
        if (!_list)
            return;

        this->m_next              = _list;
        this->m_previous          = _list->m_previous;

        _list->m_previous->m_next = this;
        _list->m_previous         = this;
    }

    /**
     * @brief insert this after _list
     *
     * @param _list
     */
    void insert_after(List<T> *_list)
    {
        if (!_list)
            return;

        this->m_previous          = _list;
        this->m_next              = _list->m_next;

        _list->m_next->m_previous = this;
        _list->m_next             = this;
    }

    /**
     * @brief Remove this from list
     *
     */
    void remove()
    {
        this->m_previous->m_next = this->m_next;
        this->m_next->m_previous = this->m_previous;

        this->m_previous = this->m_next = this;
    }

    List<T> *prev() const { return m_previous; }

    List<T> *next() const { return m_next; }

    void     traverse_print() const
    {
        List<T>          *cur = this->m_next;
        std::stringstream ss;
        std::cout << "######################### Using CRTP to print:" << std::endl;
        int idx = 0;
        while (cur != this)
        {
            ss << "{ Index: " << idx++ << " | Data: " << static_cast<T *>(cur)->m_print() << " | Address: [" << cur
               << "]" << "}";
            ss << "--->";

            if (idx % 3 == 0)
                ss << "\n";

            cur = cur->m_next;
        }

        std::cout << ss.str() << std::endl;
    }

private:

    virtual int m_print() = 0;

    void        moveFrom(List<T> &_another) noexcept
    {
        this->m_previous = std::exchange(_another.m_previous, nullptr);
        this->m_next     = std::exchange(_another.m_next, nullptr);
    }

    List<T> *m_previous, *m_next;
};

class Test : public List<Test>
{
public:

    Test() : Test(-1) {}

    explicit Test(int _id) : m_id(_id) {}

    virtual int m_print() override { return m_id; }

private:

    int m_id;
};

}  // namespace ins_list