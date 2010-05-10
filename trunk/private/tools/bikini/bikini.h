#pragma once

#include "commands.h"
#include "workspace.h"

struct bikini
{
	bikini();
	bool create();
	bool update();
	void destroy();

	// test
	bk::uint create_window(bk::handle _handle);
	void reset_window(bk::uint _ID, bk::handle _handle);
	void destroy_window(bk::uint _ID);

private:
	bk::video m_video;
	bk::ticker m_ticker;
	workspace m_workspace;
};

bikini& get_bikini();