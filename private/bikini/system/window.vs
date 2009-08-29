/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

struct input {
	float3 p : POSITION;
	float4 c : COLOR0;
};

struct output {
	float4 hpos : POSITION;
	float4 c : COLOR0;
};

output main(input _in) {
	output l_out = (output)0;
	l_out.hpos = float4(_in.p, 1);
	l_out.c = _in.c;
	return l_out;
}