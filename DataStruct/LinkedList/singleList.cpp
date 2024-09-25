#include "singleList.h"

#include "singleList_impl.h"

#include <memory>

using namespace sList;

SList::SList(int _val) : Pimpl(std::make_shared<SList_impl>()), m_head(std::make_shared<node>(_val)), m_tail(m_head) {}

std::uint32_t SList::getLen() const { return Pimpl->getLen(*this); }

bool          SList::insert(std::uint32_t _pos, const node &_node) { return Pimpl->insert(*this, _pos, _node); }

void          SList::print() const { return Pimpl->print(*this); }

node          SList::del(std::uint32_t _pos) { return Pimpl->del(*this,_pos); }