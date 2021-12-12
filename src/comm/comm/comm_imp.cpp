#include "pch.h"
#include "comm_imp.h"

void comm_base::send(const char* buff, int size)
{
	WriteFile(_pipe, buff, size, NULL, NULL);
}

void comm_base::recv(char* buff, int size, int& actual_size)
{
	ReadFile(_pipe, buff, size, (DWORD*)&actual_size, NULL);
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
	while (!WaitNamedPipe(_pipe_name, NMPWAIT_USE_DEFAULT_WAIT))
	{
		std::cout << std::this_thread::get_id() << " is waiting server" << std::endl;
		std::this_thread::yield();
	}

	_pipe = CreateFile(_pipe_name,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL, OPEN_EXISTING,
		0,
		NULL);

	if (_pipe == INVALID_HANDLE_VALUE)
		throw std::exception("fail to create client pipe");
}