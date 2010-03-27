//

template <typename _F>
inline void add_command(const bk::achar* _name, const _F &_functor)
{
	add(_name, * new command_<_F>(_functor));
}

//

inline pugi::xml_node child(const pugi::xml_node &_n, bk::uint _i)
{
	bk::uint l_index = 0;
	for (pugi::xml_node l_c = _n.first_child(); l_c; l_c = l_c.next_sibling())
		if (l_index++ == _i) return l_c;

	return pugi::xml_node();
}

template <typename _T> inline _T pop(const pugi::xml_node &_n, bk::uint _i);
template <> inline bool pop<bool>(const pugi::xml_node &_n, bk::uint _i)
{
	return child(_n, _i).attribute("value").as_bool();
}
template <> inline bk::sint pop<bk::sint>(const pugi::xml_node &_n, bk::uint _i)
{
	return child(_n, _i).attribute("value").as_int();
}

//

inline void push(pugi::xml_node &_n, bool _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("boolean");
	l_n.append_attribute("value").set_value(_v ? "true" : "false");
}
inline void push(pugi::xml_node &_n, bk::sint _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_attribute("value").set_value(bk::format("%d", _v));
}
inline void push(pugi::xml_node &_n, bk::real _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_attribute("value").set_value(bk::format("%f", _v));
}

//

struct _command { virtual void execute(const pugi::xml_node &_a, pugi::xml_node &_r) = 0; };
template <typename _F> struct command_;

template <typename _R>
struct command_<bk::functor_<_R> > : _command
{
	typedef bk::functor_<_R> F; F f;
	inline command_(F _f) : f(_f) {}
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { push(_r, f()); }
};
template <typename _R, typename _A0>
struct command_<bk::functor_<_R, _A0> > : _command
{
	typedef bk::functor_<_R, _A0> F; F f;
	inline command_(F _f) : f(_f) {}
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { push(_r, f(pop<_A0>(_a, 0))); }
};
template <typename _R, typename _A0, typename _A1>
struct command_<bk::functor_<_R, _A0, _A1> > : _command
{
	typedef bk::functor_<_R, _A0, _A1> F; F f;
	inline command_(F _f) : f(_f) {}
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { push(_r, f(pop<_A0>(_a, 0), pop<_A1>(_a, 1))); }
};
