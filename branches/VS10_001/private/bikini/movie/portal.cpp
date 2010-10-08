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

// portal

portal::portal(const info &_info, scene &_scene, uint _parent_ID, const r4x4 &_xform)
:
	sector::content(_info, _scene, _parent_ID, _xform)
{}

// portal::info

portal::info::info()
:
	sector::content::info(type::portal)
{}

} /* namespace movie ---------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/