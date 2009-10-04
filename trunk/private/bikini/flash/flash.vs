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
	
//	float4 l_pos = float4(_in.p / 20, 0, 1);
//	float4 l_pos = mul(shape.xform, float4(_in.p / 20, 0, 1));
	float4 l_pos = float4(_in.p.xy / 20, 0, 1);
	
	l_pos.xy = mul(shape.xform, l_pos.xy);
//	l_pos.xy = mul(l_pos.xy, shape.xform);
	
	l_pos.xy = (l_pos.xy - viewport.area.zw / 2) / viewport.area.zw;
	l_pos.y = -l_pos.y;
	
	l_out.hpos = l_pos;
	
	l_out.c = shape.color;
	
	return l_out;
}

#endif /* !defined(__cplusplus) -----------------------------------------------------------------*/
