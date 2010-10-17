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
	while (!m_objects.empty())
	{
		get_scene().kill(m_objects.back());
	}
}

void sector::add_object(const object &_object)
{
	uint_array::iterator l_it = std::find(m_objects.begin(), m_objects.end(), _object.ID());
	assert(l_it == m_objects.end());

	m_objects.push_back(_object.ID());
}
void sector::remove_object(const object &_object)
{
	uint_array::iterator l_it = std::find(m_objects.begin(), m_objects.end(), _object.ID());
	assert(l_it != m_objects.end());

	m_objects.erase(l_it);
}

// sector::info

sector::info::info()
:
	scene::object::info(types::sector)
{}

// sector::object

sector::object::object(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform)
:
	scene::object(_info, _scene),
	m_sector_ID(_sector_ID),
	m_xform(_xform)
{
	get_sector().add_object(*this);
}
sector::object::~object()
{
	get_sector().remove_object(*this);
}

sector& sector::object::get_sector() const
{
	assert(get_scene().exists(sector_ID()));
	assert(get_scene().get(sector_ID()).type() == types::sector);

	return get_scene().get_<sector>(sector_ID());
}

// sector::content::info

sector::object::info::info(uint _type)
:
	scene::object::info(_type)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
