#include "singleList.h"

#include "singleList_impl.h"

#include <iostream>
#include <memory>
#include <utility>

using namespace slist;

// Constructor
SList::SList(int _val) : m_head(new node(_val)) { m_Pimplptr.reset(new SList_impl()); }

// Move sematics
void SList::moveFrom(SList &_another) noexcept
{
    // unique pointer use std::move
    std::swap(this->m_head, _another.m_head);
    std::swap(this->m_Pimplptr, this->m_Pimplptr);
}

SList::SList(SList &&_src) noexcept
{
    std::cout << "Move Sematics" << std::endl;
    this->moveFrom(_src);
}

SList &SList::operator=(SList &&_rhs) noexcept
{
    this->moveFrom(_rhs);
    return *this;
}

int  SList::getLen() const { return m_Pimplptr->getLen(*this); }

bool SList::insert(int _pos, node &_node) { return m_Pimplptr->insert(*this, _pos, _node); }

void SList::print() const { return m_Pimplptr->print(*this); }

node SList::del(int _pos) { return m_Pimplptr->del(*this, _pos); }

bool SList::reverse() { return m_Pimplptr->reverse(*this); }