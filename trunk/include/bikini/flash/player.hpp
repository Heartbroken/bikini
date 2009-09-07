/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	flash player
/**	[TODO]
 */
struct player : manager
{
	struct renderer
	{
	};

	struct loader
	{
		virtual uint open(const wchar* _path) = 0;
		virtual bool good(uint _ID) const = 0;
		virtual uint seek(uint _ID, sint _offset = 0, uint _from = 0) = 0;
		virtual uint read(uint _ID, handle _buffer, uint _length) = 0;
		virtual void close(uint _ID) = 0;
	};

	struct object : manager::object
	{
		struct info : manager::object::info
		{
			typedef player manager;
			info(uint _type);
		};
		object(const info &_info, player &_player);
		inline player& get_player() const;
	};
	player();
	~player();
	//inline renderer& get_renderer() const;
	//inline loader& get_loader() const;
	template<typename _Renderer> inline bool create(_Renderer &_renderer);
	template<typename _Renderer, typename _Loader> inline bool create(_Renderer &_renderer, _Loader &_loader);
	bool update(real _dt);
	void destroy();
	uint play(const wchar* _path, uint _level = bad_ID);
	uint play(const achar* _path, uint _level = bad_ID);
	bool pause(uint _level = bad_ID);
	bool stop(uint _level = bad_ID);
	bool show(uint _level = bad_ID);
	bool hide(uint _level = bad_ID);
	bool render(uint _level = bad_ID) const;

private:
	struct _gameswf;
	_gameswf *m_gameswf_p;
	//renderer *m_renderer_p;
	//loader *m_loader_p;
	bool m_create(renderer &_renderer, loader &_loader);
	bk::loader m_def_loader;
	uint_array m_levels;
	typedef array_<object::info*> movie_info_array;
	movie_info_array m_movies;
	wstring_array m_movie_names;
	object::info& m_load_movie(const wchar* _path);
	//void m_set_handlers() const;
	//void m_reset_handlers() const;
};

#include "player.inl"