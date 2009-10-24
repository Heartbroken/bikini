/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// ticker
/** [TODO]
 */
struct ticker {
	ticker(real _period);
	~ticker();
	real period();
	void set_period(real _period);
	void sync();
private:
	real m_period;
	bool m_run;
	thread::flag m_sync;
	thread::task m_task;
	void m_proc();
};
