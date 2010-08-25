/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// random number generator
/**	Each instance of random generates independent
	sequence of random numbers. The user can reproduce a sequence
	by saving and restoring the seed member
 */
struct random
{
	/// Maximum random value
	static const uint max = 32767;
	/// Random numbers sequence seed
	uint seed;
	/// Constructor
	inline random(uint _seed = 0);
	/// Returns integer numbers in range [0..max]
	inline uint get();
	/// Returns integer numbers in range [0.._max]. The result can't be greater than max
	inline uint get(uint _max);
	/// Returns integer numbers in range [_min.._max]. The result can't be greater than max + _min
	inline sint get(sint _min, sint _max);
	/// Returns real numbers in range [0.._max]. If _max is negative the result is 0
	inline real get(real _max);
	/// Returns real numbers in range [_min.._max]. If _max is less than _min the result is in range [_max.._min]
	inline real get(real _min, real _max);
};
extern random random_0;

#include "random.inl"
