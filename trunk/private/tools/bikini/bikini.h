#pragma once

#include "commands.h"
#include "solution.h"

struct bikini
{
	bikini();
	bool create();
	bool update();
	void destroy();

	bool create_solution(const bk::wstring &_path);

	// test
	bk::uint create_window(bk::handle _handle);
	void reset_window(bk::uint _ID, bk::handle _handle);
	void destroy_window(bk::uint _ID);

private:
	bk::video m_video;
	bk::ticker m_ticker;
	solution m_solution;
};

bikini& get_bikini();