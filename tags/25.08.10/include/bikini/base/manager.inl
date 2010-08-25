/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// manager

template<typename _T>
inline _T & manager::get_(uint _ID) const
{
	return static_cast<_T &>(get(_ID));
}
template<typename _I>
inline uint manager::spawn(const _I & _info)
{
	_I::object & l_o = * new _I::object(_info, static_cast<typename _I::manager &>(*this));
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I & _info, typename _I::a0 _a0)
{
	_I::object & l_o = * new _I::object(_info, static_cast<typename _I::manager &>(*this), _a0);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1)
{
	_I::object & l_o = * new _I::object(_info, static_cast<typename _I::manager &>(*this), _a0, _a1);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2)
{
	_I::object & l_o = * new _I::object(_info, static_cast<typename _I::manager &>(*this), _a0, _a1, _a2);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3)
{
	_I::object & l_o = * new _I::object(_info, static_cast<typename _I::manager &>(*this), _a0, _a1, _a2, _a3);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3, typename _I::a4 _a4)
{
	_I::object & l_o = * new _I::object(_info, static_cast<typename _I::manager &>(*this), _a0, _a1, _a2, _a3, _a4);
	return l_o.ID();
}
template<typename _I>
inline uint manager::m_find_shared(const _I & _info)
{
	for (uint i = 0, s = m_shared.size(); i < s; ++i)
	{
		uint l_ID = m_shared[i];
		if(!exists(l_ID)) continue;
		const object::info & l_info = get(l_ID).get_info();
		if(l_info.type() != _info.type()) continue;
		if(static_cast<const _I &>(l_info) == _info) return l_ID;
	}
	return bad_ID;
}
template<typename _I>
inline uint manager::request(const _I & _info)
{
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::request(const _I & _info, typename _I::a0 _a0)
{
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::request(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1)
{
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::request(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2)
{
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1, _a2);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::request(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3)
{
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1, _a2, _a3);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::request(const _I & _info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3, typename _I::a4 _a4)
{
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1, _a2, _a3, _a4);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}

// manager::object

inline const manager::object::info & manager::object::get_info() const
{
	return m_info;
}
template<typename _I> const _I & manager::object::get_info_() const
{
	return static_cast<const _I &>(m_info);
}
inline manager & manager::object::get_manager() const
{
	return m_manager;
}
template <typename _M> inline _M & manager::object::get_manager_() const
{
	return static_cast<_M &>(m_manager);
}
inline uint manager::object::type() const
{
	return m_info.type();
}
inline uint manager::object::ID() const
{
	return m_ID;
}
inline uint manager::object::add_relation(uint _relation)
{
	m_manager.m_update_order.resize(0);
	return m_relations.add(_relation);
}
inline void manager::object::remove_relation(uint _ID)
{
	m_manager.m_update_order.resize(0);
	m_relations.remove(_ID);
}
inline uint manager::object::first_relation() const
{
	return m_relations.first_ID();
}
inline uint manager::object::next_relation(uint _ID) const
{
	return m_relations.next_ID(_ID);
}
inline uint manager::object::get_relation(uint _ID) const
{
	return m_relations.get(_ID);
}
inline bool manager::object::has_relation(uint _ID) const
{
	return m_relations.exists(_ID);
}
inline bool manager::object::has_relations() const
{
	return !m_relations.empty();
}
inline uint manager::object::add_ref()
{
	return ++m_ref_count;
}
inline uint manager::object::ref_count() const
{
	return m_ref_count;
}
inline uint manager::object::release()
{
	return --m_ref_count;
}

// manager::object::info

inline uint manager::object::info::type() const
{
	return m_type;
}
