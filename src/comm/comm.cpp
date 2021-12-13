#include "pch.h"
#include "comm.h"
#include "comm_imp.h"

void* comm_get_server()
{
	static comm_server inst;
	return &inst;
}

void* comm_get_client()
{
	static comm_client inst;
	return &inst;
}

bool comm_send_msg(void* comm, const std::string& msg)
{
	return ((comm_base*)comm)->send_msg(msg);
}

bool comm_recv_msg(void* comm, std::string& msg)
{
	return ((comm_base*)comm)->recv_msg(msg);
}