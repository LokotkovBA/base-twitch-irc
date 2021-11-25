#pragma once
#include "twitchsocket.h"


namespace ChatThing
{
	namespace Networking
	{
		class TwitchIRC : public TwitchSocket
		{
		public:
			TwitchIRC(const std::string& name, const std::string& oauthPath);
			void sendChatMessage(std::string room, std::string message);
			void joinRoom(std::string room);
			void partRoom(std::string room);
		private:
			int init(const std::string& name, const std::string& pass) override;
		private:
			std::string m_tmiUser;
			WSAData m_wsaData;
		};
	}
}
