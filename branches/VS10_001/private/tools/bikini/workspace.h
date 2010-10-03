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
		~object();

		virtual bool add_child(bk::uint _child);
		virtual bool remove_child(bk::uint _child);
		virtual bool rename(const bk::wstring &_name);
		virtual bool move(bk::uint _new_parent_ID);
		virtual bool remove();
		virtual bk::astring structure() const;
		virtual bool save() const;
		virtual bool load();
		virtual bk::wstring script() const;
		virtual void set_script(const bk::wstring &_script);

		bk::wstring path() const;

	protected:
		inline void set_GUID(const bk::GUID &_GUID) { m_GUID = _GUID; }
		inline void set_name(const bk::wstring &_name) { m_name = _name; }
		inline void set_valid(bool _yes = true) { m_valid = _yes; }
		inline void set_loading(bool _yes) { m_loading = _yes; }
		inline bool loading() const { return m_loading; }

	private:
		bk::GUID m_GUID;
		bk::uint m_parent_ID;
		bk::wstring m_name;
		bool m_valid, m_loading;
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
	};

	struct ot { enum object_type
	{
		project, stage, package, folder, resources
	};};

	inline const bk::wstring& location() const { return m_location; }

	workspace();

	bool create();
	void destroy();

	const bk::GUID& new_project(const bk::wstring &_location, const bk::wstring &_name);
	const bk::GUID& open_project(const bk::wstring &_path);
	const bk::GUID& new_package(const bk::GUID &_parent, const bk::wstring &_name);
	const bk::GUID& new_folder(const bk::GUID &_parent, const bk::wstring &_name);
	const bk::GUID& new_stage(const bk::GUID &_parent, const bk::wstring &_name);
	bk::astring object_structure(const bk::GUID &_object);
	bk::wstring object_path(const bk::GUID &_object);
	bk::astring object_name(const bk::GUID &_object);
	bool rename_object(const bk::GUID &_object, const bk::wstring &_name);
	bk::wstring object_script(const bk::GUID &_object);
	bool change_object_script(const bk::GUID &_object, const bk::wstring &_script);
	bool move_object(const bk::GUID &_object, const bk::GUID &_new_parent);
	bool remove_object(const bk::GUID &_object);
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

	static bk::wchar const* extension;

	project(const info &_info, workspace &_workspace, const bk::wstring &_name, bool _create);

	virtual bool add_child(bk::uint _child);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bool load();

private:
	void write_structure(pugi::xml_node &_root) const;
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

	static bk::wchar const* extension;

	stage(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create);

	virtual bool add_child(bk::uint _child);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bool load();
	virtual bk::wstring script() const;
	virtual void set_script(const bk::wstring &_script);

private:
	void write_structure(pugi::xml_node &_root) const;
	bk::wstring m_script;
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

	static bk::wchar const* extension;

	package(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create);

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

	static bk::wchar const* extension;

	folder(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create);

	virtual bool add_child(bk::uint _child);
	virtual bk::astring structure() const;
	virtual bool save() const;
	virtual bool load();

private:
	void write_structure(pugi::xml_node &_root) const;
};

} // namespace wo ---------------------------------------------------------------------------------