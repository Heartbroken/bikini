/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// pool
template<typename _Type> struct pool_
{
	typedef _Type type;

	inline pool_();
	inline uint add(const type &_value);
	inline type& get(uint _ID);
	inline const type& get(uint _ID) const;
	inline void remove(uint _ID);
	inline bool exists(uint _ID) const;
	inline uint first_ID() const;
	inline uint next_ID(uint _prev_ID) const;
	inline void clear();
	inline uint size() const;
	inline bool empty() const;

private:
	struct item;
	array_<item> m_items;
	uint_array m_free;
	uint m_counter;
};

typedef pool_<notype> pool;

#include "pool.inl"