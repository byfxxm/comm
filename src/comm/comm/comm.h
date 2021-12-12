#pragma once
#include <string>

#ifdef COMM_EXPORTS
#define COMM_API __declspec(dllexport)
#else
#define COMM_API __declspec(dllimport)
#endif

extern "C"
{
	COMM_API void* comm_create_server();
	COMM_API void* comm_create_client();
	COMM_API void comm_delete(void*);
	COMM_API bool comm_send_msg(void*, const std::string&);
	COMM_API bool comm_recv_msg(void*, std::string&);
}