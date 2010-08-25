/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// datareader /////////////////////////////////////////////////////////////////////////////////////

struct datareader
{
	const u8 * data;
	inline datareader(pointer _data) : data((const u8 *)_data) {}
	inline datareader(const datareader & _data) : data(_data.data) {}
	inline datareader & read(handle _data, u32 _size)
	{
		memcpy(_data, data, _size); data += _size;
		return *this;
	}
};


template<typename _Type> inline datareader & operator >> (datareader & _reader, _Type & _v)
{
	_v = *reinterpret_cast<const _Type *>(_reader.data); _reader.data += sizeof(_Type);
	return _reader;
}

inline datareader & operator >> (datareader & _reader, const char* &_v)
{
	_v = reinterpret_cast<const char *>(_reader.data); _reader.data += strlen(_v) + 1;
	return _reader;
}

inline datareader & operator >> (datareader & _reader, astring & _v)
{
	_v = reinterpret_cast<const char *>(_reader.data); _reader.data += _v.length() + 1;
	return _reader;
}

template<typename _Type> inline datareader & operator >> (datareader & _reader, std::vector<_Type> &_v)
{
	u32 l_count; _reader >> l_count; _v.resize(l_count); for(u32 i = 0; i < l_count; i++) _reader >> _v[i];
	return _reader;
}

//inline datareader& operator >> (datareader &_reader, rgba &_v) {
//	u32 l_color; _reader >> l_color; _v = rgba(l_color);
//	return _reader;
//}

// datawriter /////////////////////////////////////////////////////////////////////////////////////

struct datawriter
{
	std::vector<u8> data;
	inline datawriter & write(pointer _data, u32 _size)
	{
		const u8 * l_v_p = reinterpret_cast<const u8 *>(_data);
		data.insert(data.end(), l_v_p, l_v_p + _size);
		return *this;
	}
};

template<typename _Type> inline datawriter & operator << (datawriter & _writer, const _Type & _v)
{
	const u8 * l_v_p = reinterpret_cast<const u8 *>(&_v);
	_writer.data.insert(_writer.data.end(), l_v_p, l_v_p + sizeof(_Type));
	return _writer;
}

inline datawriter & operator << (datawriter & _writer, const char * _v)
{
	const u8 * l_v_p = reinterpret_cast<const u8 *>(_v);
	_writer.data.insert(_writer.data.end(), l_v_p, l_v_p + strlen(_v) + 1);
	return _writer;
}

inline datawriter & operator << (datawriter & _writer, const astring & _v)
{
	return _writer << _v.c_str();
}

template<typename _Type> inline datawriter & operator << (datawriter & _writer, const std::vector<_Type> &_v)
{
	_writer << _v.size(); for(u32 i = 0, s = _v.size(); i < s; ++i) _writer << _v[i];
	return _writer;
}

//inline datawriter& operator << (datawriter &_writer, const rgba &_v) {
//	return _writer << (u32)_v;
//}
