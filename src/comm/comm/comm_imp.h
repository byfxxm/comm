#pragma once

namespace comm
{
	constexpr size_t _msg_length{ 0 };

	class comm_base
	{
	public:
		virtual ~comm_base();
		bool send_msg(const std::string&);
		bool recv_msg(std::string&);

	protected:
		HANDLE _pipe;
		static const wchar_t* _pipe_name;
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