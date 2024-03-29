/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	rect
/**	[TODO]
 */
struct rect {
	inline rect();
	inline rect(sint _l, sint _t, uint _w, uint _h);
	inline const sint2& min() const;
	inline const sint2& max() const;
	inline const sint2 size() const;
	inline rect& operator = (const rect &_r);
	inline bool operator == (const rect &_r) const;
	inline const rect operator + (const sint2 &_p) const;
	inline const rect operator & (const rect &_r) const;
	inline rect& operator += (const sint2 &_p);
	inline rect& operator &= (const rect &_r);

private:
	sint2 m_min, m_max;
};

#include "rect.inl"