/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

void add_start_cap(const short2 &_p0, const short2 &_p1, real _width, array_<short2> &_mesh)
{
	real2 l_p0(_p0.x, _p0.y), l_p1(_p1.x, _p1.y);
	real2 l_side = normalize(cross(l_p1 - l_p0)) * _width * r_05;
	real2 l_s0 = l_p0 - l_side, l_s1 = l_p0 + l_side;

	_mesh.push_back(short2((short)l_s0.x, (short)l_s0.y));
	_mesh.push_back(short2((short)l_s1.x, (short)l_s1.y));
}
void add_end_cap(const short2 &_p0, const short2 &_p1, real _width, array_<short2> &_mesh)
{
	real2 l_p0(_p0.x, _p0.y), l_p1(_p1.x, _p1.y);
	real2 l_side = normalize(cross(l_p1 - l_p0)) * _width * r_05;
	real2 l_s0 = l_p0 - l_side, l_s1 = l_p0 + l_side;

	_mesh.push_back(short2((short)l_s0.x, (short)l_s0.y));
	_mesh.push_back(short2((short)l_s1.x, (short)l_s1.y));
}
void close_line(array_<short2> &_mesh)
{
	_mesh.push_back(_mesh[0]);
	_mesh.push_back(_mesh[1]);
}
void add_joint(const short2 &_p0, const short2 &_p1, const short2 &_p2, real _width, array_<short2> &_mesh)
{
	real2 l_p0(_p0.x, _p0.y);
	real2 l_p1(_p1.x, _p1.y);
	real2 l_p2(_p2.x, _p2.y);
	real2 l_point = l_p1;
	real2 l_dir0 = l_p1 - l_p0;
	real2 l_dir1 = l_p2 - l_p1;
	real2 l_normal0 = normalize(cross(l_dir0)) * _width * r_05;
	real2 l_normal1 = normalize(cross(l_dir1)) * _width * r_05;
	real2 l_p00 = l_point - l_normal0, l_p01 = l_point + l_normal0;
	real2 l_p10 = l_point - l_normal1, l_p11 = l_point + l_normal1;

	//real l_sin = cross(l_dir0, l_dir1);
	//if (l_sin > 0)
	//{
	//	real2 l_p = (l_p00 + l_p01) * r_05 - l_point;
	//	l_p
	//}
	//else if (l_sin < 0)
	//{
	//}

	_mesh.push_back(short2((short)l_p00.x, (short)l_p00.y));
	_mesh.push_back(short2((short)l_p01.x, (short)l_p01.y));
	_mesh.push_back(short2((short)l_p10.x, (short)l_p10.y));
	_mesh.push_back(short2((short)l_p11.x, (short)l_p11.y));
}
void build_line_mesh(const short2 _points[], uint _count, real _width, array_<short2> &_mesh)
{
	if (_count < 2) return;

	bool l_closed = (_points[0] == _points[_count - 1]);

	if (l_closed)
		add_joint(_points[_count - 2], _points[0], _points[1], _width, _mesh);
	else
		add_start_cap(_points[0], _points[1], _width, _mesh);

	for (uint i = 0; i < _count - 2; ++i)
		add_joint(_points[i], _points[i + 1], _points[i + 2], _width, _mesh);

	if (l_closed)
		close_line(_mesh);
	else
		add_end_cap(_points[_count - 2], _points[_count - 1], _width, _mesh);
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
