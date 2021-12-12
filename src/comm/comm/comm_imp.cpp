#include "pch.h"
#include "comm_imp.h"

comm_base::~comm_base()
{
	CloseHandle(_pipe);
}

void comm_base::send_msg(const std::string& msg)
{
	if (!WriteFile(_pipe, msg.c_str(), msg.length(), NULL, NULL))
		throw std::exception("send error");
}

void comm_base::recv_msg(std::string& msg)
{
	msg.clear();
	DWORD actual_size = 0;
	char buff[1024]{ 0 };
	do
	{
		if (!ReadFile(_pipe, buff, sizeof(buff), &actual_size, NULL))
			throw std::exception("client error");

		msg += buff;
	} while (actual_size < sizeof(buff));
}

comm_server::~comm_server()
{
	DisconnectNamedPipe(_pipe);
}

comm_server::comm_server()
{
	_pipe = CreateNamedPipe(_pipe_name,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		NMPWAIT_WAIT_FOREVER,
		0);

	if (_pipe == INVALID_HANDLE_VALUE)
		throw std::exception("fail to create server pipe");

	if (!ConnectNamedPipe(_pipe, NULL))
		throw std::exception("fail to create pipe");
}

comm_client::comm_client()
{
	while (!WaitNamedPipe(_pipe_name, NMPWAIT_WAIT_FOREVER))
		std::this_thread::yield();

	_pipe = CreateFile(_pipe_name,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL, OPEN_EXISTING,
		0,
		NULL);

	if (_pipe == INVALID_HANDLE_VALUE)
		throw std::exception("fail to create client pipe");
}