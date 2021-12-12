#include "pch.h"
#include "comm.h"
#include "comm_imp.h"

void* comm_create_server()
{
	return new comm_server();
}

void* comm_create_client()
{
	return new comm_client();
}

void comm_delete(void* comm)
{
	delete comm;
}

void comm_send_msg(void* comm, const char* buff, unsigned long size)
{
	return ((comm_base*)comm)->send(buff, size);
}

void comm_recv_msg(void* comm, char* buff, unsigned long size, unsigned long& actual_size)
{
	return ((comm_base*)comm)->recv(buff, size, actual_size);
}