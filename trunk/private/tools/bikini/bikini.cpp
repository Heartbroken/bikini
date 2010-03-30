// bikini.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

namespace bikini { /*----------------------------------------------------------------------------*/

bk::video g_video;
bk::vo::window::info g_vo_window_info;
bk::ticker g_ticker(1.f / 60.f);

bk::uint create_window(bk::handle _handle)
{
	bk::uint l_vo_window_ID = g_video.spawn(g_vo_window_info, (HWND)_handle);
	bk::uint l_vo_viewport_ID = g_video.get_<bk::vo::window>(l_vo_window_ID).viewport_ID(0);
	g_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_flags(bk::cf::color);
	bk::color l_color(bk::random_0.get(1.f), bk::random_0.get(1.f), bk::random_0.get(1.f));
	g_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_color(l_color);
	return l_vo_window_ID;
}
void reset_window(bk::uint _ID, bk::handle _handle)
{
	g_video.get_<bk::vo::window>(_ID).reset((HWND)_handle);
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

bool create()
{
	if (g_video.create())
	{
		commands::add("Update", bk::functor_<bool>(&update));
		commands::add("CreateView", bk::functor_<bk::uint, bk::handle>(&create_window));
		commands::add("ResetView", bk::functor_<void, bk::uint, bk::handle>(&reset_window));
		commands::add("DestroyView", bk::functor_<void, bk::uint>(&destroy_window));
		return true;
	}
	return false;
}
void destroy()
{
	commands::remove("DestroyView");
	commands::remove("ResetView");
	commands::remove("CreateView");
	commands::remove("Update");
	g_video.destroy();
}

} // namespace bikini /*-------------------------------------------------------------------------*/