/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

// swfstream

swfstream::swfstream(loader &_loader, const wchar* _path) :
	m_loader(_loader), m_path(_path), m_position(0)
{
	m_file_ID = m_loader.open(_path);
	if(m_file_ID != bad_ID) {
		u8 l_b0 = BYTE(), l_b1 = BYTE(), l_b2 = BYTE();
		if((l_b0 == 0x46 || l_b0 == 0x43) && l_b1 == 0x57 && l_b2 == 0x53) { // "FWS" or "CWS"
			m_version = UI8(); m_length = UI32();
			m_compressed = (l_b0 == 0x43);
		} else {
			m_loader.close(m_file_ID);
			m_file_ID = bad_ID;
			m_version = bad_ID;
			std::cerr << "ERROR: Bad SWF file header\n";
		}
	}
}
swfstream::~swfstream() {
	if(m_file_ID != bad_ID) m_loader.close(m_file_ID);
}
uint swfstream::seek(sint _offset, uint _from) {
	return m_loader.seek(m_file_ID, _offset, _from);
}
void swfstream::align() {
	m_bit = u8(-1);
}
u8 swfstream::BYTE() {
	m_loader.read(m_file_ID, &m_byte, 1);
	m_bit = u8(-1);
	return m_byte;
}
bool swfstream::BIT() {
	if(m_bit == u8(-1)) BYTE(), m_bit = 7;
	return ((m_byte & (1 << m_bit--)) > 0);
}
uint swfstream::UI8() {
	u8 l_b0 = BYTE();
	return uint(l_b0);
}
uint swfstream::UI16() {
	u8 l_b0 = BYTE(), l_b1 = BYTE();
	return uint(l_b0) + uint(l_b1 << 8);
}
uint swfstream::UI32() {
	u8 l_b0 = BYTE(), l_b1 = BYTE(), l_b2 = BYTE(), l_b3 = BYTE();
	return uint(l_b0) + uint(l_b1 << 8) + uint(l_b2 << 16) + uint(l_b3 << 24);
}
ubig swfstream::UI64() {
	u8 l_b0 = BYTE(), l_b1 = BYTE(), l_b2 = BYTE(), l_b3 = BYTE(), l_b4 = BYTE(), l_b5 = BYTE(), l_b6 = BYTE(), l_b7 = BYTE();
	return uint(l_b0) + uint(l_b1 << 8) + uint(l_b2 << 16) + uint(l_b3 << 24) + (ubig(l_b4) << 32) + (ubig(l_b5) << 40) + (ubig(l_b6) << 48) + (ubig(l_b7) << 56);
}
sint swfstream::SI8() {
	return sint(UI8());
}
sint swfstream::SI16() {
	return sint(UI16());
}
sint swfstream::SI32() {
	return sint(UI32());
}
sbig swfstream::SI64() {
	return sbig(UI64());
}
uint swfstream::EncodedU32() {
	uint l_v = 0;
	u8 l_b = BYTE(); u32 l_c = 5;
	while(l_c--) {
		l_v |= ((l_b & 0x7f) << (4 - l_c));
		if((l_b & 0x80) == 0) return l_v;
	}
	return l_v;
}
real swfstream::FIXED() {
	return real(SI32()) / real(65536);
}
real swfstream::FIXED8() {
	return real(SI16()) / real(256);
}
real swfstream::FLOAT16() {
	u16 l_v = (u16)UI16();
	u32 l_x = (l_v & 0x8000) << 16;
	s32 l_e = (l_v & 0x7c00) >> 10;
	if(l_e) l_x |= (l_e + (127 - 16)) << 23;
	l_x |= (l_v & 0x3ff) << 13;
	return real(*(f32*)&l_x);
}
real swfstream::FLOAT() {
	u32 l_v = (u32)UI32();
	return real(*(f32*)&l_v);
}
rbig swfstream::DOUBLE() {
	u64 l_v = (u64)UI32();
	return rbig(*(f64*)&l_v);
}
uint swfstream::UB(uint _size) {
	uint l_v = 0;
	for(uint i = 0; i < _size; ++i) l_v = (l_v << 1) | (BIT() ? 1 : 0);
	return l_v;
}
sint swfstream::SB(uint _size) {
	if(_size == 0) return 0;
	sint l_v = (BIT() ? -1 : 0);
	for(uint i = 1; i < _size; ++i) l_v = (l_v << 1) | (BIT() ? 1 : 0);
	return l_v;
}
real swfstream::FB(uint _size) {
	return real(SB(_size)) / real(0xffff);
}
wstring swfstream::STRING() {
	astring l_a;
	for(u8 l_b = BYTE(); l_b > 0; l_b = BYTE()) l_a += (achar)l_b;
	if(l_a.length() == 0) return L"";
	uint l_size = MultiByteToWideChar(CP_UTF8, 0, l_a.data(), (int)l_a.length(), 0, 0);
	wchar* l_buffer = (wchar*)_malloca(l_size * sizeof(wchar));
	MultiByteToWideChar(CP_UTF8, 0, l_a.data(), (int)l_a.length(), l_buffer, (int)l_size);
	return wstring(l_buffer, l_size);
}
color swfstream::RGB() {
	u8 l_r = BYTE(), l_g = BYTE(), l_b = BYTE();
	return color(l_r, l_g, l_b);
}
color swfstream::RGBA() {
	u8 l_r = BYTE(), l_g = BYTE(), l_b = BYTE(), l_a = BYTE();
	return color(l_r, l_g, l_b, l_a);
}
color swfstream::ARGB() {
	u8 l_a = BYTE(), l_r = BYTE(), l_g = BYTE(), l_b = BYTE();
	return color(l_r, l_g, l_b, l_a);
}
rect swfstream::RECT() {
	m_bit = u8(-1);
	uint l_s = UB(5);
	sint l_x0 = SB(l_s), l_x1 = SB(l_s), l_y0 = SB(l_s), l_y1 = SB(l_s);
	return rect(l_x0, l_y0, l_x1 - l_x0, l_y1 - l_y0);
}
r3x3 swfstream::MATRIX() {
	m_bit = u8(-1);
	r3x3 l_v = r3x3_1;
	uint l_has_scale = UB(1);
	if(l_has_scale) {
		uint l_scale_bits = UB(5);
		real l_scale_x = FB(l_scale_bits), l_scale_y = FB(l_scale_bits);
		l_v[0][0] = l_scale_x; l_v[1][1] = l_scale_y;
	}
	uint l_has_rotate = UB(1);
	if(l_has_rotate) {
		uint l_rotate_bits = UB(5);
		real l_rotate_x = FB(l_rotate_bits), l_rotate_y = FB(l_rotate_bits);
		l_v[0][1] = l_rotate_x; l_v[1][0] = l_rotate_y;
	}
	uint l_translate_bits = UB(5);
	sint l_translate_x = SB(l_translate_bits), l_translate_y = SB(l_translate_bits);
	l_v[2][0] = real(l_translate_x); l_v[2][1] = real(l_translate_y);
	return l_v;
}
cxform swfstream::CXFORM() {
	m_bit = u8(-1);
	color l_m = white;
	color l_a = black;
	uint l_has_add = UB(1);
	uint l_has_mul = UB(1);
	uint l_bits = UB(4);
	if(l_has_mul) {
		real l_r = FB(l_bits), l_g = FB(l_bits), l_b = FB(l_bits);
		l_m = color(l_r, l_g, l_b);
	}
	if(l_has_add) {
		sint l_r = SB(l_bits), l_g = SB(l_bits), l_b = SB(l_bits);
		l_a = color(real(l_r), real(l_g), real(l_b));
	}
	return cxform(l_m, l_a);
}
cxform swfstream::CXFORMWITHALPHA() {
	m_bit = u8(-1);
	color l_m = white;
	color l_a = black;
	uint l_has_add = UB(1);
	uint l_has_mul = UB(1);
	uint l_bits = UB(4);
	if(l_has_mul) {
		real l_r = FB(l_bits), l_g = FB(l_bits), l_b = FB(l_bits), l_a = FB(l_bits);
		l_m = color(l_r, l_g, l_b, l_a);
	}
	if(l_has_add) {
		sint l_r = SB(l_bits), l_g = SB(l_bits), l_b = SB(l_bits), l_a = SB(l_bits);
		l_a = color(real(l_r), real(l_g), real(l_b), real(l_a));
	}
	return cxform(l_m, l_a);
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
