/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace flash_vs
{
#	include "flash.vs"
#	include compiled_shader(flash.vs)
}

namespace flash_ps
{
#	include "flash.ps"
#	include compiled_shader(flash.ps)
}

namespace flash_vf { static const D3DVERTEXELEMENT9 data[] = 
{
	{ 0, 0, D3DDECLTYPE_SHORT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0xff, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 }
};}

namespace flash_rs { static const DWORD data[] =
{
	D3DRS_CULLMODE, D3DCULL_CCW,
	DWORD(-1), DWORD(-1),
};}


renderer::renderer(video &_video)
:
	m_video(_video), m_viewport_ID(bad_ID)
{
	m_vformat.data = flash_vf::data;
	m_vshader.data = flash_vs::data;
	m_pshader.data = flash_ps::data;
	m_states.data = flash_rs::data;
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
	m_states_ID = m_video.spawn(m_states);

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
	m_video.kill(m_states_ID);
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
void renderer::draw_tristrip(const xform &_xform, const color &_color, const short2* _points, uint _count)
{
	if (m_video.exists(m_viewport_ID))
	{
		vo::viewport &l_viewport = m_video.get_<vo::viewport>(m_viewport_ID);
		vo::drawcall &l_drawcall = l_viewport.add_drawcall();
		l_drawcall.set_states(m_states_ID);
		l_drawcall.set_vbufset(m_vbufset_ID);
		l_drawcall.set_shaders(m_vshader_ID, m_pshader_ID);
		l_drawcall.set_size(_count - 2);

		flash_vs::viewport_consts l_viewport_consts;
		l_viewport_consts.area = real4((real)0, (real)0, (real)550, (real)400);
		l_drawcall.write_consts(1, flash_vs::viewport_offset, l_viewport_consts);

		flash_vs::shape_consts l_shape_consts;
		l_shape_consts.xform = r2x4
		(
			real4(_xform[0][0], _xform[0][1], _xform[0][2], 0),
			real4(_xform[1][0], _xform[1][1], _xform[1][2], 0)
		);
		l_shape_consts.color = _color;
		l_drawcall.write_consts(1, flash_vs::shape_offset, l_shape_consts);

		vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_memreader_ID);

		l_drawcall.set_start(l_memreader.size() / sizeof(short2));

		l_memreader.write(_points, _count * sizeof(short2));
	}
}
void renderer::end_render()
{
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
