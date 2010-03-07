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

private:
	struct key { uint code; bool state; };
	array_<key> m_keys;
	void add_key_state(uint _code, bool _state) { key l_key = { _code, _state }; m_keys.push_back(l_key); }
	struct mouse { short2 point; bool button; };
	mouse m_mouse;
	void set_mouse_state(const short2 &_point, bool _button) { m_mouse.point = _point; m_mouse.button = _button; }
	hittest m_hittest;
	bool do_hittest(const short2 &_point);
};