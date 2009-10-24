// test_application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

namespace at { enum application_tasks {
	task0
};}

struct task0 : bk::application::task
{
	struct info : bk::application::task::info
	{
		typedef task0 object;
		inline info() : bk::application::task::info(at::task0, "test_application main task") {}
	};
	inline task0(const info &_info, bk::application &_application)
	:
		bk::application::task(_info, _application)
	{}
	void main()
	{
		bk::window l_window;
		l_window.create(800, 600);
		l_window.set_caption("test_application ");

		bk::video l_video; l_video.create();
		bk::vo::window::info l_vo_window_info;
		bk::uint l_vo_window_ID = l_video.spawn(l_vo_window_info, l_window.get_handle());

		bk::flash::renderer l_renderer(l_video);
		l_renderer.create();

		bk::uint l_vo_viewport_ID = l_video.get_<bk::vo::window>(l_vo_window_ID).viewport_ID(0);
		l_renderer.set_viewport_ID(l_vo_viewport_ID);

		bk::flash::player l_player;
		l_player.create(l_renderer);
		l_player.play("data/gui/test.swf");

		l_window.show();

		bk::ticker l_ticker(bk::real(1.0/60.0));

		bk::rbig l_time = bk::sys_time();

		while (true)
		{
			bk::real l_dt = bk::real(bk::sys_time() - l_time);
			l_time += l_dt;

			l_dt = bk::min(l_dt, bk::real(0.3));

			if (!l_window.update(l_dt)) break;

			l_player.update(l_dt);
			l_player.render();

			l_video.update(l_dt);

			l_ticker.sync();
		}

		l_player.destroy();
		l_renderer.destroy();

		l_video.kill(l_vo_window_ID);
		l_video.destroy();

		l_window.destroy();
	}
};

void main()
{
	bk::application l_app;
	task0::info l_task0_info;
	l_app.spawn(l_task0_info);
	l_app.run();
}
