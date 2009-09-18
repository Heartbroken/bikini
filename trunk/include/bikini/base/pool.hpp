/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// uint_ID
struct uint_ID
{
	static const uint uint_half_size = sizeof(uint) * 8 / 2;
	uint counter : uint_half_size, index : uint_half_size;
	inline uint_ID();
	inline uint_ID(uint _counter, uint _index);
	inline uint_ID(const uint_ID &_ID);
	inline uint_ID(uint _ID);
	inline uint_ID& operator = (const uint_ID &_ID);
	inline uint_ID& operator = (uint _ID);
	inline operator uint() const;
};

/// pool
template<typename _Type> struct pool_
{
	typedef _Type type;

	struct item { uint_ID ID; type value; };

	inline pool_();
	inline uint_ID add(const type &_value);
	inline type& get(const uint_ID &_ID);
	inline const type& get(const uint_ID &_ID) const;
	inline void remove(const uint_ID &_ID);
	inline bool exists(const uint_ID &_ID) const;
	inline uint_ID first_ID() const;
	inline uint_ID next_ID(const uint_ID &_prev_ID) const;
	inline void clear();
	inline void size() const;
	inline bool empty() const;

private:
	array_<item> m_items;
	uint_array m_free;
	uint m_counter;
};

typedef pool_<notype> pool;

#include "pool.inl"