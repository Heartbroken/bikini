/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	stream
/**	[TODO]
 */
struct stream {
	virtual ~stream() {}
	virtual u8 get() = 0;
};

///	tagstream
/**	[TODO]
 */
struct tagstream {
	template<typename _Stream> inline tagstream(_Stream &_stream);
	~tagstream();
	inline bool good() const { return m_version != bad_ID; }
	inline uint version() const { return m_version; }
	inline uint lingth() const { return m_length; }
	inline bool compressed() const { return m_compressed; }
	inline sint2 frame_size() const { return m_frame_size; }
	inline real frame_rate() const { return m_frame_rate; }
	inline uint frame_count() const { return m_frame_count; }
	u8 read_byte();
	bool read_bit();
	void skip(uint _bytes);
private:
	stream &m_stream;
	u8 m_byte, m_bit;
	uint m_version, m_length;
	bool m_compressed;
	sint2 m_frame_size;
	real m_frame_rate;
	uint m_frame_count;
	void m_read_header();
};

///
struct UI8 {
	uint v;
	inline operator uint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, UI8 &_v);
};
///
struct UI16 {
	uint v;
	inline operator uint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, UI16 &_v);
};
///
struct UI32 {
	uint v;
	inline operator uint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, UI32 &_v);
};
///
struct UI64 {
	ubig v;
	inline operator ubig () const { return v; }
	friend tagstream& operator >> (tagstream &_s, UI64 &_v);
};
///
struct SI8 {
	sint v;
	inline operator sint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, SI8 &_v);
};
///
struct SI16 {
	sint v;
	inline operator sint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, SI16 &_v);
};
///
struct SI32 {
	sint v;
	inline operator sint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, SI32 &_v);
};
///
struct SI64 {
	sbig v;
	inline operator sbig () const { return v; }
	friend tagstream& operator >> (tagstream &_s, SI64 &_v);
};
///
struct EncodedU32 {
	uint v;
	inline operator uint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, EncodedU32 &_v);
};
///
struct FIXED {
	real v;
	inline operator real () const { return v; }
	friend tagstream& operator >> (tagstream &_s, FIXED &_v);
};
///
struct FIXED8 {
	real v;
	inline operator real () const { return v; }
	friend tagstream& operator >> (tagstream &_s, FIXED8 &_v);
};
///
struct FLOAT16 {
	real v;
	inline operator real () const { return v; }
	friend tagstream& operator >> (tagstream &_s, FLOAT16 &_v);
};
///
struct FLOAT {
	real v;
	inline operator real () const { return v; }
	friend tagstream& operator >> (tagstream &_s, FLOAT &_v);
};
///
struct DOUBLE {
	rbig v;
	inline operator rbig () const { return v; }
	friend tagstream& operator >> (tagstream &_s, DOUBLE &_v);
};
///
struct UB {
	uint s; uint v;
	inline UB(uint _size = uint(-1)) : s(_size) {}
	inline operator uint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, UB &_v);
};
///
struct SB {
	uint s; sint v;
	inline SB(uint _size = uint(-1)) : s(_size) {}
	inline operator sint () const { return v; }
	friend tagstream& operator >> (tagstream &_s, SB &_v);
};
///
struct FB {
	uint s; real v;
	inline FB(uint _size = uint(-1)) : s(_size) {}
	inline operator real () const { return v; }
	friend tagstream& operator >> (tagstream &_s, FB &_v);
};
///
struct STRING {
	wstring v;
	inline operator wstring () const { return v; }
	friend tagstream& operator >> (tagstream &_s, STRING &_v);
};
///
struct RGB {
	color v;
	inline operator color () const { return v; }
	friend tagstream& operator >> (tagstream &_s, RGB &_v);
};
///
struct RGBA {
	color v;
	inline operator color () const { return v; }
	friend tagstream& operator >> (tagstream &_s, RGBA &_v);
};
///
struct ARGB {
	color v;
	inline operator color () const { return v; }
	friend tagstream& operator >> (tagstream &_s, ARGB &_v);
};
///
struct RECT {
	rect v;
	inline operator rect () const { return v; }
	friend tagstream& operator >> (tagstream &_s, RECT &_v);
};
///
struct MATRIX {
	r3x2 v;
	inline operator r3x2 () const { return v; }
	friend tagstream& operator >> (tagstream &_s, MATRIX &_v);
};
///
struct CXFORM {
	color m, a;
	friend tagstream& operator >> (tagstream &_s, CXFORM &_v);
};
///
struct CXFORMWITHALPHA {
	color m, a;
	friend tagstream& operator >> (tagstream &_s, CXFORMWITHALPHA &_v);
};
///
struct SWFHEADER {
	uint version, length; bool compressed;
	friend tagstream& operator >> (tagstream &_s, SWFHEADER &_v);
};
///
struct SWFINFO {
	sint2 size; real rate; uint frames;
	friend tagstream& operator >> (tagstream &_s, SWFINFO &_v);
};
///
struct RECORDHEADER {
	tag::code type; uint length;
	friend tagstream& operator >> (tagstream &_s, RECORDHEADER &_v);
};
///
struct DefineShape {
	friend tagstream& operator >> (tagstream &_s, DefineShape &_v);
};

#include "tagstream.inl"