// bikini.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

namespace bikini { /*----------------------------------------------------------------------------*/

bk::video g_video;
bk::vo::window::info g_vo_window_info;

bk::uint create_window(bk::uint _handle)
{
	bk::uint l_vo_window_ID = g_video.spawn(g_vo_window_info, (HWND)_handle);
	bk::uint l_vo_viewport_ID = g_video.get_<bk::vo::window>(l_vo_window_ID).viewport_ID(0);
	g_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_flags(bk::cf::color);
	bk::color l_color(bk::random_0.get(1.f), bk::random_0.get(1.f), bk::random_0.get(1.f));
	g_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_color(l_color);
	return l_vo_window_ID;
}
bool update(bk::real _dt)
{
	return g_video.update(_dt);
}

void create()
{
	g_video.create();
	bk::functor_<bk::uint, bk::uint> l_create_gui_view(&create_window);
	commands::add("CreateGuiView", l_create_gui_view);
	bk::functor_<bool, bk::real> l_update(&update);
	commands::add("Update", l_update);
}
void destroy()
{
	commands::remove("Update");
	commands::remove("CreateGuiView");
	g_video.destroy();
}

} // namespace bikini /*-------------------------------------------------------------------------*/