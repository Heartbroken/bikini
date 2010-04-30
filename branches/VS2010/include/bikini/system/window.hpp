/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct window
{
	window();
	virtual ~window();
	bool create(uint _width, uint _height, HICON _icon = 0);
	HWND get_handle();
	void show(bool _yes = true);
	void hide();
	void set_caption(const wstring &_s);
	void set_caption(const astring &_s);
	void set_size(uint _width, uint _height);
	uint width() const;
	uint height() const;
	bool update(real _dt);
	bool active() const;
	void destroy();

private:
	HWND m_handle;
	static LRESULT CALLBACK _proc(HWND _handle, UINT _message, WPARAM _wparam, LPARAM _lparam);
	LRESULT m_proc(UINT _message, WPARAM _wparam, LPARAM _lparam);
};
