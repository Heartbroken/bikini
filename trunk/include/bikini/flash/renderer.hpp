/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct renderer
{
	inline uint viewport_ID() const { m_viewport_ID; }
	inline void set_viewport_ID(uint _viewport_ID) { m_viewport_ID = _viewport_ID; }

	renderer(video &_video);
	~renderer();
	bool create();
	void destroy();

	uint create_texture(uint _format, pointer _data, uint _width, uint _height, uint _pitch);
	void destroy_texture(uint _ID);
	bool begin_render(const color &_background, const rect &_viewport);
	void set_xform(const xform &_xform);
	void set_color(const color &_color);
	void set_texture(uint _ID, const xform &_txform);
	void draw_tristrip(const short2* _points, uint _count);
	void end_render();

private:
	video &m_video;
	uint m_viewport_ID;
	vo::vformat::info m_vformat;
	uint m_vformat_ID;
	vo::memreader::info m_memreader;
	uint m_memreader_ID;
	vo::vbuffer::info m_vbuffer;
	uint m_vbuffer_ID;
	vo::vshader::info m_vshader;
	uint m_vshader_ID;
	vo::pshader::info m_pshader;
	uint m_pshader_ID;
	vo::vbufset::info m_vbufset;
	uint m_vbufset_ID;
	vo::states::info m_states;
	uint m_states_ID;
	vo::texture::info m_texture;
	vo::texset::info m_texset;
	struct texture { uint texture_ID, width, height, memreader_ID, texset_ID; };
	pool_<texture> m_textures;
	uint m_texset_ID;
	uint m_deftexset_ID;
};
