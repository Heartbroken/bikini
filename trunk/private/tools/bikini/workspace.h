#pragma once

struct workspace : bk::manager
{
	struct object : bk::manager::object
	{
		struct info : bk::manager::object::info
		{
			typedef workspace manager;
			typedef bk::uint a0;
			typedef const bk::wstring& a1;

			inline info(bk::uint _type)
			:
				bk::manager::object::info(_type)
			{}
		};

		inline workspace& get_workspace() const { return get_manager_<workspace>(); }

		inline const bk::GUID& GUID() const { return m_GUID; }
		inline bk::uint parent_ID() const { return m_parent_ID; }
		inline const bk::wstring& name() const { return m_name; }
		inline bool valid() const { return m_valid; }

		object(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name);

		virtual bool add_child(bk::uint _child) { add_relation(_child); return true; }
		virtual bool rename(const bk::wstring &_name) { set_name(_name); return true; }
		virtual bk::astring structure() const { return ""; }
		virtual bool save() const { return true; }
		virtual bk::wstring path() const { return L""; }

	protected:
		inline void set_name(const bk::wstring &_name) { m_name = _name; }
		inline void set_valid(bool _yes = true) { m_valid = _yes; }

	private:
		bk::GUID m_GUID;
		bk::uint m_parent_ID;
		bk::wstring m_name;
		bool m_valid;
	};

	struct ot { enum object_type
	{
		project, package, folder, stage, resources
	};};

	workspace();

	bool create();
	void destroy();

	const bk::GUID& new_project(const bk::wstring &_location, const bk::wstring &_name);
	const bk::GUID& new_package(const bk::GUID& _parent, const bk::wstring &_name);
	const bk::GUID& new_folder(const bk::GUID& _parent, const bk::wstring &_name);
	bk::astring object_structure(const bk::GUID& _object);
	bool rename_object(const bk::GUID& _object, const bk::wstring &_name);
	bool remove_object(const bk::GUID& _object);
	bool save_all();

private:
	bk::uint find_object(const bk::GUID &_object) const;
};

namespace wo { // workspace objects ---------------------------------------------------------------

struct project : workspace::object
{
	struct info : workspace::object::info
	{
		typedef project object;
		typedef const bk::wstring& a0;

		inline info()
		:
			workspace::object::info(workspace::ot::project)
		{}
	};


	project(const info &_info, workspace &_workspace, const bk::wstring &_location, const bk::wstring &_name);

	virtual bool add_child(bk::uint _child);
	virtual bool rename(const bk::wstring &_name);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bk::wstring path() const;

private:
	bk::folder m_folder;
	void write_structure(pugi::xml_node &_root) const;
};

struct package : workspace::object
{
	struct info : workspace::object::info
	{
		typedef package object;

		inline info()
		:
			workspace::object::info(workspace::ot::package)
		{}
	};

	package(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name);

	virtual bool add_child(bk::uint _child);
	virtual bool rename(const bk::wstring &_name);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bk::wstring path() const;


private:
	void write_structure(pugi::xml_node &_root) const;
};

struct folder : workspace::object
{
	struct info : workspace::object::info
	{
		typedef folder object;

		inline info()
		:
			workspace::object::info(workspace::ot::folder)
		{}
	};

	folder(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name);

	virtual bool add_child(bk::uint _child);
	virtual bool rename(const bk::wstring &_name);
	virtual bk::wstring path() const;
};

} // namespace wo ---------------------------------------------------------------------------------