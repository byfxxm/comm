#pragma once

#ifdef COMM_EXPORTS
#define COMM_API __declspec(dllexport)
#else
#define COMM_API __declspec(dllimport)
#endif

extern "C"
{
	COMM_API void comm_send_msg(const char*, int);
	COMM_API void comm_recv_msg(char*, int&);
}