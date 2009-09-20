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

private:
	video &m_video;
	uint m_viewport_ID;
};
