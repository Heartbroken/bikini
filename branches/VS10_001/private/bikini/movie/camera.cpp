/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk /*----------------------------------------------------------------------------------*/
{
namespace movie /*-------------------------------------------------------------------------------*/
{

// camera

camera::camera(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform)
:
	sector::content(_info, _scene, _sector_ID, _xform)
{}

bool camera::render(const context &_c) const
{
	context l_c = _c;
	l_c.camera_ID = ID();

	return get_sector().render(l_c);
}
bool camera::render(const context &_c, const decor &_decor) const
{
	return true;
}
bool camera::render(const context &_c, const actor &_actor) const
{
	return true;
}
bool camera::render(const context &_c, const portal &_portal) const
{
	return true;
}

// camera::info

camera::info::info()
:
	sector::content::info(types::camera)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
