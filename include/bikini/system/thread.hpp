/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace thread { /*----------------------------------------------------------------------------*/

///	_task_result_ - used internally by task_
template<typename _T> struct _task_result_ {
	inline _task_result_() {}
	inline _task_result_(const _T &_r) : r(_r) {}
	inline _task_result_& operator = (const _T &_r) { r = _r; return *this; }
	inline _T get() const { return r; }
private:
	_T r;
};

/// set thread name
inline void set_thread_name(uint _ID, const achar* _name);

///	Thread task class template. Serves to start and manage separate thread.
/**	Encloses a function, member function or functor with up to ten arguments.
	Allows to check if enclosed function finished execution and to get execution result.
 */
template<typename _R, typename _A0 = notype, typename _A1 = notype, typename _A2 = notype, typename _A3 = notype, typename _A4 = notype, typename _A5 = notype, typename _A6 = notype, typename _A7 = notype, typename _A8 = notype, typename _A9 = notype>
struct task_ : uncopyble {
	/// construct a task from a function or a functor
	template<typename _F> inline task_(_F &_f, const achar* _name = 0, sint _priority = THREAD_PRIORITY_NORMAL, uint _stacksize = 0, uint _processor = bad_ID);
	/// construct a task ftom a member function
	template<typename _O, typename _M> inline task_(_O &_o, const _M &_m, const achar* _name = 0, sint _priority = THREAD_PRIORITY_NORMAL, uint _stacksize = 0, uint _processor = bad_ID);
	/// destructor
	inline ~task_();
	/// start execution
	inline bool run(_A0 _a0 = _A0(), _A1 _a1 = _A1(), _A2 _a2 = _A2(), _A3 _a3 = _A3(), _A4 _a4 = _A4(), _A5 _a5 = _A5(), _A6 _a6 = _A6(), _A7 _a7 = _A7(), _A8 _a8 = _A8(), _A9 _a9 = _A9());
	/// check if execution is finished
	inline bool done() const;
	/// wait while execution will be finished and return the result
	inline _R wait() const;
	/// terminate execution (don't use this)
	inline void terminate();
	/// clear a task after execution is finished
	inline void clear();
private:
	astring m_name;
	typedef functor_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9> functor;
	functor m_functor;
	handle m_handle; uint m_ID;
	sint m_priority;
	uint m_stacksize;
	uint m_processor;
	_task_result_<_R> m_result;
};
typedef task_<void> task;

///	Event synchronization object wrapper.
/**	Allows to create event, to set event signaled and nonsignaled state,
	and to wait for event signaled state is set.
	Unfortunately "event" is a reserved keyword in C++.
	So I'll call my event a flag.
 */
struct flag : uncopyble {
	/// constructor
	inline flag(bool _reset = false, bool _state = false, const astring &_name = "");
	/// destructor
	inline ~flag();
	/// set event signaled state
	inline void set();
	/// set event nonsignaled state
	inline void reset();
	/// a calling thead will wait for event signaled state is set
	inline bool wait(real _timeout = infinity);
private:
	handle m_handle;
};

///	Mutex synchronization object wrapper.
/**	
 */
struct mutex {
	inline mutex(bool _owned = false, const astring &_name = "");
	inline ~mutex();
	inline bool take(real _timeout = infinity);
	inline void drop();
private:
	handle m_handle;
};

///	
/**	
 */
struct section {
	inline section();
	inline ~section();
	inline void enter();
	inline bool try_enter();
	inline void leave();
private:
	CRITICAL_SECTION m_criticalsection;
};

///
struct locker {
	inline locker(section &_section, bool _try_lock = false);
	inline ~locker();
	inline operator bool ();
private:
	section &m_section;
	bool m_locked;
};

#include "thread.inl"

} /* namespace thread ---------------------------------------------------------------------------*/
