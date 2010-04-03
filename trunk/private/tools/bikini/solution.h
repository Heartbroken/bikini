#pragma once

struct solution : bk::manager
{
	struct object : bk::manager::object
	{
		struct info : bk::manager::object::info
		{
			typedef solution manager;

			inline info(bk::uint _type)
			:
				bk::manager::object::info(_type)
			{}
		};

		inline solution& get_solution() const { return get_manager_<solution>(); }
		inline const bk::wstring& name() const { return m_name; }
		inline void set_name(const bk::wstring &_name) { m_name = _name; }

		inline object(const info &_info, solution &_solution)
		:
			bk::manager::object(_info, _solution),
			m_GUID(bk::random_GUID())
		{}

	private:
		bk::wstring m_name;
		GUID m_GUID;
	};

	struct ot { enum object_type
	{
		project
	};};

	inline const bk::wstring& name() const { return m_name; }

	solution();

private:
	bk::wstring m_name;
};

namespace so { // solution objects ----------------------------------------------------------------

struct project : solution::object
{
	struct info : solution::object::info
	{
		typedef project object;

		inline info()
		:
			solution::object::info(solution::ot::project)
		{}
	};

	inline project(const info &_info, solution &_solution)
	:
		solution::object(_info, _solution)
	{}
};

} // namespace so ---------------------------------------------------------------------------------