/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct folder
{
	struct file
	{
		file();

	private:
		wstring m_name;
		folder &m_parent;
	};

	folder();
	folder(const folder &_folder);
	folder(const wstring &_path);
	~folder();

	folder& operator = (const folder &_folder);

	const wstring& name() const;
	bool is_root() const;
	const folder& parent() const;
	wstring path() const;
	bool exists() const;
	bool create() const;
	bool empty() const;
	bool rename(const wstring &_name);
	bool move(const folder &_to);
	bool remove();

private:
	wstring m_name;
	folder &m_parent;
};

extern folder bad_folder;