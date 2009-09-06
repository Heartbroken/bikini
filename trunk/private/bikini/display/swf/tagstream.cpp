/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace swf { /*-------------------------------------------------------------------------------*/

tagstream::~tagstream() {
	delete &m_stream;
}
void tagstream::m_read_header() {
	SWFHEADER l_header; *this >> l_header;
	if(l_header.version != bad_ID) {
		m_version = l_header.version;
		m_length = l_header.length;
		m_compressed = l_header.compressed;
		SWFINFO l_info; *this >> l_info;
		m_frame_size = l_info.size;
		m_frame_rate = l_info.rate;
		m_frame_count = l_info.frames;
	}
}
u8 tagstream::read_byte() {
	m_byte = m_stream.get(); m_bit = u8(-1);
	return m_byte;
}
bool tagstream::read_bit() {
	if(m_bit == u8(-1)) read_byte(), m_bit = 7;
	return ((m_byte & (1 << m_bit--)) > 0);
}
void tagstream::skip(uint _bytes) {
	while(_bytes--) read_byte();
}

//

tagstream& operator >> (tagstream &_s, UI8 &_v) {
	u8 l_b0 = _s.read_byte();
	_v.v = uint(l_b0);
	return _s;
}
tagstream& operator >> (tagstream &_s, UI16 &_v) {
	u8 l_b0 = _s.read_byte(), l_b1 = _s.read_byte();
	_v.v = uint(l_b0) + uint(l_b1 << 8);
	return _s;
}
tagstream& operator >> (tagstream &_s, UI32 &_v) {
	u8 l_b0 = _s.read_byte(), l_b1 = _s.read_byte(), l_b2 = _s.read_byte(), l_b3 = _s.read_byte();
	_v.v = uint(l_b0) + uint(l_b1 << 8) + uint(l_b2 << 16) + uint(l_b3 << 24);
	return _s;
}
tagstream& operator >> (tagstream &_s, UI64 &_v) {
	u8 l_b0 = _s.read_byte(), l_b1 = _s.read_byte(), l_b2 = _s.read_byte(), l_b3 = _s.read_byte();
	u8 l_b4 = _s.read_byte(), l_b5 = _s.read_byte(), l_b6 = _s.read_byte(), l_b7 = _s.read_byte();
	_v.v = uint(l_b0) + uint(l_b1 << 8) + uint(l_b2 << 16) + uint(l_b3 << 24);
	_v.v += (ubig(l_b4) << 32) + (ubig(l_b5) << 40) + (ubig(l_b6) << 48) + (ubig(l_b7) << 56);
	return _s;
}
tagstream& operator >> (tagstream &_s, SI8 &_v) {
	UI8 l_u; _s >> l_u; _v.v = sint(l_u.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, SI16 &_v) {
	UI16 l_u; _s >> l_u; _v.v = sint(l_u.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, SI32 &_v) {
	UI32 l_u; _s >> l_u; _v.v = sint(l_u.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, SI64 &_v) {
	UI64 l_u; _s >> l_u; _v.v = sbig(l_u.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, EncodedU32 &_v) {
	_v.v = 0;
	u8 l_b = _s.read_byte(); u32 l_c = 5;
	while(l_c--) {
		_v.v |= ((l_b & 0x7f) << (4 - l_c));
		if((l_b & 0x80) == 0) return _s;
	}
	return _s;
}
tagstream& operator >> (tagstream &_s, FIXED &_v) {
	SI32 l_s; _s >> l_s; _v.v = real(l_s.v) / real(65536);
	return _s;
}
tagstream& operator >> (tagstream &_s, FIXED8 &_v) {
	SI16 l_s; _s >> l_s; _v.v = real(l_s.v) / real(256);
	return _s;
}
tagstream& operator >> (tagstream &_s, FLOAT16 &_v) {
	SI16 l_s; _s >> l_s; u16 l_v = u16(l_s.v);
	u32 l_x = (l_v & 0x8000) << 16;
	s32 l_e = (l_v & 0x7c00) >> 10;
	if(l_e) l_x |= (l_e + (127 - 16)) << 23;
	l_x |= (l_v & 0x3ff) << 13;
	_v.v = real(*(f32*)&l_x);
	return _s;
}
tagstream& operator >> (tagstream &_s, FLOAT &_v) {
	UI32 l_u; _s >> l_u;
	_v.v = real(*(f32*)&l_u.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, DOUBLE &_v) {
	UI64 l_u; _s >> l_u;
	_v.v = rbig(*(f64*)&l_u.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, UB &_v) {
	_v.v = 0;
	for(uint i = 0; i < _v.s; ++i) _v.v = (_v.v << 1) | (_s.read_bit() ? 1 : 0);
	return _s;
}
tagstream& operator >> (tagstream &_s, SB &_v) {
	_v.v = (_s.read_bit() ? -1 : 0);
	for(uint i = 1; i < _v.s; ++i) _v.v = (_v.v << 1) | (_s.read_bit() ? 1 : 0);
	return _s;
}
tagstream& operator >> (tagstream &_s, FB &_v) {
	SB l_s(_v.s); _s >> l_s; _v.v = real(l_s.v) / real(256);
	return _s;
}
tagstream& operator >> (tagstream &_s, STRING &_v) {
	u8 l_b; _v.v = L"";
	while((l_b = _s.read_byte()) > 0) {
		if(l_b < 0x7f) {
			_v.v += (wchar_t)l_b;
		} else if((l_b & 0x80) > 0) {
			u16 l_wc = ((l_b & 0x1f) << 6) | (_s.read_byte() & 0x3f);
			_v.v += (wchar_t)l_wc;
		}
	}
	return _s;
}
tagstream& operator >> (tagstream &_s, RGB &_v) {
	u8 l_r = _s.read_byte(), l_g = _s.read_byte(), l_b = _s.read_byte();
	_v.v = color(l_r, l_g, l_b);
	return _s;
}
tagstream& operator >> (tagstream &_s, RGBA &_v) {
	u8 l_r = _s.read_byte(), l_g = _s.read_byte(), l_b = _s.read_byte(), l_a = _s.read_byte();
	_v.v = color(l_r, l_g, l_b, l_a);
	return _s;
}
tagstream& operator >> (tagstream &_s, ARGB &_v) {
	u8 l_a = _s.read_byte(), l_r = _s.read_byte(), l_g = _s.read_byte(), l_b = _s.read_byte();
	_v.v = color(l_r, l_g, l_b, l_a);
	return _s;
}
tagstream& operator >> (tagstream &_s, RECT &_v) {
	UB l_s(5); _s >> l_s;
	SB l_x0(l_s), l_x1(l_s), l_y0(l_s), l_y1(l_s); _s >> l_x0 >> l_x1 >> l_y0 >> l_y1;
	_v.v = rect(l_x0.v, l_y0.v, l_x1.v - l_x0.v, l_y1.v - l_y0.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, MATRIX &_v) {
	_v.v = r3x2_1;
	UB l_has_scale(1); _s >> l_has_scale;
	if(l_has_scale.v) {
		UB l_scale_bits(5); _s >> l_scale_bits;
		FB l_scale_x(l_scale_bits.v), l_scale_y(l_scale_bits.v);
		_s >> l_scale_x >> l_scale_y;
		_v.v[0][0] = l_scale_x.v; _v.v[1][1] = l_scale_y.v;
	}
	UB l_has_rotate(1); _s >> l_has_rotate;
	if(l_has_rotate.v) {
		UB l_rotate_bits(5); _s >> l_rotate_bits;
		FB l_rotate_x(l_rotate_bits.v), l_rotate_y(l_rotate_bits.v);
		_s >> l_rotate_x >> l_rotate_y;
		_v.v[0][1] = l_rotate_x.v; _v.v[1][0] = l_rotate_y.v;
	}
	UB l_translate_bits(5); _s >> l_translate_bits;
	SB l_translate_x(l_translate_bits.v), l_translate_y(l_translate_bits.v);
	_s >> l_translate_x >> l_translate_y;
	_v.v[2][0] = real(l_translate_x.v); _v.v[2][1] = real(l_translate_y.v);
	return _s;
}
tagstream& operator >> (tagstream &_s, CXFORM &_v) {
	UB l_has_add(1); _s >> l_has_add;
	UB l_has_mul(1); _s >> l_has_mul;
	UB l_bits(4); _s >> l_bits;
	if(l_has_mul.v) {
		FB l_r(l_bits), l_g(l_bits), l_b(l_bits); _s >> l_r >> l_g >> l_b;
		_v.m = color(l_r.v, l_g.v, l_b.v);
	}
	if(l_has_add.v) {
		SB l_r(l_bits), l_g(l_bits), l_b(l_bits); _s >> l_r >> l_g >> l_b;
		_v.m = color(real(l_r.v), real(l_g.v), real(l_b.v));
	}
	return _s;
}
tagstream& operator >> (tagstream &_s, CXFORMWITHALPHA &_v) {
	UB l_has_add(1); _s >> l_has_add;
	UB l_has_mul(1); _s >> l_has_mul;
	UB l_bits(4); _s >> l_bits;
	if(l_has_mul.v) {
		FB l_r(l_bits), l_g(l_bits), l_b(l_bits), l_a(l_bits); _s >> l_r >> l_g >> l_b >> l_a;
		_v.m = color(l_r.v, l_g.v, l_b.v, l_a.v);
	}
	if(l_has_add.v) {
		SB l_r(l_bits), l_g(l_bits), l_b(l_bits), l_a(l_bits); _s >> l_r >> l_g >> l_b >> l_a;
		_v.m = color(real(l_r.v), real(l_g.v), real(l_b.v), real(l_a.v));
	}
	return _s;
}
tagstream& operator >> (tagstream &_s, SWFHEADER &_v) {
	UI8 l_b0, l_b1, l_b2; _s >> l_b0 >> l_b1 >> l_b2;
	if((l_b0.v == 0x46 || l_b0.v == 0x43) && l_b1.v == 0x57 && l_b2.v == 0x53) { // "FWS" or "CWS"
		UI8 l_version; _s >> l_version; _v.version = l_version;
		UI32 l_length; _s >> l_length; _v.length = l_length;
		_v.compressed = (l_b0.v == 0x43);
	} else {
		_v.version = bad_ID;
		std::cerr << "ERROR: Bad SWF file header\n";
	}
	return _s;
}
tagstream& operator >> (tagstream &_s, SWFINFO &_v) {
	RECT l_rect; _s >> l_rect; _v.size = l_rect.v.size();
	FIXED8 l_rate; _s >> l_rate; _v.rate = l_rate;
	UI16 l_frames; _s >> l_frames; _v.frames = l_frames;
	return _s;
}
tagstream& operator >> (tagstream &_s, RECORDHEADER &_v) {
	UI16 l_c; _s >> l_c;
	_v.type = (tag::code)((l_c.v & 0xffc0) >> 6);
	_v.length = l_c.v & 0x3f;
	if(_v.length == 0x3f) {
		SI32 l_l; _s >> l_l;
		_v.length = l_l.v;
	}
	return _s;
}

} /* namespace swf ------------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
