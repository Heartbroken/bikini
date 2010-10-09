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

// scene

static
const sector::info& scene_default_sector()
{
	static sector::info sl_sector_info;
	return sl_sector_info;
}

static
const camera::info& scene_default_camera()
{
	static camera::info sl_camera_info;
	return sl_camera_info;
}

scene::scene()
:
	m_default_sector_ID(bad_ID),
	m_default_camera_ID(bad_ID),
	m_active_camera_ID(bad_ID)
{}

bool scene::create()
{
	m_default_sector_ID = spawn(scene_default_sector());
	m_default_camera_ID = spawn(scene_default_camera(), m_default_sector_ID, r4x4_1);

	set_active_camera_ID(m_default_camera_ID);

	return true;
}
bool scene::update(real _dt)
{
	return super::update(_dt);
}
bool scene::render() const
{
	if (exists(active_camera_ID()))
	{
		camera &l_camera = get_<camera>(active_camera_ID());
	}

	return true;
}
void scene::destroy()
{
	super::destroy();

	m_default_sector_ID = m_default_camera_ID = m_active_camera_ID = bad_ID;
}

// scene::object

scene::object::object(const info &_info, scene &_scene)
:
	bk::manager::object(_info, _scene)
{}

// scene::object::info

scene::object::info::info(uint _type)
:
	bk::manager::object::info(_type)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
