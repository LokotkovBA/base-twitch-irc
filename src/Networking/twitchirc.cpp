#include "twitchirc.h"

namespace ChatThing
{
	namespace Networking
	{
		TwitchIRC::TwitchIRC(const std::string& name, const std::string& oauthPath):TwitchSocket(name, oauthPath)
		{
			if (init(name, getOauth(oauthPath)) != 0)
			{
				std::cout << "Initialisation failed!";
			}
		}

		int TwitchIRC::init(const std::string& name, const std::string& pass)
		{
			addrinfo hints{ };
			addrinfo* result;

			m_tmiUser = ":" + name + "!" + name + "@" + name + ".tmi.twitch.tv";

			if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0)
			{
				std::cout << "Startup Failed" << std::endl;
				return 1;
			}

			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;

			if (getaddrinfo("irc.twitch.tv", "6667", &hints, &result) != 0)
			{
				std::cout << "getaddrinfo failed" << std::endl;
				WSACleanup();
				return 1;
			}

			m_twitchSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
			if (m_twitchSocket == INVALID_SOCKET)
			{
				std::cout << "Invalid Socket" << std::endl;
				WSACleanup();
				freeaddrinfo(result);
				return 1;
			}

			if (connect(m_twitchSocket, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR)
			{
				closesocket(m_twitchSocket);
				std::cout << "Connect SOCKET ERROR" << std::endl;
				WSACleanup();
				freeaddrinfo(result);
				return 1;
			}

			freeaddrinfo(result);

			if ((sendToSocket("PASS oauth:" + pass) <= 0) || (sendToSocket("NICK " + name) <= 0))
			{
				WSACleanup();
				closesocket(m_twitchSocket);
				return 1;
			}

			char* buffer = new char[BUFFER_SIZE];

			if (receiveFromSocket(buffer, BUFFER_SIZE) <= 0)
			{
				WSACleanup();
				closesocket(m_twitchSocket);
				return 1;
			}

			return 0;
		}

		void TwitchIRC::sendChatMessage(std::string room, std::string message)
		{

			sendToSocket(m_tmiUser + " PRIVMSG #" + room + " :" + message);
			char* buffer = new char[BUFFER_SIZE];

			receiveFromSocket(buffer, BUFFER_SIZE);
		}

		void TwitchIRC::joinRoom(std::string room)
		{
			if (sendToSocket(m_tmiUser + " JOIN #" + room) > 0)
				std::cout << "Joined " + room << std::endl;

			char* buffer = new char[BUFFER_SIZE];
			receiveFromSocket(buffer, BUFFER_SIZE);
		}

		void TwitchIRC::partRoom(std::string room)
		{
			if (sendToSocket(m_tmiUser + " PART #" + room) > 0)
				std::cout << "Parted " + room << std::endl;

			char* buffer = new char[BUFFER_SIZE];
			receiveFromSocket(buffer, BUFFER_SIZE);
		}
	}
}