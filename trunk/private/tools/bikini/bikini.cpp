// bikini.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

namespace bikini { /*----------------------------------------------------------------------------*/

bk::video g_video;
bk::vo::window::info g_vo_window_info;
bk::ticker g_ticker(1.f / 30.f);

//
bk::vo::memreader::info g_vo_memreader_info;

bk::uint create_window(bk::handle _handle)
{
	bk::uint l_vo_window_ID = g_video.spawn(g_vo_window_info, (HWND)_handle);
	bk::uint l_vo_viewport_ID = g_video.get_<bk::vo::window>(l_vo_window_ID).viewport_ID(0);
	g_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_flags(bk::cf::color);
	bk::color l_color(bk::random_0.get(1.f), bk::random_0.get(1.f), bk::random_0.get(1.f));
	g_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_color(l_color);
	return l_vo_window_ID;
}
void destroy_window(bk::uint _ID)
{
	g_video.kill(_ID);
}
bool update()
{
	g_ticker.sync();

	static bk::rbig sl_time = bk::sys_time();

	bk::rbig l_newtime = bk::sys_time();
	bk::rbig l_dt = l_newtime - sl_time;
	sl_time = l_newtime;

	return g_video.update((bk::real)l_dt);
}

void create()
{
	g_video.create();
	bk::functor_<bk::uint, bk::handle> l_create_gui_view(&create_window);
	commands::add("CreateGuiView", l_create_gui_view);
	bk::functor_<void, bk::uint> l_destroy_gui_view(&destroy_window);
	commands::add("DestroyGuiView", l_destroy_gui_view);
	bk::functor_<bool> l_update(&update);
	commands::add("Update", l_update);
}
void destroy()
{
	commands::remove("Update");
	commands::remove("CreateGuiView");
	g_video.destroy();
}

} // namespace bikini /*-------------------------------------------------------------------------*/