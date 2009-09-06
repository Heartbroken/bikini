/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct uint_ID
{
	static const uint uint_half_size = sizeof(uint) * 8 / 2;
	uint counter : uint_half_size, index : uint_half_size;
	inline uint_ID() {}
	inline uint_ID(uint _counter, uint _index) : counter(_counter), index(_index) {}
	inline uint_ID(const uint_ID &_ID) : counter(_ID.counter), index(_ID.index) {}
	inline uint_ID(uint _ID) : counter(_ID >> uint_half_size), index(_ID) {}
	inline uint_ID& operator = (const uint_ID &_ID) { counter = _ID.counter; index = _ID.index; return *this; }
	inline uint_ID& operator = (uint _ID) { counter = _ID >> uint_half_size; index = _ID; return *this; }
	inline operator uint() const { return uint((counter << uint_half_size) | index); }
};

template<typename _Type>
struct pool_
{
	typedef _Type type;
	struct item { uint_ID ID; type value; };
	pool_() : m_counter(0) {}
	uint_ID add(const type &_value)
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
	type& get(const uint_ID &_ID)
	{
		assert(exists(_ID));
		return m_items[_ID.index].value;
	}
	const type& get(const uint_ID &_ID) const
	{
		assert(exists(_ID));
		return m_items[_ID.index].value;
	}
	void remove(const uint_ID &_ID)
	{
		assert(exists(_ID));
		m_free.push_back(_ID.index);
		m_items[_ID.index].ID = bad_ID;
	}
	bool exists(const uint_ID &_ID) const
	{
		if (_ID.index > m_items.size() || m_items[_ID.index].ID != _ID) return false;
		return true;
	}
	uint_ID first_ID() const
	{
		for (uint i = 0, s = m_items.size(); i < s; ++i)
		{
			const item &l_item = m_items[i];
			if (l_item.ID != bad_ID) return l_item.ID;
		}
		return bad_ID;
	}
	uint_ID next_ID(const uint_ID &_prev_ID) const
	{
		assert(_prev_ID.index < m_items.size());
		for (uint i = _prev_ID.index + 1, s = m_items.size(); i < s; ++i)
		{
			const item &l_item = m_items[i];
			if (l_item.ID != bad_ID) return l_item.ID;
		}
		return bad_ID;
	}
private:
	array_<item> m_items;
	uint_array m_free;
	uint m_counter;
};

typedef pool_<notype> pool;
