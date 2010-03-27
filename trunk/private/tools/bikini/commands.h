#pragma once

namespace commands { /*--------------------------------------------------------------------------*/

struct _command;

void create();
void destroy();

void add(const bk::achar* _name, _command &_c);
void remove(const bk::achar* _name);

template <typename _F>
inline void add_command(const bk::achar* _name, const _F &_functor);

#include "commands.inl"

} /* namespace commands -------------------------------------------------------------------------*/
