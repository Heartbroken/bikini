/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

static const D3DVERTEXELEMENT9 sg_vformat[] = 
{
	{ 0, 0, D3DDECLTYPE_SHORT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0xff, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 }
};

renderer::renderer(video &_video)
:
	m_video(_video), m_viewport_ID(bad_ID)
{
	m_vo_vformat.data = sg_vformat;
}
renderer::~renderer()
{
}
bool renderer::create()
{
	m_vo_vformat_ID = m_video.spawn(m_vo_vformat);
	m_vo_memreader_ID = m_video.spawn(m_vo_memreader, 1024 * 1024 * 1);
	return true;
}
void renderer::destroy()
{
	m_video.kill(m_vo_vformat_ID);
	m_video.kill(m_vo_memreader_ID);
}
bool renderer::begin_render()
{
	return true;
}
void renderer::draw_tristrip(const short2* _points, uint _count)
{
	vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_vo_memreader_ID);

	if (!l_memreader.push_data(_points, _count * sizeof(short2)))
	{
		std::cerr << "WARNING: Flash renderer memreader buffer is full.\n";
	}
}
void renderer::end_render()
{
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
