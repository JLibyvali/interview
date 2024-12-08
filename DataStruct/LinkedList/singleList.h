#pragma once
#include "singleList_impl.h"

#include <compare>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace slist
{

// Exception handler
enum class err
{
    Samenode,
    Nullpointer,
    BadOptions
};

class myException : public std::exception
{
private:

    std::string str;

public:

    myException(err _errtype)
    {
        switch (_errtype)
        {
        case err::Nullpointer: str = "Nullpointer"; break;
        case err::Samenode   : str = "Samenode"; break;
        default              : str = "Unknow exception type";
        }
    }

    virtual const char *what() const noexcept override { return str.c_str(); }
};

/**
 * @brief This Linked nodes implement Whole `5-rules constructors` and comparaison sematic
 *
 */
struct node
{
    int   m_id;
    node *m_next;

    node(int _id) : m_id(_id), m_next(nullptr) {}

    ~node()
    {
        // Can auto recursively destruct objects.
        delete m_next;
        m_next = nullptr;
    }

    // Copy sematics
    node(const node &_src) = default;

    node &operator=(const node &_lhs)
    {
        if (this == &_lhs)
            return *this;

        // Using copy and swap sematics ensure the exception safety
        // Don't Using that in Copy-constructor , will case stack overflow.
        node temp{_lhs};
        this->moveFrom(temp);

        return *this;
    }

    // Move sematics
    node(node &&_src) noexcept
    {
        std::cout << "######## Move ###########" << std::endl;
        this->moveFrom(_src);
    }

    node &operator=(node &&_lhs) noexcept
    {

        this->moveFrom(_lhs);
        return *this;
    }

    // Cpp20
    auto operator<=>(const node &_src) const
    {
        if (auto cmp = this->m_id <=> _src.m_id; cmp != 0)
            return cmp;

        throw myException(err::Samenode);
    }

    const bool operator==(const node &that) const { return (this->m_id == that.m_id); }

private:

    /**
     * @brief noexcept for copy and move, and simplify when datamembers changed.
     *
     * @param _another
     */
    void moveFrom(node &_another) noexcept
    {
        this->m_next = std::exchange(_another.m_next, nullptr);
        this->m_id   = std::exchange(_another.m_id, 0);
    }
};

class SList
{

public:

    explicit SList(int _val);
    ~SList() = default;

    // Move sematic
    SList(SList &&_src) noexcept;
    SList &operator=(SList &&_rhs) noexcept;

    /**
     * @brief return elements nums of single list
     *
     * @return int
     */
    int    getLen() const;

    /**
     * @brief insert the "node" at "_pos"
     *
     * @param _pos  insert postion, from 1 ~ getLen()
     * @param _node aimed insert node
     */
    bool   insert(int _pos, node &_node);

    /**
     * @brief  print all elements in linked list.
     * @param _list
     */
    void   print() const;

    /**
     * @brief delete the node at "_pos"
     *
     * @param _pos
     * @return node
     */
    node   del(int _pos);

    /**
     * @brief Reverse single list
     *
     * @return bool, true for reverse success.
     */
    bool   reverse();

private:

    // Non copyable
    void moveFrom(SList &_another) noexcept;
    SList(const SList &_src)                           = delete;
    SList                &operator=(const SList &_src) = delete;

    // Using unique pointer.
    std::unique_ptr<node> m_head;

    /**
     * @brief Using Private implement pattern,
     * unique_ptr(), shared_ptr() all ok.
     */
    friend class SList_impl;
    std::unique_ptr<SList_impl> m_Pimplptr;
};

}  // namespace slist