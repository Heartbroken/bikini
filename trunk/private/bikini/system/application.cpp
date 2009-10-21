/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// application

application::application()
{
	timeBeginPeriod(1);
#if defined(WIN32)	// console window
	typedef HWND (WINAPI *GetConsoleWindow_fn)(void);
	HMODULE l_kernel32_h = GetModuleHandleA("kernel32.dll");
	GetConsoleWindow_fn GetConsoleWindow = (GetConsoleWindow_fn)GetProcAddress(l_kernel32_h, "GetConsoleWindow");
	if(GetConsoleWindow != 0) ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetConsoleTitleA(" bikini-iii");
#endif
}
application::~application()
{
	timeEndPeriod(1);
}
bool application::run()
{
	ticker l_ticker(0.1f);
	bk::rbig l_time = bk::sys_time();
	bool l_done = false;
	while (!l_done)
	{
		bk::real l_dt = bk::real(bk::sys_time() - l_time);
		l_time = bk::sys_time();

		update(l_dt);

		l_done = true;
		for (uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID))
		{
			if(get_<task>(l_ID).done()) kill(l_ID);
			else l_done = false;
		}

		l_ticker.sync();
	}
	return false;
}

// application::task

application::task::task(const info &_info, application &_application)
:
	manager::object(_info, _application), m_task(*this, &application::task::main, _info.name.c_str())
{}
application::task::~task()
{
	if(!m_task.done())
	{
		m_task.terminate();
	}
}
bool application::task::update(real _dt)
{
	if (!m_task.started())
	{
		m_task.run();
	}

	return true;
}

// application::task::info

application::task::info::info(uint _type, const achar* _name)
:
	manager::object::info(_type), name(_name ? _name : "")
{}

} /* namespace bk -------------------------------------------------------------------------------*/
