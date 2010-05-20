/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

extern video::rendering* new_rendering_D3D11(video &_video);
extern video::rendering* new_rendering_D3D9(video &_video);

// video

video::rendering& video::new_rendering(video &_video)
{
	video::rendering *l_rendering_p = new_rendering_D3D11(_video);
	if (l_rendering_p == 0) l_rendering_p = new_rendering_D3D9(_video);

	return *l_rendering_p;
}

} /* namespace bk -------------------------------------------------------------------------------*/
