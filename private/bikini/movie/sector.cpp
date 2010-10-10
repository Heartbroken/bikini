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

void sector::add_content(const content &_content)
{
	uint_array::iterator l_it = std::find(m_content.begin(), m_content.end(), _content.ID());
	assert(l_it == m_content.end());

	m_content.push_back(_content.ID());
}
void sector::remove_content(const content &_content)
{
	uint_array::iterator l_it = std::find(m_content.begin(), m_content.end(), _content.ID());
	assert(l_it != m_content.end());

	m_content.erase(l_it);
}
void sector::kill_all_content()
{
	for (uint i = 0, s = m_content.size(); i < s; ++i)
	{
		uint l_ID = m_content[i];
		get_scene().kill(l_ID);
	}

	m_content.resize(0);
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
