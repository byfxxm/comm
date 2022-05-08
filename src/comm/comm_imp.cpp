#include "pch.h"
#include "comm_imp.h"

bool CommBase::send_msg(const std::string& msg) {
	if (!WriteFile(pipe_, std::to_string(msg.length()).c_str(), sizeof(size_t), NULL, NULL))
		return false;

	if (!WriteFile(pipe_, msg.c_str(), (DWORD)msg.length(), NULL, NULL))
		return false;

	return true;
}

bool CommBase::recv_msg(std::string& msg) {
	constexpr auto len_size = sizeof(size_t);
	char len[len_size]{};

	if (!ReadFile(pipe_, len, len_size, NULL, NULL))
		return false;

	auto length = std::stoul(std::string(len));
	DWORD actual_size = 0;
	char buff[1024]{};
	msg.clear();

	do {
		if (!ReadFile(pipe_, buff, sizeof(buff) - 1, &actual_size, NULL))
			return false;

		msg += buff;
		length -= actual_size;
	} while (length != 0);

	return true;
}

CommServer::~CommServer() {
	DisconnectNamedPipe(pipe_);
	CloseHandle(pipe_);
}

CommServer::CommServer() {
	pipe_ = CreateNamedPipe(pipe_name_,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		NMPWAIT_WAIT_FOREVER,
		0);

	if (pipe_ == INVALID_HANDLE_VALUE)
		throw std::exception("fail to create server pipe");

	if (!ConnectNamedPipe(pipe_, NULL))
		throw std::exception("fail to create pipe");
}

CommClient::~CommClient() {
	CloseHandle(pipe_);
}

CommClient::CommClient() {
	while (!WaitNamedPipe(pipe_name_, NMPWAIT_WAIT_FOREVER))
		std::this_thread::yield();

	pipe_ = CreateFile(pipe_name_,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL, OPEN_EXISTING,
		0,
		NULL);

	if (pipe_ == INVALID_HANDLE_VALUE)
		throw std::exception("fail to create client pipe");
}