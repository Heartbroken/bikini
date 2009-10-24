/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

//device

bool device::update(real _dt)
{
	//for(uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID)) {
	//	object &l_object = get<object>(l_ID);
	//	if(!l_object.valid() && !l_object.create()) kill(l_ID);
	//}
	return super::update(_dt);
}

// device::object

device::object::object(const info &_info, device &_device) :
	manager::object(_info, _device),
	m_version(infinity)
{}
device::object::~object() {
	//if(valid()) {
	//	std::cerr << "ERROR: Destroy device object before deleting\n";
	//	assert(m_version == infinity);
	//}
}
//bool device::object::create() {
//	update_version();
//	return true;
//}
//void device::object::destroy() {
//	set_invalid();
//}

// device::object::info

device::object::info::info(uint _type) :
	manager::object::info(_type)
{}

} /* namespace bk -------------------------------------------------------------------------------*/
