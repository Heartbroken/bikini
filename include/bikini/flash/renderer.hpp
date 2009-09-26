/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
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

	bool begin_render();
	void draw_tristrip(const short2* _points, uint _count);
	void end_render();

private:
	video &m_video;
	uint m_viewport_ID;
	vo::vformat::info m_vo_vformat;
	uint m_vo_vformat_ID;
	vo::memreader::info m_vo_memreader;
	uint m_vo_memreader_ID;
};
