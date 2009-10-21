/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// manager

manager::manager() /*: m_counter(0)*/ {
}
manager::~manager() {
	for (uint l_ID = m_objects.first_ID(); l_ID != bad_ID; l_ID = m_objects.next_ID(l_ID))
	{
		delete m_objects.get(l_ID);
	}
}
uint manager::add(object &_object) {
	m_update_order.resize(0);
	return m_objects.add(&_object);
}
bool manager::exists(uint _ID) const {
	return m_objects.exists(_ID);
}
manager::object& manager::get(uint _ID) const {
	return *m_objects.get(_ID);
}
void manager::remove(uint _ID) {
	m_update_order.resize(0);
	m_objects.remove(_ID);
}
uint manager::get_first_ID(uint _type /*= bad_ID*/) const {
	for (uint l_ID = m_objects.first_ID(); l_ID != bad_ID; l_ID = m_objects.next_ID(l_ID))
	{
		object &l_object = get(l_ID);
		if (_type == bad_ID || l_object.type() == _type) return l_ID;
	}
	return bad_ID;
}
uint manager::get_next_ID(uint _prev_ID, uint _type /*= bad_ID*/) const {
	for (uint l_ID = m_objects.next_ID(_prev_ID); l_ID != bad_ID; l_ID = m_objects.next_ID(l_ID))
	{
		object &l_object = get(l_ID);
		if (_type == bad_ID || l_object.type() == _type) return l_ID;
	}
	return bad_ID;
}
void manager::kill(uint _ID) {
	delete m_objects.get(_ID);
}
uint manager::release(uint _ID) {
	if(exists(_ID) && get(_ID).ref_count() > 0) return get(_ID).release();
	return 0;
}
bool manager::update(real _dt) {
	for(uint i = m_shared.size(); i-- > 0;) {
		uint l_ID = m_shared[i];
		assert(exists(l_ID));
		if(get(l_ID).ref_count() == 0) {
			kill(l_ID);
			m_shared.erase(m_shared.begin() + i);
		}
	}
	if(m_update_order.empty())  m_build_update_order();
	for(uint i = 0, s = m_update_order.size(); i < s; ++i) {
		get(m_update_order[i]).update(_dt);
	}
	return true;
}
void manager::clear() {
	for (uint l_ID = m_objects.first_ID(); l_ID != bad_ID; l_ID = m_objects.next_ID(l_ID))
	{
		delete m_objects.get(l_ID);
	}
	//m_counter = 0;
}
void manager::destroy() {
	clear();
}
void manager::m_build_update_order() {
	const uint index_mask = uint(-1) >> (sizeof(uint) * 8 / 2);
	m_update_order.resize(0);
	static array_<uint> l_queue; l_queue.resize(0);
	static array_<uint> l_objects; l_objects.resize(0);
	for (uint l_ID = m_objects.first_ID(); l_ID != bad_ID; l_ID = m_objects.next_ID(l_ID))
	{
		object &l_object = get(l_ID);
		uint l_index = (l_object.ID() & index_mask);
		while (l_objects.size() < l_index) l_objects.push_back(bad_ID);
		l_objects.push_back(l_object.ID());
	}
	for(uint i = 0, s = l_objects.size(); i < s; ++i)
	{
		if(!exists(l_objects[i])) continue;
		l_queue.push_back(l_objects[i]); l_objects[i] = bad_ID;
		while(!l_queue.empty()) {
			if(!exists(l_queue.back()))
			{
				l_queue.pop_back();
				continue;
			}
			object &l_object = get(l_queue.back());
			if(l_object.has_relations()) {
				bool l_continue = false;
				for(uint l_ID = l_object.first_relation(); l_ID != bad_ID; l_ID = l_object.next_relation(l_ID))
				{
					uint l_relation_ID = l_object.get_relation(l_ID);
					uint l_index = uint_ID(l_relation_ID).index;
					if(exists(l_relation_ID) && l_objects[l_index] != bad_ID)
					{
						l_continue = true;
						l_queue.push_back(l_relation_ID);
						l_objects[l_index] = bad_ID;
						break;
					}
				}
				if(l_continue) continue;
			}
			m_update_order.push_back(l_object.ID());
			l_queue.pop_back();
		}
	}
}

// manager::object

manager::object::object(const info &_info, manager &_manager) : m_info(_info), m_manager(_manager), m_ref_count(0) {
	m_ID = m_manager.add(*this);
}
manager::object::~object() {
	m_manager.remove(m_ID);
}
bool manager::object::update(real _dt) {
	return false;
}

// manager::object::info

manager::object::info::info(uint _type) : m_type(_type) {
}
manager::object::info::~info() {
}

} /* namespace bk -------------------------------------------------------------------------------*/
