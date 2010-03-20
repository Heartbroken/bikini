/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace flash_vs
{
#	include "flash.vs"
#	include compiled_shader(flash.vs)
	static viewport_consts viewport;
	static shape_consts shape;
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
//	D3DRS_FILLMODE, D3DFILL_WIREFRAME,
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

	m_texset_ID = m_deftexset_ID = create_texture(video::tf::a8r8g8b8, &bad_ID, 1, 1, 4);

	return true;
}
void renderer::destroy()
{
	destroy_texture(m_deftexset_ID);

	for (uint l_ID = m_textures.first_ID(); l_ID != bad_ID; l_ID = m_textures.next_ID(l_ID))
	{
		destroy_texture(l_ID);
	}
	for (uint l_ID = m_meshes.first_ID(); l_ID != bad_ID; l_ID = m_meshes.next_ID(l_ID))
	{
		destroy_mesh(l_ID);
	}

	m_video.kill(m_vformat_ID);
	m_video.kill(m_memreader_ID);
	m_video.kill(m_vbuffer_ID);
	m_video.kill(m_vshader_ID);
	m_video.kill(m_pshader_ID);
	m_video.kill(m_vbufset_ID);
	m_video.kill(m_states_ID);
}
uint renderer::create_texture(uint _format, pointer _data, uint _width, uint _height, uint _pitch)
{
	texture l_texture;

	l_texture.width = _width;
	l_texture.height = _height;

	l_texture.texture_ID = m_video.spawn(m_texture);

	l_texture.texset_ID = m_video.spawn(m_texset);
	m_video.get_<vo::texset>(l_texture.texset_ID).set_texture(0, l_texture.texture_ID);

	l_texture.memreader_ID = m_video.spawn(m_memreader);
	m_video.get_<vo::texture>(l_texture.texture_ID).set_source(l_texture.memreader_ID);

	vo::memreader &l_memreader = m_video.get_<vo::memreader>(l_texture.memreader_ID);
	l_memreader.write(&_format, sizeof(_format));
	sint2 l_size(_width, _height); l_memreader.write(&l_size, sizeof(l_size));
	l_memreader.write(&_pitch, sizeof(_pitch));
	l_memreader.write(_data, _height * _pitch);

	return m_textures.add(l_texture);
}
void renderer::destroy_texture(uint _ID)
{
	if (!m_textures.exists(_ID)) return;

	texture &l_texture = m_textures.get(_ID);
	m_video.kill(l_texture.texset_ID);
	m_video.kill(l_texture.memreader_ID);
	m_video.kill(l_texture.texture_ID);

	m_textures.remove(_ID);
}
uint renderer::create_mesh(const short2 _points[], uint _count)
{
	mesh l_mesh;

	l_mesh.size = _count - 2;

	l_mesh.memreader_ID = m_video.spawn(m_memreader);
	m_video.get_<vo::memreader>(l_mesh.memreader_ID).write(_points, _count * sizeof(short2));

	l_mesh.vbuffer_ID = m_video.spawn(m_vbuffer);
	m_video.get_<vo::vbuffer>(l_mesh.vbuffer_ID).set_source(l_mesh.memreader_ID);

	l_mesh.vbufset_ID = m_video.spawn(m_vbufset);
	m_video.get_<vo::vbufset>(l_mesh.vbufset_ID).set_vformat(m_vformat_ID);
	m_video.get_<vo::vbufset>(l_mesh.vbufset_ID).set_vbuffer(0, l_mesh.vbuffer_ID, 0, 4);

	return m_meshes.add(l_mesh);
}
void renderer::destroy_mesh(uint _ID)
{
	if (!m_meshes.exists(_ID)) return;

	mesh &l_mesh = m_meshes.get(_ID);
	m_video.kill(l_mesh.vbufset_ID);
	m_video.kill(l_mesh.memreader_ID);
	m_video.kill(l_mesh.vbuffer_ID);

	m_meshes.remove(_ID);
}
bool renderer::begin_render(const color &_background, const rect &_viewport)
{
	if (m_video.exists(m_viewport_ID))
	{
		vo::viewport &l_viewport = m_video.get_<vo::viewport>(m_viewport_ID);

		l_viewport.set_clear_flags(cf::color);
		l_viewport.set_clear_color(_background);
		l_viewport.clear();

		flash_vs::viewport.area = float4((float)_viewport.min().x, (float)_viewport.min().y, (float)_viewport.size().x, (float)_viewport.size().y);

		vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_memreader_ID);
		l_memreader.clear();
	}

	return true;
}
void renderer::set_xform(const xform &_xform)
{
	flash_vs::shape.xform = float4x2
	(
		_xform[0][0], _xform[0][1], _xform[0][2] - 10.f, 0,
		_xform[1][0], _xform[1][1], _xform[1][2] - 10.f, 0
	);
}
void renderer::set_color(const color &_color)
{
	flash_vs::shape.color = _color;
}
void renderer::set_texture(uint _ID, const xform &_txform)
{
	if (m_textures.exists(_ID))
	{
		texture &l_texture = m_textures.get(_ID);

		m_texset_ID = l_texture.texset_ID;

		flash_vs::shape.txform = float4x2
		(
			_txform[0][0], _txform[0][1], _txform[0][2], 0,
			_txform[1][0], _txform[1][1], _txform[1][2], 0
		);

		flash_vs::shape.tex_scale = float4
		(
			 float(1) / float(l_texture.width), float(1) / float(l_texture.height), 0, 0
		);
	}
	else
	{
		m_texset_ID = m_textures.get(m_deftexset_ID).texset_ID;
	}
}
void renderer::draw_tristrip(const short2* _points, uint _count)
{
	if (m_video.exists(m_viewport_ID))
	{
		vo::viewport &l_viewport = m_video.get_<vo::viewport>(m_viewport_ID);

		vo::drawcall &l_drawcall = l_viewport.add_drawcall();
		l_drawcall.set_states(m_states_ID);
		l_drawcall.set_vbufset(m_vbufset_ID);
		l_drawcall.set_shaders(m_vshader_ID, m_pshader_ID);
		l_drawcall.set_size(_count - 2);

		vo::memreader &l_memreader = m_video.get_<vo::memreader>(m_memreader_ID);
		l_drawcall.set_start(l_memreader.size() / sizeof(short2));
		l_memreader.write(_points, _count * sizeof(short2));

		l_drawcall.write_consts(1, flash_vs::viewport_offset, flash_vs::viewport);
		l_drawcall.write_consts(1, flash_vs::shape_offset, flash_vs::shape);

		l_drawcall.set_texset(m_texset_ID);
	}
}
void renderer::draw_mesh(uint _ID)
{
	if (m_video.exists(m_viewport_ID) && m_meshes.exists(_ID))
	{
		vo::viewport &l_viewport = m_video.get_<vo::viewport>(m_viewport_ID);
		mesh &l_mesh = m_meshes.get(_ID);

		vo::drawcall &l_drawcall = l_viewport.add_drawcall();
		l_drawcall.set_states(m_states_ID);
		l_drawcall.set_vbufset(l_mesh.vbufset_ID);
		l_drawcall.set_shaders(m_vshader_ID, m_pshader_ID);
		l_drawcall.set_size(l_mesh.size);

		l_drawcall.write_consts(1, flash_vs::viewport_offset, flash_vs::viewport);
		l_drawcall.write_consts(1, flash_vs::shape_offset, flash_vs::shape);

		l_drawcall.set_texset(m_texset_ID);
	}
}
void renderer::end_render()
{
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
