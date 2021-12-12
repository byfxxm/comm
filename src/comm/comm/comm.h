#pragma once

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
	COMM_API void comm_send_msg(void*, const char*, unsigned long);
	COMM_API void comm_recv_msg(void*, char*, unsigned long, unsigned long&);
}