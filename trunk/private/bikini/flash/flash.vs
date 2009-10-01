/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include <bikini/system/shader.shh>

#include <bikini/system/next_c_register.shh>
#define used_c_registers 4

float4x4 xform : register(first_c_register) =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

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
	float4 l_pos = mul(xform, float4(_in.p / 20, 0, 1));
//	l_pos.xy = (l_pos.xy - float2(400, 300)) / float2(800, 600);
	l_pos.xy = (l_pos.xy - current_viewport.area.zw / 2) / current_viewport.area.zw;
	l_out.hpos = l_pos;
	l_out.c = float4(1, 1, 1, 1);
	return l_out;
}