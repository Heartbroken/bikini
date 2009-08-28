#include "stdafx.h"

// system/video
TEST(system_video, video_create) {
	bk::video l_video;
	l_video.create();
	ASSERT_TRUE(l_video.ready());
	l_video.destroy();
	ASSERT_FALSE(l_video.ready());
}
TEST(system_video, window_create) {
	bk::video l_video;
	l_video.create();
	ASSERT_TRUE(l_video.ready());

	bk::window l_window(l_video);
	l_window.create(640, 400);

	bk::vr::window::info l_window_info;
	bk::u32 l_window_ID = l_video.spawn(l_window_info, l_window.get_handle());
	l_video.update(0);
	ASSERT_TRUE(l_video.get<bk::vr::window>(l_window_ID).valid());
	l_video.kill(l_window_ID);

	l_video.destroy();
	ASSERT_FALSE(l_video.ready());
}
