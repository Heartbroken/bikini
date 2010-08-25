/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct movie : player::object
{
	struct info : player::object::info
	{
		typedef movie object;
		inline handle get_handle() const;
		info(handle _handle);
		~info();
	private:
		handle m_handle;
	};
	movie(const info &_info, player &_player);
	~movie();
	bool update(real _dt);
	bool render() const;

private:
	handle m_handle;
};

#include "movie.inl"