/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct window {
	window(video &_video);
	virtual ~window();
//#	if defined(XBOX)
//	bool create();
//#	elif defined(WIN32)
	bool create(uint _width, uint _height, bool _fullscreen = false, HICON _icon = 0);
	bool create(HWND _handle);
	HWND get_handle();
	void show(bool _yes = true);
	void hide();
	void set_caption(const wstring &_s);
	void set_caption(const astring &_s);
	void set_size(uint _width, uint _height);
//#	endif
	uint width() const;
	uint height() const;
	bool update(real _dt);
	bool active() const;
	bool clear(uint _flags = cf::all, const color &_color = black, real _depth = 1.f, uint _stencil = 0) const;
	bool begin() const;
	bool set_scissor(uint _x0, uint _y0, uint _x1, uint _y1);
	bool remove_scissor();
	bool draw_line(sint _x0, sint _y0, sint _x1, sint _y1, const color &_c = white, uint _width = 1);
	void draw_line(const real2 &_s, const real2 &_e, const color &_c, real _width);
	void draw_tris(const real2 *_points, const uint *_tris, uint _count, const color &_c = white, const r3x3 &_position = r3x3_1);
	bool draw_rect(sint _x0, sint _y0, sint _x1, sint _y1, const color &_c = white);
	bool flush_drawings();
	bool end() const;
	bool present() const;
	void destroy();
	//
	virtual void on_mouse_down(const sint2 &_position, uint _button) {}
	virtual void on_mouse_up(const sint2 &_position, uint _button) {}
	virtual void on_mouse_move(const sint2 &_position) {}
	//
protected:
private:
#	if defined(WIN32)
	HWND m_handle;
	WNDPROC m_oldproc;
	static LRESULT CALLBACK window_proc(HWND _handle, UINT _message, WPARAM _wparam, LPARAM _lparam);
	LRESULT m_proc(UINT _message, WPARAM _wparam, LPARAM _lparam);
#	endif
	thread::section m_lock;
	video &m_video;
	//struct screen { vr::screen::info info; uint ID; } m_screen;
	//struct vbuffer { vr::vbuffer::info info; uint ID, def_ID; handle data; uint start, used; } m_vbuffer;
	//struct vformat { vr::vformat::info info; uint ID, def_ID; } m_vformat;
	//struct rstates { vr::rstates::info info; uint ID, def_ID; } m_rstates;
	//struct vshader { vr::vshader::info info; uint ID, def_ID; } m_vshader;
	//struct pshader { vr::pshader::info info; uint ID, def_ID; } m_pshader;
	struct scissor { uint x0, y0, x1, y1; } m_scissor;
	typedef matrix_<1, 3, f32> f1x3;
	typedef matrix_<1, 4, f32> f1x4;
	typedef matrix_<4, 4, f32> f4x4;
	struct vertex { f1x3 p; u32 c; };
	bool m_add_tris(uint _count, vertex *_v_p);
	bool m_flush_tris();
};
