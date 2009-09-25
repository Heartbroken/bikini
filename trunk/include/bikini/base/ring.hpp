/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// ring buffer
template<typename _Type, uint _Size> struct ring_
{
	typedef _Type type;
	static const uint size = _Size;

	inline ring_()
	:
		m_write(0), m_read(0)
	{
	}
	inline ~ring_()
	{
		while (!empty()) pop();
	}
	inline bool empty() const
	{
		return m_write == m_read;
	}
	inline bool full() const
	{
		return ((m_write + sizeof(type)) % size) == m_read;
	}
	inline bool push(const type &_v)
	{
		if (full()) return false;
		new(m_buffer + m_write) type(_v);
		m_write = (m_write + sizeof(type)) % size;
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
		m_read = (m_read + sizeof(type)) % size;
		return true;
	}

private:
	u8 m_buffer[size * sizeof(type)];
	uint m_write, m_read;
};
