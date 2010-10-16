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

// sector

sector::sector(const info &_info, scene &_scene)
:
	scene::object(_info, _scene)
{}
sector::~sector()
{
	kill_all_content();
}

bool sector::render(const context &_c) const
{
	scene &l_scene = get_scene();

	assert(l_scene.exists(_c.camera_ID));
	camera &l_camera = l_scene.get_<camera>(_c.camera_ID);

	for (uint i = 0, s = m_decors.size(); i < s; ++i)
	{
		uint l_decor_ID = m_decors[i];
		assert(l_scene.exists(l_decor_ID) && l_scene.get(l_decor_ID).type() == types::decor);
		const decor &l_decor = l_scene.get_<decor>(l_decor_ID);

		l_camera.render(_c, l_decor);
	}

	for (uint i = 0, s = m_actors.size(); i < s; ++i)
	{
		uint l_actor_ID = m_actors[i];
		assert(l_scene.exists(l_actor_ID) && l_scene.get(l_actor_ID).type() == types::actor);
		const actor &l_actor = l_scene.get_<actor>(l_actor_ID);

		l_camera.render(_c, l_actor);
	}

	for (uint i = 0, s = m_portals.size(); i < s; ++i)
	{
		uint l_portal_ID = m_portals[i];
		assert(l_scene.exists(l_portal_ID) && l_scene.get(l_portal_ID).type() == types::portal);
		const portal &l_portal = l_scene.get_<portal>(l_portal_ID);

		l_camera.render(_c, l_portal);
	}

	return true;
}

uint_array& sector::get_content_array(uint _type)
{
	switch (_type)
	{
	case types::camera : return m_cameras;
	case types::portal : return m_portals;
	case types::decor : return m_decors;
	case types::actor : return m_actors;
	}

	assert(0 && "ERROR: Bad content type");

	return *(uint_array*)0;
}
void sector::add_content(const content &_content)
{
	uint_array &l_content = get_content_array(_content.type());
	uint_array::iterator l_it = std::find(l_content.begin(), l_content.end(), _content.ID());
	assert(l_it == l_content.end());

	l_content.push_back(_content.ID());
}
void sector::remove_content(const content &_content)
{
	uint_array &l_content = get_content_array(_content.type());
	uint_array::iterator l_it = std::find(l_content.begin(), l_content.end(), _content.ID());
	assert(l_it != l_content.end());

	l_content.erase(l_it);
}
void sector::kill_all_content()
{
	uint l_types[] = { types::camera, types::portal, types::decor, types::actor };

	for (uint i = 0; i < sizeof(l_types) / sizeof(l_types[0]); ++i)
	{
		uint_array &l_content = get_content_array(l_types[i]);

		for (uint i = 0, s = l_content.size(); i < s; ++i)
		{
			uint l_ID = l_content[i];
			get_scene().kill(l_ID);
		}

		l_content.resize(0);
	}
}

// sector::info

sector::info::info()
:
	scene::object::info(types::sector)
{}

// sector::content

sector::content::content(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform)
:
	scene::object(_info, _scene),
	m_sector_ID(_sector_ID),
	m_xform(_xform)
{
	get_sector().add_content(*this);
}
sector::content::~content()
{
	get_sector().remove_content(*this);
}

sector& sector::content::get_sector() const
{
	assert(get_scene().exists(sector_ID()));
	assert(get_scene().get(sector_ID()).type() == types::sector);

	return get_scene().get_<sector>(sector_ID());
}

// sector::content::info

sector::content::info::info(uint _type)
:
	scene::object::info(_type)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
