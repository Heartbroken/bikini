/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

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
	float4 l_pos = float4(_in.p / 20, 0, 1);
	l_pos.xy = (l_pos.xy - float2(400, 300)) / float2(800, 600);
	l_out.hpos = l_pos;
	l_out.c = float4(1, 1, 1, 1);
	return l_out;
}