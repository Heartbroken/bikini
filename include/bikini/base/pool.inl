/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// uint_ID

inline uint_ID::uint_ID()
{}
inline uint_ID::uint_ID(uint _counter, uint _index)
:
	counter(_counter), index(_index)
{}
inline uint_ID::uint_ID(const uint_ID &_ID)
:
	counter(_ID.counter), index(_ID.index)
{}
inline uint_ID::uint_ID(uint _ID)
:
	counter(_ID >> uint_half_size), index(_ID)
{}
inline uint_ID& uint_ID::operator = (const uint_ID &_ID)
{
	counter = _ID.counter; index = _ID.index;
	return *this;
}
inline uint_ID& uint_ID::operator = (uint _ID)
{
	counter = _ID >> uint_half_size; index = _ID;
	return *this;
}
inline uint_ID::operator uint() const
{
	return uint((counter << uint_half_size) | index);
}

// pool

template<typename _T>
inline pool_<_T>::pool_()
:
	m_counter(0)
{}
template<typename _T>
inline uint_ID pool_<_T>::add(const type &_value)
{
	uint l_index;
	if (m_free.empty())
	{
		l_index = m_items.size();
		m_items.resize(m_items.size() + 1);
	}
	else
	{
		l_index = m_free.back();
		m_free.pop_back();
	}
	item &l_item = m_items[l_index];
	l_item.ID = uint_ID(m_counter++, l_index);
	l_item.value = _value;
	return l_item.ID;
}
template<typename _T>
inline typename pool_<_T>::type& pool_<_T>::get(const uint_ID &_ID)
{
	assert(exists(_ID));
	return m_items[_ID.index].value;
}
template<typename _T>
inline const typename pool_<_T>::type& pool_<_T>::get(const uint_ID &_ID) const
{
	assert(exists(_ID));
	return m_items[_ID.index].value;
}
template<typename _T>
inline void pool_<_T>::remove(const uint_ID &_ID)
{
	assert(exists(_ID));
	m_free.push_back(_ID.index);
	m_items[_ID.index].ID = bad_ID;
}
template<typename _T>
inline bool pool_<_T>::exists(const uint_ID &_ID) const
{
	if (_ID.index > m_items.size() || m_items[_ID.index].ID != _ID) return false;
	return true;
}
template<typename _T>
inline uint_ID pool_<_T>::first_ID() const
{
	for (uint i = 0, s = m_items.size(); i < s; ++i)
	{
		const item &l_item = m_items[i];
		if (l_item.ID != bad_ID) return l_item.ID;
	}
	return bad_ID;
}
template<typename _T>
inline uint_ID pool_<_T>::next_ID(const uint_ID &_prev_ID) const
{
	assert(_prev_ID.index < m_items.size());
	for (uint i = _prev_ID.index + 1, s = m_items.size(); i < s; ++i)
	{
		const item &l_item = m_items[i];
		if (l_item.ID != bad_ID) return l_item.ID;
	}
	return bad_ID;
}
template<typename _T>
inline void pool_<_T>::clear()
{
	m_items.resize(0);
	m_free.resize(0);
}
template<typename _T>
inline void pool_<_T>::size() const
{
	return m_items.size() - m_free.size();
}
template<typename _T>
inline bool pool_<_T>::empty() const
{
	return m_items.size() == m_free.size();
}