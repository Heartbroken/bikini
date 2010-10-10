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

bool camera::render() const
{
	scene &l_scene = get_scene();
	sector &l_sector = get_sector();

	for (uint i = 0, s = l_sector.object_count(); i < s; ++i)
	{
		uint l_object_ID = l_sector.get_object_ID(i);
		assert(l_scene.exists(l_object_ID));

		content &l_object = l_scene.get_<content>(l_object_ID);

		switch (l_object.type())
		{
			case types::decor :
			{
				break;
			}
			case types::actor :
			{
				break;
			}
		}
	}

	return true;
}

// camera::info

camera::info::info()
:
	sector::content::info(types::camera)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
