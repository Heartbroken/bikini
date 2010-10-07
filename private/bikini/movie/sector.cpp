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

// sector::info

sector::info::info()
:
	scene::object::info(type::sector)
{}

// sector::content

sector::content::content(const info &_info, scene &_scene, uint _parent_ID, const r4x4 &_xform)
:
	scene::object(_info, _scene),
	m_parent_ID(_parent_ID),
	m_xform(_xform)
{}

// sector::content::info

sector::content::info::info(uint _type)
:
	scene::object::info(_type)
{}

} /* namespace action ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
