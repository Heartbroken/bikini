/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

loader::loader() : m_counter(0)
{}
loader::~loader() {
	for(uint i = 0, s = m_files.size(); i < s; ++i) if(m_files[i].stream_p != 0) {
		std::ifstream &l_stream = *m_files[i].stream_p;
		l_stream.close();
		delete &l_stream;
	}
}
uint loader::open(const wchar* _path) {
	std::ifstream &l_stream = * new std::ifstream(_path, std::ios_base::binary);
	if(l_stream.good()) {
		file l_file; l_file.stream_p = &l_stream;
		uint l_index;
		if(m_free_IDs.empty()) {
			l_index = m_files.size();
			m_files.push_back(l_file);
		} else {
			l_index = m_free_IDs.back(); m_free_IDs.pop_back();
			m_files[l_index] = l_file;
		}
		m_files[l_index].ID = (++m_counter << (sizeof(uint) * 8 / 2)) | l_index;
		return m_files[l_index].ID;
	}
	delete &l_stream;
	return bad_ID;
}
bool loader::good(uint _ID) const {
	uint l_index = _ID & (bad_ID >> (sizeof(uint) * 8 / 2));
	if(l_index > m_files.size() || m_files[l_index].ID != _ID || m_files[l_index].stream_p == 0) return false;
	std::ifstream &l_stream = *m_files[l_index].stream_p;
	return l_stream.good();
}
uint loader::seek(uint _ID, sint _offset, uint _from) {
	uint l_index = _ID & (bad_ID >> (sizeof(uint) * 8 / 2));
	if(l_index > m_files.size() || m_files[l_index].ID != _ID || m_files[l_index].stream_p == 0) return bad_ID;
	std::ifstream &l_stream = *m_files[l_index].stream_p;
	if(_offset != 0 || _from != 1) l_stream.seekg(_offset, _from);
	return l_stream.tellg();
}
uint loader::read(uint _ID, handle _buffer, uint _length) {
	uint l_index = _ID & (bad_ID >> (sizeof(uint) * 8 / 2));
	if(l_index > m_files.size() || m_files[l_index].ID != _ID || m_files[l_index].stream_p == 0) return bad_ID;
	std::ifstream &l_stream = *m_files[l_index].stream_p;
	l_stream.read((achar*)_buffer, _length);
	return l_stream.gcount();
}
void loader::close(uint _ID) {
	uint l_index = _ID & (bad_ID >> (sizeof(uint) * 8 / 2));
	if(l_index > m_files.size() || m_files[l_index].ID != _ID || m_files[l_index].stream_p == 0) return;
	std::ifstream &l_stream = *m_files[l_index].stream_p;
	l_stream.close();
	delete m_files[l_index].stream_p;
	m_files[l_index].stream_p = 0;
	m_files[l_index].ID = bad_ID;
}

} /* namespace bk -------------------------------------------------------------------------------*/
