#pragma once

namespace comm
{

	class comm_base
	{
	public:
		void send(const char*, int);
		void recv(char*, int, int&);

	protected:
		HANDLE _pipe;
		const wchar_t* _pipe_name = L"\\\\.\\pipe\\comm";
	};

	class comm_server : public comm_base
	{
	public:
		comm_server();
	};

	class comm_client : public comm_base
	{
	public:
		comm_client();
	};
}