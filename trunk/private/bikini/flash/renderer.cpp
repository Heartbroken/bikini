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

#include compiled_shader(flash.vs)
#include compiled_shader(flash.ps)


renderer::renderer(video &_video)
:
	m_video(_video), m_viewport_ID(bad_ID)
{
	m_vformat.data = sg_vformat;
	m_vshader.data = flash_vs;
	m_pshader.data = flash_ps;
}
renderer::~renderer()
{
}
bool renderer::create()
{
	m_vformat_ID = m_video.spawn(m_vformat);
	m_memreader_ID = m_video.spawn(m_memreader);
	m_vbuffer_ID = m_video.spawn(m_vbuffer);
	m_video.get_<vo::vbuffer>(m_vbuffer_ID).set_source(m_memreader_ID);
	m_vshader_ID = m_video.spawn(m_vshader);
	m_pshader_ID = m_video.spawn(m_pshader);
	m_vbufset_ID = m_video.spawn(m_vbufset);
	m_video.get_<vo::vbufset>(m_vbufset_ID).set_vformat(m_vformat_ID);
	m_video.get_<vo::vbufset>(m_vbufset_ID).set_vbuffer(0, m_vbuffer_ID, 0, 4);

	return true;
}
void renderer::destroy()
{
	m_video.kill(m_vformat_ID);
	m_video.kill(m_memreader_ID);
	m_video.kill(m_vbuffer_ID);
	m_video.kill(m_vshader_ID);
	m_video.kill(m_pshader_ID);
	m_video.kill(m_vbufset_ID);
}
bool renderer::begin_render()
{
	if (m_video.exists(m_viewport_ID))
	{
		vo::viewport &l_viewport = m_video.get_<vo::viewport>(m_viewport_ID);
		l_viewport.clear();

		vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_memreader_ID);
		l_memreader.clear();

	}

	return true;
}
void renderer::draw_tristrip(const short2* _points, uint _count)
{
	if (m_video.exists(m_viewport_ID))
	{
		vo::viewport &l_viewport = m_video.get_<vo::viewport>(m_viewport_ID);
		vo::drawcall &l_drawcall = l_viewport.add_drawcall();
		l_drawcall.set_vbufset(m_vbufset_ID);
		l_drawcall.set_shaders(m_vshader_ID, m_pshader_ID);
		l_drawcall.set_size(_count - 2);

		vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_memreader_ID);
		l_memreader.add_data(_points, _count * sizeof(short2));
	}
}
void renderer::end_render()
{
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
