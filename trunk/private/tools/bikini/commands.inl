//

void add_command(const bk::achar* _name, _command &_c);

template <typename _F>
inline void add(const bk::achar* _name, const _F &_functor)
{
	add_command(_name, * new command_<_F>(_functor));
}

//

inline pugi::xml_node child(const pugi::xml_node &_n, bk::uint _i)
{
	bk::uint l_index = 0;
	for (pugi::xml_node l_c = _n.first_child(); l_c; l_c = l_c.next_sibling())
		if (l_index++ == _i) return l_c;

	return pugi::xml_node();
}

template <typename _T> struct pop;
template <> struct pop<bool> { static inline bool a(const pugi::xml_node &_n, bk::uint _i)
{
	bk::astring l_s = child(_n, _i).child_value();
	if (l_s == "0" || l_s == "false") return false;
	return true;
}};
template <> struct pop<unsigned int> { static inline unsigned int a(const pugi::xml_node &_n, bk::uint _i)
{
	unsigned int l_v; sscanf_s(child(_n, _i).child_value(), "%u", &l_v);
	return l_v;
}};
template <> struct pop<int> { static inline int a(const pugi::xml_node &_n, bk::uint _i)
{
	int l_v; sscanf_s(child(_n, _i).child_value(), "%d", &l_v);
	return l_v;
}};
template <> struct pop<unsigned __int64> { static inline unsigned __int64 a(const pugi::xml_node &_n, bk::uint _i)
{
	unsigned __int64 l_v; sscanf_s(child(_n, _i).child_value(), "%I64u", &l_v);
	return l_v;
}};
template <> struct pop<__int64> { static inline __int64 a(const pugi::xml_node &_n, bk::uint _i)
{
	__int64 l_v; sscanf_s(child(_n, _i).child_value(), "%I64d", &l_v);
	return l_v;
}};
template <> struct pop<bk::handle> { static inline bk::handle a(const pugi::xml_node &_n, bk::uint _i)
{
	bk::handle l_v;
#ifdef _WIN64
	sscanf_s(child(_n, _i).child_value(), "%I64d", &l_v);
#else
	sscanf_s(child(_n, _i).child_value(), "%d", &l_v);
#endif
	return l_v;
}};
template <> struct pop<bk::real> { static inline bk::real a(const pugi::xml_node &_n, bk::uint _i)
{
	bk::real l_v; sscanf_s(child(_n, _i).child_value(), "%f", &l_v);
	return l_v;
}};
template <> struct pop<const bk::achar*> { static inline const bk::achar* a(const pugi::xml_node &_n, bk::uint _i)
{
	return child(_n, _i).child_value();
}};
template <> struct pop<bk::astring> { static inline bk::astring a(const pugi::xml_node &_n, bk::uint _i)
{
	return child(_n, _i).child_value();
}};
template <> struct pop<const bk::astring&> { static inline const bk::achar* a(const pugi::xml_node &_n, bk::uint _i)
{
	return child(_n, _i).child_value();
}};

//

inline void push(pugi::xml_node &_n, bool _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("boolean");
	l_n.append_child(pugi::node_pcdata).set_value(_v ? "true" : "false");
}
inline void push(pugi::xml_node &_n, unsigned int _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_child(pugi::node_pcdata).set_value(bk::format("%u", _v));
}
inline void push(pugi::xml_node &_n, int _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_child(pugi::node_pcdata).set_value(bk::format("%d", _v));
}
inline void push(pugi::xml_node &_n, unsigned __int64 _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_child(pugi::node_pcdata).set_value(bk::format("%I64u", _v));
}
inline void push(pugi::xml_node &_n, __int64 _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_child(pugi::node_pcdata).set_value(bk::format("%I64d", _v));
}
inline void push(pugi::xml_node &_n, float _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_child(pugi::node_pcdata).set_value(bk::format("%f", _v));
}
inline void push(pugi::xml_node &_n, double _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("number");
	l_n.append_child(pugi::node_pcdata).set_value(bk::format("%f", _v));
}
inline void push(pugi::xml_node &_n, const char* _v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("string");
	l_n.append_child(pugi::node_pcdata).set_value(_v);
}
inline void push(pugi::xml_node &_n, const bk::astring &_v)
{
	pugi::xml_node l_n = _n.append_child(); l_n.set_name("string");
	l_n.append_child(pugi::node_pcdata).set_value(_v.c_str());
}

//

struct _command { virtual void execute(const pugi::xml_node &_a, pugi::xml_node &_r) = 0; };
template <typename _F> struct command_;

// _R
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
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { push(_r, f(pop<_A0>::a(_a, 0))); }
};
template <typename _R, typename _A0, typename _A1>
struct command_<bk::functor_<_R, _A0, _A1> > : _command
{
	typedef bk::functor_<_R, _A0, _A1> F; F f;
	inline command_(F _f) : f(_f) {}
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { push(_r, f(pop<_A0>::a(_a, 0), pop<_A1>::a(_a, 1))); }
};

// void
template <>
struct command_<bk::functor_<void> > : _command
{
	typedef bk::functor_<void> F; F f;
	inline command_(F _f) : f(_f) {}
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { f(); }
};
template <typename _A0>
struct command_<bk::functor_<void, _A0> > : _command
{
	typedef bk::functor_<void, _A0> F; F f;
	inline command_(F _f) : f(_f) {}
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { f(pop<_A0>::a(_a, 0)); }
};
template <typename _A0, typename _A1>
struct command_<bk::functor_<void, _A0, _A1> > : _command
{
	typedef bk::functor_<void, _A0, _A1> F; F f;
	inline command_(F _f) : f(_f) {}
	void execute(const pugi::xml_node &_a, pugi::xml_node &_r) { f(pop<_A0>::a(_a, 0), pop<_A1>::a(_a, 1)); }
};
