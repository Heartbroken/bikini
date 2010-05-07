#pragma once

#include "commands.h"
#include "project.h"

struct bikini
{
	bikini();
	bool create();
	bool update();
	void destroy();

	bool create_project(const bk::wstring &_path);

	// test
	bk::uint create_window(bk::handle _handle);
	void reset_window(bk::uint _ID, bk::handle _handle);
	void destroy_window(bk::uint _ID);

private:
	bk::video m_video;
	bk::ticker m_ticker;
	project m_project;
};

bikini& get_bikini();