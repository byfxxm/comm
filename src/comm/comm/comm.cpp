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

void comm_send_msg(void* comm, const std::string& msg)
{
	return ((comm_base*)comm)->send_msg(msg);
}

void comm_recv_msg(void* comm, std::string& msg)
{
	return ((comm_base*)comm)->recv_msg(msg);
}