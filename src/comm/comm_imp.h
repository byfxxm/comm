#pragma once

namespace comm {
	class CommBase {
	public:
		virtual ~CommBase() = default;
		bool send_msg(const std::string&);
		bool recv_msg(std::string&);

	protected:
		HANDLE pipe_;
		const wchar_t* pipe_name_{ LR"(\\.\pipe\comm)" };
	};

	class CommServer : public CommBase {
	public:
		CommServer();
		virtual ~CommServer() override;
	};

	class CommClient : public CommBase {
	public:
		CommClient();
		virtual ~CommClient() override;
	};
}