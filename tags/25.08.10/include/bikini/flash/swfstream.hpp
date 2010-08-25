/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct swfstream {
	inline loader& get_loader() const { return m_loader; }
	inline const wstring& get_path() const { return m_path; }
	inline uint get_position() const { return m_position; }
	inline bool good() const { return m_file_ID != bad_ID; }
	swfstream(loader &_loader, const wchar* _path);
	~swfstream();
	uint seek(sint _offset = 0, uint _from = 1);
	void align();
	u8 BYTE();
	bool BIT();
	uint UI8();
	uint UI16();
	uint UI32();
	ubig UI64();
	sint SI8();
	sint SI16();
	sint SI32();
	sbig SI64();
	uint EncodedU32();
	real FIXED();
	real FIXED8();
	real FLOAT16();
	real FLOAT();
	rbig DOUBLE();
	uint UB(uint _size);
	sint SB(uint _size);
	real FB(uint _size);
	wstring STRING();
	color RGB();
	color RGBA();
	color ARGB();
	rect RECT();
	r3x3 MATRIX();
	cxform CXFORM();
	cxform CXFORMWITHALPHA();
private:
	loader &m_loader;
	wstring m_path;
	uint m_file_ID, m_position;
	u8 m_byte, m_bit;
	uint m_version, m_length;
	bool m_compressed;
};
