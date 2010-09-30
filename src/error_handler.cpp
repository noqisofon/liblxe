#include <stdafx.h>
#include <lxe/error_handler.hpp>


//void eventlog_translator(unsigned int code, EXCEPTION_POINTERS* ep)
//{
//}


void throw_exception_translator(unsigned int code, EXCEPTION_POINTERS* ep)
{
    throw win32_error( code );
}
