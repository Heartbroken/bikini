/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _T>
inline ring_<_T>::ring_(uint _size)
:
	m_size(_size), m_write(0), m_read(0)
{
	m_buffer = (type*)malloc(m_size * sizeof(type));
}
template<typename _T>
inline ring_<_T>::~ring_()
{
	while (!empty()) pop();
	free(m_buffer);
}
template<typename _T>
inline uint ring_<_T>::size() const
{
	return m_size;
}
template<typename _T>
inline uint ring_<_T>::used_space() const
{
	return (m_read > m_write) ? (m_size - m_read + m_write) : (m_write - m_read);
}
template<typename _T>
inline uint ring_<_T>::free_space() const
{
	return (m_read > m_write) ? (m_read - m_write) : (m_size - m_write + m_read);
}
template<typename _T>
inline bool ring_<_T>::empty() const
{
	return m_write == m_read;
}
template<typename _T>
inline bool ring_<_T>::full() const
{
	return (m_write + 1) % m_size == m_read;
}
template<typename _T>
inline bool ring_<_T>::push(const type &_v)
{
	if (full()) return false;

	new(m_buffer + m_write) type(_v);
	m_write = (m_write + 1) % m_size;

	return true;
}
template<typename _T>
inline bool ring_<_T>::write(const type* _data, uint _size)
{
	if (_size > free_space()) return false;

	uint l_write = m_write;

	for (uint i = 0; i < _size; ++i)
	{
		new(m_buffer + l_write) type(_data[i]);
		l_write = (l_write + 1) % m_size;
	}

	m_write = l_write;

	return true;
}
template<>
inline bool ring_<byte>::write(const byte* _data, uint _size)
{
	if (_size > free_space()) return false;

	const byte* l_data = _data;
	uint l_size = _size;
	uint l_write = m_write;

	if (l_write + l_size > m_size)
	{
		memcpy(m_buffer + l_write, l_data, m_size - l_write);
		l_data += m_size - l_write;
		l_size -= m_size - l_write;
		l_write = 0;
	}

	memcpy(m_buffer + l_write, l_data, l_size);
	l_write += l_size;

	m_write = l_write;

	return true;
}
template<typename _T>
inline typename ring_<_T>::type& ring_<_T>::front()
{
	return *(m_buffer + m_read);
}
template<typename _T>
inline const typename ring_<_T>::type& ring_<_T>::front() const
{
	return *(m_buffer + m_read);
}
template<typename _T>
inline void ring_<_T>::pop()
{
	(m_buffer + m_read)->~type();
	m_read = (m_read + 1) % m_size;
}
template<typename _T>
inline bool ring_<_T>::read(type* _data, uint _size)
{
	if (_size > used_space()) return false;

	uint l_read = m_read;

	for (uint i = 0; i < _size; ++i)
	{
		new(_data + i) type(m_buffer[l_read]);
		(m_buffer + m_read)->~type();
		l_read = (l_read + 1) % m_size;
	}

	m_read = l_read;

	return true;
}
template<>
inline bool ring_<byte>::read(byte* _data, uint _size)
{
	if (_size > used_space()) return false;

	byte* l_data = _data;
	uint l_size = _size;
	uint l_read = m_read;

	if (l_read + l_size > m_size)
	{
		memcpy(l_data, m_buffer + l_read, m_size - l_read);
		l_data += m_size - l_read;
		l_size -= m_size - l_read;
		l_read = 0;
	}

	memcpy(l_data, m_buffer + l_read, l_size);
	l_read += l_size;

	m_read = l_read;

	return true;
}
