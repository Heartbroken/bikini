/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// movie

movie::movie(const info &_info, player &_player)
:
	player::object(_info, _player), m_handle(0)
{
	gameswf::movie_definition &l_movie_def = *(gameswf::movie_definition*)_info.get_handle();
	gameswf::root &l_movie = * l_movie_def.create_instance();
	l_movie.add_ref();
	m_handle = &l_movie;
}
movie::~movie()
{
	((gameswf::root*)m_handle)->drop_ref();
}
bool movie::update(real _dt)
{
	gameswf::root &l_movie = *(gameswf::root*)m_handle;
	l_movie.advance((float)_dt);
	return true;
}
bool movie::render() const
{
	gameswf::root &l_movie = *(gameswf::root*)m_handle;
	l_movie.display();
	return true;
}

// movie::info

movie::info::info(handle _handle) : player::object::info(ot::movie), m_handle(_handle)
{}
movie::info::~info()
{}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
