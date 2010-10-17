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
	sector::object(_info, _scene, _sector_ID, _xform)
{}

bool camera::render(const context &_c) const
{
	m_last_frame = m_next_frame;
	m_next_frame.clear();

	context l_c = _c;
	l_c.camera_ID = ID();

	render(l_c, get_sector());

	for (uint_hashset::iterator l_it = m_last_frame.begin(); l_it != m_last_frame.end(); ++l_it)
	{
		uint l_object_ID = *l_it;
	}

	return true;
}
bool camera::render(const context &_c, const sector &_sector) const
{
	scene &l_scene = get_scene();

	for (uint i = 0, s = _sector.object_count(); i < s; ++i)
	{
		uint l_object_ID = _sector.object_ID(i);
		assert(l_scene.exists(l_object_ID));

		m_next_frame.insert(l_object_ID);

		uint_hashset::iterator l_it = m_last_frame.find(l_object_ID);

		if (l_it != m_last_frame.end())
		{
			m_last_frame.erase(l_object_ID);
			continue;
		}

		switch (l_scene.get(l_object_ID).type())
		{
		case types::portal : render(_c, l_scene.get_<portal>(l_object_ID)); break;
		case types::decor : render(_c, l_scene.get_<decor>(l_object_ID)); break;
		case types::actor : render(_c, l_scene.get_<actor>(l_object_ID)); break;
		}
	}

	return true;
}
bool camera::render(const context &_c, const portal &_portal) const
{
	scene &l_scene = get_scene();
	uint l_target_ID = _portal.target_ID();

	if (!l_scene.exists(l_target_ID)) return false;

	assert(l_scene.get(l_target_ID).type() == types::portal);
	const portal &l_target = l_scene.get_<portal>(l_target_ID);

	context l_c = _c;
	l_c.portal_xform *= l_target.xform();

	render(l_c, l_target.get_sector());

	return true;
}
bool camera::render(const context &_c, const decor &_decor) const
{
	return true;
}
bool camera::render(const context &_c, const actor &_actor) const
{
	return true;
}

// camera::info

camera::info::info()
:
	sector::object::info(types::camera)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
