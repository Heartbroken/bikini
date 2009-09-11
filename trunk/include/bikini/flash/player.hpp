/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	flash player
/**	[TODO]
 */
struct player
{
	player();
	~player();

	template<typename _Renderer> inline bool create(_Renderer &_renderer);
	template<typename _Renderer, typename _Loader> inline bool create(_Renderer &_renderer, _Loader &_loader);

	bool update(real _dt);
	bool render() const;

	void destroy();

	bool play(const astring &_path);
	bool play(const wstring &_path);
	bool pause(bool _yes = true);
	bool stop();

private:
	struct _gameswf; _gameswf *m_gameswf_p;
	struct renderer; struct loader;
	bool create(renderer &_renderer, loader &_loader);
	bk::loader m_def_loader;
};

#include "player.inl"