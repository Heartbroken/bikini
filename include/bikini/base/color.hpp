/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// color
template<typename _Type>
struct color_ : matrix_<1, 4, _Type> {
	inline color_();
	inline color_(_Type _r, _Type _g, _Type _b, _Type _a = _Type(1));
	inline color_(u8 _r, u8 _g, u8 _b, u8 _a = u8(255));
	inline color_(u32 _c);
	inline const _Type r() const;
	inline _Type& r();
	inline const _Type g() const;
	inline _Type& g();
	inline const _Type b() const;
	inline _Type& b();
	inline const _Type a() const;
	inline _Type& a();
	inline operator u32 () const;
};
typedef color_<real> color;

const color white(r_1, r_1, r_1);
const color black(r_0, r_0, r_0);
const color red(r_1, r_0, r_0);
const color green(r_0, r_1, r_0);
const color blue(r_0, r_0, r_1);
const color yellow(r_1, r_1, r_0);
const color cyan(r_0, r_1, r_1);
const color magenta(r_1, r_0, r_1);

/// cxform
template<typename _Type>
struct cxform_ {
	typedef color_<_Type> color;
	inline cxform_() : m_mul(white), m_add(black) {}
	inline cxform_(const color &_mul, const color &_add) : m_mul(_mul), m_add(_add) {}
	inline const color transform(const color &_c) const {
		return color(
			clamp(_c.r * m_mul.r + m_add.r, _Type(0), _Type(1)),
			clamp(_c.g * m_mul.g + m_add.g, _Type(0), _Type(1)),
			clamp(_c.b * m_mul.b + m_add.b, _Type(0), _Type(1)),
			clamp(_c.a * m_mul.a + m_add.a, _Type(0), _Type(1))
		);
	}
	//friend inline const color operator * (const color &_c, const cxform &_x) {
	//}
private:
	color m_mul, m_add;
};
typedef cxform_<real> cxform;

#include "color.inl"
