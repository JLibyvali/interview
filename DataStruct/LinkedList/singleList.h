#pragma once

#include <compare>
#include <exception>
#include <memory>
#include <string>

namespace sList
{

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


struct node
{
    int                   m_id   = -1;
    std::shared_ptr<node> m_next = nullptr;

    node(int _id) : m_id(_id) {}

    auto operator<=>(const node &that) const
    {
        if (auto cmp = this->m_id <=> that.m_id; cmp != 0)
            return cmp;
        throw myException(err::Samenode);
    }

    const bool operator==(const node &that) const
    {
        return (this->m_id == that.m_id);
    }
};

class SList_impl;

class SList
{

public:

    explicit SList(int _val);

    /**
     * @brief return elements nums of single list
     *
     * @return uint32_t
     */
    std::uint32_t                 getLen() const;

    /**
     * @brief insert the "node" at "_pos"
     *
     * @tparam U
     * @param _pos  must be uint32_t
     * @param _node
     */
    bool                          insert(std::uint32_t _pos, const node &_node);

    /**
     * @brief  print all elements in linked list.
     *
     * @param _list
     */
    void                          print() const;

    /**
     * @brief delete the node at "_pos"
     * 
     * @param _pos 
     * @return node 
     */
    node    del(std::uint32_t _pos);


private:

    friend class SList_impl;
    std::shared_ptr<node>       m_head = nullptr;

    std::shared_ptr<node>       m_tail = nullptr;

    std::shared_ptr<SList_impl> Pimpl = nullptr;
};

}  // namespace sList