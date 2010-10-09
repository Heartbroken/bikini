/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk /*----------------------------------------------------------------------------------*/
{
namespace movie /*------------------------------------------------------------------------------*/
{

// camera

camera::camera(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform)
:
	sector::content(_info, _scene, _sector_ID, _xform)
{}

bool camera::render() const
{
	scene &l_scene = get_scene();

	if (l_scene.exists(sector_ID()))
	{
		sector &l_sector = l_scene.get_<sector>(sector_ID());
	}

	return true;
}

// camera::info

camera::info::info()
:
	sector::content::info(type::camera)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
