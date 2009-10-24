/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

loader::loader()
{}
loader::~loader()
{
	for (uint l_ID = m_pool.first_ID(); l_ID != bad_ID; l_ID = m_pool.next_ID(l_ID)) close(l_ID);
}
uint loader::open(const wchar* _path)
{
	std::ifstream &l_stream = * new std::ifstream(_path, std::ios_base::binary);
	if(l_stream.good()) return m_pool.add(&l_stream);
	delete &l_stream;
	return bad_ID;
}
bool loader::good(uint _ID) const
{
	if (!m_pool.exists(_ID)) return false;
	std::ifstream &l_stream = *m_pool.get(_ID);
	return l_stream.good();
}
uint loader::seek(uint _ID, sint _offset, uint _from)
{
	if (!m_pool.exists(_ID)) return bad_ID;
	std::ifstream &l_stream = *m_pool.get(_ID);
	l_stream.seekg(_offset, (std::ifstream::seek_dir)_from);
	return l_stream.tellg();
}
uint loader::read(uint _ID, handle _buffer, uint _length)
{
	if (!m_pool.exists(_ID)) return bad_ID;
	std::ifstream &l_stream = *m_pool.get(_ID);
	l_stream.read((achar*)_buffer, _length);
	return l_stream.gcount();
}
void loader::close(uint _ID)
{
	if (!m_pool.exists(_ID)) return;
	std::ifstream &l_stream = *m_pool.get(_ID);
	m_pool.remove(_ID);
	l_stream.close();
	delete &l_stream;
}

} /* namespace bk -------------------------------------------------------------------------------*/
