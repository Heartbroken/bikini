/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	base application class
/**	[TODO]
 */
struct application : manager
{
	///	base application task class
	/**	[TODO]
	 */
	struct task : manager::object
	{
		struct info : manager::object::info
		{
			typedef task object;
			typedef application manager;
			astring name;
			info(uint _type, const achar* _name = 0);
		};

		inline application& get_application() const { return static_cast<application&>(get_manager()); }
		inline bool done() const { return m_task.done(); }
		inline void wait() const { return m_task.wait(); }

		task(const info &_info, application &_application);
		~task();

	protected:
		virtual void main() = 0;

	private:
		thread::task m_task;
	};

	application();
	~application();
	virtual bool run();
};
