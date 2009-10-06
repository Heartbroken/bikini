/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include <bikini/system/shader.shh>

#include <bikini/system/viewport.shh>
#include "shape.shh"

#if !defined(__cplusplus) /*---------------------------------------------------------------------*/

struct input
{
	float2 p : POSITION;
};

struct output
{
	float4 hpos : POSITION;
	float4 c : COLOR0;
};

output main(input _in)
{
	output l_out = (output)0;
	
	float3x3 l_xform =
	{
		shape.xform._11, shape.xform._12, 0,
		shape.xform._21, shape.xform._22, 0,
		shape.xform._31, shape.xform._32, 1
	};
	
	float2 l_pos = mul(float3(_in.p, 1), l_xform);
	
	l_pos = l_pos + viewport.area.xy;
	l_pos = 2 * (l_pos - viewport.area.zw / 2) / viewport.area.zw;
	l_pos.y = -l_pos.y;

	l_out.hpos = float4(l_pos, 0, 1);
	
	l_out.c = shape.color;
	
	return l_out;
}

#endif /* !defined(__cplusplus) -----------------------------------------------------------------*/
