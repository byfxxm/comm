#pragma once

namespace comm
{
	class comm_base_c
	{
	public:
		virtual ~comm_base_c() = default;
		bool send_msg(const std::string&);
		bool recv_msg(std::string&);

	protected:
		HANDLE _pipe;
		const wchar_t* _pipe_name{ LR"(\\.\pipe\comm)" };
	};

	class comm_server_c : public comm_base_c
	{
	public:
		comm_server_c();
		virtual ~comm_server_c() override;
	};

	class comm_client_c : public comm_base_c
	{
	public:
		comm_client_c();
		virtual ~comm_client_c() override;
	};
}