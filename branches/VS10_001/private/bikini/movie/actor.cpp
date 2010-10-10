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

// actor

actor::actor(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform)
:
	sector::content(_info, _scene, _sector_ID, _xform)
{}

// actor::info

actor::info::info()
:
	sector::content::info(types::actor)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
