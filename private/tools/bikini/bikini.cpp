#include "stdafx.h"

static bk::vo::window::info g_vo_window_info;

bikini& get_bikini()
{
	static bikini sl_bikini;
	return sl_bikini;
}

bikini::bikini()
:
	m_ticker(1.f / 60.f)
{}
bool bikini::create()
{
	if (m_video.create())
	{
		commands::add("Update", bk::functor_<bool>(*this, &bikini::update));
		commands::add("Destroy", bk::functor(*this, &bikini::destroy));

		// test
		commands::add("CreateView", bk::functor_<bk::uint, bk::handle>(*this, &bikini::create_window));
		commands::add("ResetView", bk::functor_<void, bk::uint, bk::handle>(*this, &bikini::reset_window));
		commands::add("DestroyView", bk::functor_<void, bk::uint>(*this, &bikini::destroy_window));
		// test

		return m_workspace.create();
	}
	return false;
}
bool bikini::update()
{
	m_ticker.sync();

	static bk::rbig sl_time = bk::sys_time();

	bk::rbig l_time = bk::sys_time();
	bk::rbig l_dt = l_time - sl_time;
	sl_time = l_time;

	return m_video.update((bk::real)l_dt);
}
void bikini::destroy()
{
	// test
	commands::remove("DestroyView");
	commands::remove("ResetView");
	commands::remove("CreateView");
	// test

	commands::remove("Destroy");
	commands::remove("Update");

	m_workspace.destroy();
	m_video.destroy();
}


// test
bk::uint bikini::create_window(bk::handle _handle)
{
	bk::uint l_vo_window_ID = m_video.spawn(g_vo_window_info, (HWND)_handle);
	bk::uint l_vo_viewport_ID = m_video.get_<bk::vo::window>(l_vo_window_ID).viewport_ID(0);
	m_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_flags(bk::cf::color);
	bk::color l_color(bk::random_0.get(1.f), bk::random_0.get(1.f), bk::random_0.get(1.f));
	m_video.get_<bk::vo::viewport>(l_vo_viewport_ID).set_clear_color(l_color);
	return l_vo_window_ID;
}
void bikini::reset_window(bk::uint _ID, bk::handle _handle)
{
	m_video.get_<bk::vo::window>(_ID).reset((HWND)_handle);
}
void bikini::destroy_window(bk::uint _ID)
{
	m_video.kill(_ID);
}
// test
