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
		inline void remove_child(bk::uint _child) { for (bk::uint l_ID = first_relation(); l_ID != bk::bad_ID; l_ID = next_relation(l_ID)) if (get_relation(l_ID) == _child) { remove_relation(l_ID); break; } }

		object(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name);
		~object();

		virtual bool add_child(bk::uint _child) { add_relation(_child); return true; }
		virtual bool rename(const bk::wstring &_name) { set_name(_name); return true; }
		virtual bool move(bk::uint _new_parent_ID) { m_parent_ID = _new_parent_ID; return true; }
		virtual bool remove() { return false; }
		virtual bk::astring structure() const { return ""; }
		virtual bool save() const { return true; }
		virtual bool load() { return true; }

		bk::wstring path() const;

	protected:
		inline void set_name(const bk::wstring &_name) { m_name = _name; }
		inline void set_valid(bool _yes = true) { m_valid = _yes; }

	private:
		bk::GUID m_GUID;
		bk::uint m_parent_ID;
		bk::wstring m_name;
		bool m_valid;
	};

	struct folder : object
	{
		struct info : object::info
		{
			typedef bool a2;

			inline info(bk::uint _type)
			:
				object::info(_type)
			{}
		};

		folder(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create);

		virtual bool rename(const bk::wstring &_name);
		virtual bool move(bk::uint _new_parent_ID);
		virtual bool remove();

	private:
	};

	struct ot { enum object_type
	{
		project, package, folder, stage, resources
	};};

	inline const bk::wstring& location() const { return m_location; }

	workspace();

	bool create();
	void destroy();

	const bk::GUID& new_project(const bk::wstring &_location, const bk::wstring &_name);
	const bk::GUID& open_project(const bk::wstring &_path);
	const bk::GUID& new_package(const bk::GUID& _parent, const bk::wstring &_name);
	const bk::GUID& new_folder(const bk::GUID& _parent, const bk::wstring &_name);
	const bk::GUID& new_stage(const bk::GUID& _parent, const bk::wstring &_name);
	bk::astring object_structure(const bk::GUID& _object);
	bool rename_object(const bk::GUID& _object, const bk::wstring &_name);
	bool move_object(const bk::GUID& _object, const bk::GUID& _new_parent);
	bool remove_object(const bk::GUID& _object);
	bool save_all();

private:
	bk::wstring m_location;
	bk::uint find_object(const bk::GUID &_object) const;
};

namespace wo { // workspace objects ---------------------------------------------------------------

struct project : workspace::folder
{
	struct info : workspace::folder::info
	{
		typedef project object;
		typedef const bk::wstring& a0;	// name
		typedef bool a1;				// create

		inline info()
		:
			workspace::folder::info(workspace::ot::project)
		{}
	};

	static const bk::wchar* extension;

	project(const info &_info, workspace &_workspace, const bk::wstring &_name, bool _create);

	virtual bool add_child(bk::uint _child);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bool load();

private:
	void write_structure(pugi::xml_node &_root) const;
};

struct package : workspace::folder
{
	struct info : workspace::folder::info
	{
		typedef package object;

		inline info()
		:
			workspace::folder::info(workspace::ot::package)
		{}
	};

	static const bk::wchar* extension;

	package(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name, bool _create);

	virtual bool add_child(bk::uint _child);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bool load();

private:
	void write_structure(pugi::xml_node &_root) const;
};

struct folder : workspace::folder
{
	struct info : workspace::folder::info
	{
		typedef folder object;

		inline info()
		:
			workspace::folder::info(workspace::ot::folder)
		{}
	};

	folder(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name, bool _create);

	virtual bool add_child(bk::uint _child);
};

struct stage : workspace::folder
{
	struct info : workspace::folder::info
	{
		typedef stage object;

		inline info()
		:
			workspace::folder::info(workspace::ot::stage)
		{}
	};

	static const bk::wchar* extension;

	stage(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name, bool _create);

	virtual bool add_child(bk::uint _child);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bool load();

private:
	void write_structure(pugi::xml_node &_root) const;
};

} // namespace wo ---------------------------------------------------------------------------------