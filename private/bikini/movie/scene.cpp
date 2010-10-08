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

bool scene::create()
{
	return true;
}
bool scene::update(real _dt)
{
	return super::update(_dt);
}
bool scene::render() const
{
	return true;
}

void scene::destroy()
{
	super::destroy();
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

} /* namespace movie ---------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
