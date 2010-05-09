#pragma once

struct project : bk::manager
{
	struct object : bk::manager::object
	{
		struct info : bk::manager::object::info
		{
			typedef project manager;

			inline info(bk::uint _type)
			:
				bk::manager::object::info(_type)
			{}
		};

		inline project& get_project() const { return get_manager_<project>(); }
		inline const bk::wstring& name() const { return m_name; }
		inline void set_name(const bk::wstring &_name) { m_name = _name; }

		inline object(const info &_info, project &_project)
		:
			bk::manager::object(_info, _project),
			m_GUID(bk::random_GUID())
		{}

	private:
		bk::wstring m_name;
		GUID m_GUID;
	};

	struct ot { enum object_type
	{
		package, folder, stage, resources
	};};

	inline const bk::wstring& name() const { return m_name; }
	inline const bk::wstring path() const { return m_folder.path(); }

	project();

	bool create(const bk::wstring &_location, const bk::wstring &_name);
	void destroy();

	void write_structure(pugi::xml_node &_root) const;
	bk::astring get_structure() const;
	bool save() const;

private:
	GUID m_GUID;
	bk::wstring m_name;
	bk::folder m_folder;
};

namespace po { // project objects -----------------------------------------------------------------

struct package : project::object
{
	struct info : project::object::info
	{
		typedef package object;

		inline info()
		:
			project::object::info(project::ot::package)
		{}
	};

	inline package(const info &_info, project &_project)
	:
		project::object(_info, _project)
	{}
};

struct folder : project::object
{
	struct info : project::object::info
	{
		typedef folder object;

		inline info()
		:
			project::object::info(project::ot::folder)
		{}
	};

	inline folder(const info &_info, project &_project)
	:
		project::object(_info, _project)
	{}
};

} // namespace po ---------------------------------------------------------------------------------