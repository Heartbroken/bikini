/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _T>
inline ring_<_T>::ring_(uint _size)
:
	m_size(_size * sizeof(type)), m_write(0), m_read(0)
{
	m_buffer = new byte[m_size];
}
template<typename _T>
inline ring_<_T>::~ring_()
{
	while (!empty()) pop();
	delete [] m_buffer;
}
template<typename _T>
inline uint ring_<_T>::size() const
{
	return m_size / sizeof(type);
}
template<typename _T>
inline uint ring_<_T>::used_space() const
{
	return ((m_read > m_write) ? (m_size - m_read + m_write) : (m_write - m_read)) / sizeof(type);
}
template<typename _T>
inline uint ring_<_T>::free_space() const
{
	return size() - used_space();
}
template<typename _T>
inline bool ring_<_T>::empty() const
{
	return m_write == m_read;
}
template<typename _T>
inline bool ring_<_T>::full() const
{
	return (m_write + sizeof(type)) % m_size == m_read;
}
template<typename _T>
inline bool ring_<_T>::push(const type &_v)
{
	if (full()) return false;
	new(m_buffer + m_write) type(_v);
	m_write = (m_write + sizeof(type)) % m_size;
	return true;
}
template<typename _T>
inline typename ring_<_T>::type& ring_<_T>::front()
{
	return *(type*)(m_buffer + m_read);
}
template<typename _T>
inline const typename ring_<_T>::type& ring_<_T>::front() const
{
	return *(const type*)(m_buffer + m_read);
}
template<typename _T>
inline bool ring_<_T>::pop()
{
	if (empty()) return false;
	((type*)(m_buffer + m_read))->~type();
	m_read = (m_read + sizeof(type)) % m_size;
	return true;
}
