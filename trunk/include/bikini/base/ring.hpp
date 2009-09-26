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

	inline ring_(uint _size)
	:
		m_size(_size * sizeof(type)), m_write(0), m_read(0)
	{
		m_buffer = new byte[m_size];
	}
	inline ~ring_()
	{
		while (!empty()) pop();
		delete [] m_buffer;
	}
	inline uint size() const
	{
		return m_size / sizeof(type);
	}
	inline uint used_space() const
	{
		return ((m_read > m_write) ? (m_size - m_read + m_write) : (m_write - m_read)) / sizeof(type);
	}
	inline uint free_space() const
	{
		return size() - used_space();
	}
	inline bool empty() const
	{
		return m_write == m_read;
	}
	inline bool full() const
	{
		return (m_write + sizeof(type)) % m_size == m_read;
	}
	inline bool push(const type &_v)
	{
		if (full()) return false;
		new(m_buffer + m_write) type(_v);
		m_write = (m_write + sizeof(type)) % m_size;
		return true;
	}
	inline type& front()
	{
		return *(type*)(m_buffer + m_read);
	}
	inline bool pop()
	{
		if (empty()) return false;
		((type*)(m_buffer + m_read))->~type();
		m_read = (m_read + sizeof(type)) % m_size;
		return true;
	}

private:
	byte* m_buffer;
	const uint m_size;
	uint m_write, m_read;
};
