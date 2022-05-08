#include "pch.h"
#include "comm.h"
#include "comm_imp.h"

void* comm_get_server() {
	static CommServer inst;
	return &inst;
}

void* comm_get_client() {
	static CommClient inst;
	return &inst;
}

bool comm_send_msg(void* comm, const std::string& msg) {
	return ((CommBase*)comm)->send_msg(msg);
}

bool comm_recv_msg(void* comm, std::string& msg) {
	return ((CommBase*)comm)->recv_msg(msg);
}