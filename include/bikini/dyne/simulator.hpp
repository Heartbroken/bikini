/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2011 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct simulator
{
	typedef make_typelist_<
		structure
	> types;

	simulator();

	bool create();
	void destroy();

private:
};

DECLARE_UTEST(dyne_simulator);