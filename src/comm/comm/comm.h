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
	COMM_API void comm_delete(void* comm);
	COMM_API bool comm_send_msg(void* comm, const std::string& msg);
	COMM_API bool comm_recv_msg(void* comm, std::string& msg);
}