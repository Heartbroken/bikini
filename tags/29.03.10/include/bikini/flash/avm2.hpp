/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct avm2 : avmplus::AvmCore {
	avm2();
	bool do_ABC(pointer _data, uint _size);
private:
	void interrupt(avmplus::MethodEnv *env);
	void stackOverflow(avmplus::MethodEnv *env);
	avmplus::Toplevel *m_toplevel_p;
};
