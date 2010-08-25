/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

inline rect::rect()
{
}
inline rect::rect(sint _l, sint _t, uint _w, uint _h)
	:
	m_min(_l, _t), m_max(_l + _w, _t + _h)
{}
inline const sint2 & rect::min() const
{
	return m_min;
}
inline const sint2 & rect::max() const
{
	return m_max;
}
inline const sint2 rect::size() const
{
	return max() - min();
}
inline rect & rect::operator = (const rect & _r)
{
	m_min = _r.min(); m_max = _r.max(); return *this;
}
inline bool rect::operator == (const rect & _r) const
{
	return m_min == _r.min() && m_max == _r.max();
}
inline const rect rect::operator + (const sint2 & _p) const
{
	return rect(m_min.x + _p.x, m_min.y + _p.y, m_max.x - m_min.x + _p.x, m_max.y - m_min.y + _p.y);
}
inline const rect rect::operator & (const rect & _r) const
{
	return rect(bk::max(m_min.x, _r.min().x), bk::max(m_min.y, _r.min().y), bk::min(m_max.x, _r.max().x), bk::min(m_max.y, _r.max().y));
}
inline rect & rect::operator += (const sint2 & _p)
{
	*this = *this + _p; return *this;
}
inline rect & rect::operator &= (const rect & _r)
{
	*this = *this & _r; return *this;
}
