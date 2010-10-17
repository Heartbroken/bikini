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

// decor

decor::decor(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform)
:
	sector::object(_info, _scene, _sector_ID, _xform)
{}

// decor::info

decor::info::info()
:
	sector::object::info(types::decor)
{}

} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
