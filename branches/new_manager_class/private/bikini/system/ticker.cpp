/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// ticker

ticker::ticker(real _period) :
	m_period(_period),
	m_run(true),
	m_sync(false, false),
	m_task(*this, &ticker::m_proc, "bikini-iii ticker", THREAD_PRIORITY_TIME_CRITICAL)
{
	m_task.run();
}
ticker::~ticker()
{
	m_run = false;
	m_task.wait();
}
real ticker::period()
{
	return m_period;
}
void ticker::set_period(real _period)
{
	m_period = _period;
}
void ticker::sync()
{
	m_sync.wait();
}
void ticker::m_proc()
{
	while(m_run) {
		sleep(m_period);
		m_sync.set();
	}
}

} /* namespace bk -------------------------------------------------------------------------------*/
