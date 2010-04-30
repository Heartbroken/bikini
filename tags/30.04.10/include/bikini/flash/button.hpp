/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct button : player::object {
	struct info : player::object::info {
		typedef button object;
		info(swfstream &_s, tag::type _type);
	private:
		void m_read_buttonrecords(swfstream &_s, tag::type _type);
		void m_read_actionrecords(swfstream &_s, tag::type _type);
		void m_read_buttoncondactions(swfstream &_s);
	};
	button(const info &_info, player &_player);
private:
	uint m_movie_ID;
	uint m_curr_state;
	r3x3 m_position;
	array_<uint> m_objects;
};
