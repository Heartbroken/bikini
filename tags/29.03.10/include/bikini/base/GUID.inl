/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// create random GUID
inline GUID random_GUID(random &_random) {
	GUID l_guid;
	l_guid.Data1 = (unsigned long)((_random.get() << 16) | _random.get());
	l_guid.Data2 = (unsigned short)_random.get();
	l_guid.Data3 = (unsigned short)(0x4000 | (0x0fff & _random.get()));
	for(uint i = 0; i < 8; ++i) l_guid.Data4[i] = (unsigned char)_random.get();
	return l_guid;
}
