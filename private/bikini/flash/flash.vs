/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
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
	float2 tex0 : TEXCOORD0;
	float4 c : COLOR0;
	float4 hpos : SV_POSITION;
};

output main(input _in)
{
	output l_out = (output)0;

	// position
	float2 l_pos = mul(float3(_in.p, 1), shape.xform);
	
	l_pos = l_pos + viewport.area.xy;
	l_pos = 2 * (l_pos - viewport.area.zw / 2) / viewport.area.zw;
	l_pos.y = -l_pos.y;

	l_out.hpos = float4(l_pos, 0, 1);

	// texture coords
	l_out.tex0 = mul(float3(_in.p, 1), shape.txform) * shape.tex_scale;
	
	// color
	l_out.c = shape.color;
	
	return l_out;
}

#endif /* !defined(__cplusplus) -----------------------------------------------------------------*/
