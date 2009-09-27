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

#include "flash.vs.win32.h"
#include "flash.ps.win32.h"

renderer::renderer(video &_video)
:
	m_video(_video), m_viewport_ID(bad_ID)
{
	m_vo_vformat.data = sg_vformat;
	m_vo_vshader.data = flash_vs;
	m_vo_pshader.data = flash_ps;
}
renderer::~renderer()
{
}
bool renderer::create()
{
	m_vo_vformat_ID = m_video.spawn(m_vo_vformat);
	m_vo_memreader_ID = m_video.spawn(m_vo_memreader);
	m_vo_vbuffer_ID = m_video.spawn(m_vo_vbuffer);
	m_video.get_<vo::vbuffer>(m_vo_vbuffer_ID).set_source(m_vo_memreader_ID);
	m_vo_vshader_ID = m_video.spawn(m_vo_vshader);
	m_vo_pshader_ID = m_video.spawn(m_vo_pshader);

	return true;
}
void renderer::destroy()
{
	m_video.kill(m_vo_vformat_ID);
	m_video.kill(m_vo_memreader_ID);
	m_video.kill(m_vo_vbuffer_ID);
	m_video.kill(m_vo_vshader_ID);
	m_video.kill(m_vo_pshader_ID);
}
bool renderer::begin_render()
{
	vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_vo_memreader_ID);
	l_memreader.reset();
	return true;
}
void renderer::draw_tristrip(const short2* _points, uint _count)
{
	vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_vo_memreader_ID);
	l_memreader.add_data(_points, _count * sizeof(short2));
}
void renderer::end_render()
{
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
