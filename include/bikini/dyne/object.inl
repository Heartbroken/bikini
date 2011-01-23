/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2011 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

inline object::object()
:
	m_simulator(*(simulator*)0),
	m_ID(bad_ID)
{}
inline object::object(const object &_o)
:
	m_simulator(_o.get_simulator()),
	m_ID(_o.ID())
{}
inline object& object::operator = (const object &_o)
{
	this->~object();
	new(this) object(_o);
	return *this;
}

inline simulator& object::get_simulator() const
{
	return m_simulator;
}
inline uint object::ID() const
{
	return m_ID;
}

inline bool object::is_valid() const
{
	return &get_simulator() != 0 && ID() != bad_ID;
}
