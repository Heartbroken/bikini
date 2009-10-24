/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// ring buffer
template<typename _Type> struct ring_
{
	typedef _Type type;

	inline ring_(uint _size);
	inline ~ring_();
	inline uint size() const;
	inline uint used_space() const;
	inline uint free_space() const;
	inline bool empty() const;
	inline bool full() const;
	inline bool push(const type &_v);
	inline bool write(const type* _data, uint _size);
	inline type& front();
	inline const type& front() const;
	inline void pop();
	inline bool read(type* _data, uint _size);

private:
	type* m_buffer;
	const uint m_size;
	uint m_write, m_read;
};

#include "ring.inl"