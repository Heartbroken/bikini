/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

#if defined(XBOX)

#elif defined(WIN32)

//std::string format(const char *_s, ...) {
//	static const int sl_length = 1024 * 5;
//	static char sl_buff[sl_length];
//	va_list l_args;
//	va_start(l_args, _s);
//	int l_size = _vsnprintf_s(sl_buff, sl_length, sl_length, _s, l_args);
//	va_end(l_args);
//	return sl_buff;
//}

bool ARI(char* _expression, char* _file, int _line, char* _function, char* _message) {
	std::cerr << "Assertion failed ...\n";
	std::cerr << "    Expression: " << _expression << "\n";
	std::cerr << "    File: " << _file << ":" <<_line << "\n";
	std::cerr << "    Function: " << _function << "\n";
	if(_message) std::cerr << "    " << _message << "\n";
	switch(MessageBoxA(0, format("%s\n\nFile: %s:%d\nFunction: %s\n%s\n\nHit <Retry> to debug", _expression, _file, _line, _function, _message ? _message : ""), "bikini-iii | assertion failed", MB_ABORTRETRYIGNORE|MB_ICONERROR)) {
		case IDABORT : std::cerr << "... terminating\n"; Sleep(1); _exit(-1);
		case IDRETRY : std::cerr << "... debugging\n"; return false;
		case IDIGNORE : std::cerr << "... ignored\n"; return true;
	}
	return true;
}

bool ARI2(char* _expression, char* _file, int _line, char* _function, char* _message) {
	std::cerr << "Verifying failed ...\n";
	std::cerr << "    Expression: " << _expression << "\n";
	std::cerr << "    File: " << _file << ":" <<_line << "\n";
	std::cerr << "    Function: " << _function << "\n";
	if(_message) std::cerr << "    " << _message << "\n";
	return true;
}

#endif

} /* namespace bk -------------------------------------------------------------------------------*/
