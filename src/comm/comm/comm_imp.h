#pragma once

namespace comm
{
	class comm_base
	{
	public:
		virtual ~comm_base();
		void send_msg(const std::string&);
		void recv_msg(std::string&);

	protected:
		HANDLE _pipe;
		const wchar_t* _pipe_name = L"\\\\.\\pipe\\comm";
	};

	class comm_server : public comm_base
	{
	public:
		comm_server();
		virtual ~comm_server() override;
	};

	class comm_client : public comm_base
	{
	public:
		comm_client();
		virtual ~comm_client() override = default;
	};
}