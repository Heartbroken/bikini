/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// button

button::button(const info &_info, player &_player) :
	player::object(_info, _player)
{}

// button::info

button::info::info(swfstream &_s, tag::type _type) : player::object::info(ot::button) {
	assert(_type == tag::DefineButton || _type == tag::DefineButton2);
	if(_type == tag::DefineButton2) {
		uint l_reserved = _s.UB(7);
		assert(l_reserved == 0);
		uint l_menu = _s.UB(1);
		uint l_actionoffset = _s.UI16();
	}
	m_read_buttonrecords(_s, _type);
	if(_type == tag::DefineButton2) {
		m_read_buttoncondactions(_s);
	}
}
void button::info::m_read_buttonrecords(swfstream &_s, tag::type _type) {
	enum {
		state_up		= 1<<0,
		state_over		= 1<<1,
		state_down		= 1<<2,
		state_hit		= 1<<3,
		has_filterlist	= 1<<4,
		has_blendmode	= 1<<5,
	};
	while(true) {
		uint l_flags = _s.UI8();
		if(l_flags == 0) break;
		uint l_character_ID = _s.UI16();
		uint l_placedepth = _s.UI16();
		r3x3 l_placematrix = _s.MATRIX();
		if(_type == tag::DefineButton2) {
			cxform l_cxform = _s.CXFORMWITHALPHA();
			if(l_flags&has_filterlist) {
				uint l_count = _s.UI8();
				assert(l_count == 0); // @@@ not supported yet
			}
			if(l_flags&has_blendmode) uint l_blendmode = _s.UI8();
		}
	}
}
void button::info::m_read_actionrecords(swfstream &_s, tag::type _type) {
}
void button::info::m_read_buttoncondactions(swfstream &_s) {
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
