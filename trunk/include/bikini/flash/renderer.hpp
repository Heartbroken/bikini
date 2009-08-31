/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct renderer
{
	virtual ~renderer() {}
	virtual void draw_line(const real2 &_s, const real2 &_e, const color &_c, real _width) = 0;
	virtual void draw_tris(const real2 *_points, const uint *_tris, uint _count, const color &_c, const r3x3 &_position) = 0;
};
