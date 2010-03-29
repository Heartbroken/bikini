/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct sensor
{
	sensor();

	bool create(HWND _window);
	void destroy();

	uint key_count() const;
	void key_state(uint _i, uint &_code, bool &_state) const;
	void reset_keys();

	void mouse_state(short2 &_point, bool &_button) const;

	void set_hittest(const hittest &_hittest);

	struct _private; _private * m_private;
};