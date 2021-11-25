#pragma once
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

#define BUFFER_SIZE 512

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

namespace ChatThing
{
	namespace Networking
	{
		class TwitchSocket
		{
		public:
			TwitchSocket(const std::string& name, const std::string& oauthPath);
			~TwitchSocket();
			int sendToSocket(std::string message);
			int receiveFromSocket(char* buffer, int buffersize);

		protected:
			virtual int init(const std::string& name, const std::string& pass) { return 1; }
			static std::string getOauth(const std::string& path);
		protected:
			SOCKET m_twitchSocket;
		};
	}
}