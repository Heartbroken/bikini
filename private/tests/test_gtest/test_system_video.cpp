#include "stdafx.h"

// system/video
TEST(system_video, video_create) {
	bk::video l_video;
	ASSERT_TRUE(l_video.create());
	l_video.destroy();
}
TEST(system_video, window_create) {
	bk::video l_video;
	ASSERT_TRUE(l_video.create());

	bk::window l_window(l_video);
	ASSERT_TRUE(l_window.create(640, 400));

	bk::vo::window::info l_window_info;
	bk::u32 l_window_ID = l_video.spawn(l_window_info, l_window.get_handle());
	l_video.update(0);
	ASSERT_TRUE(l_video.get<bk::vo::window>(l_window_ID).valid());
	l_video.kill(l_window_ID);

	l_video.destroy();
}
