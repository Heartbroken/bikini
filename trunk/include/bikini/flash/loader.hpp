/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct loader {
	virtual ~loader() {}
	virtual uint open(const wchar* _path) = 0;
	virtual bool good(uint _ID) const = 0;
	virtual uint seek(uint _ID, sint _offset = 0, uint _from = 1) = 0;
	virtual uint read(uint _ID, handle _buffer, uint _length) = 0;
	virtual void close(uint _ID) = 0;
};
