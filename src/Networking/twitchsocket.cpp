#include "twitchsocket.h"

namespace ChatThing
{
	namespace Networking
	{
		TwitchSocket::TwitchSocket(const std::string& name, const std::string& oauthPath)
		{
			m_twitchSocket = INVALID_SOCKET;
		}

		TwitchSocket::~TwitchSocket()
		{
			WSACleanup();
			closesocket(m_twitchSocket);
		}

		std::string TwitchSocket::getOauth(const std::string& path)
		{
			std::string oauth;
			std::ifstream oauthFile;
			oauthFile.open(path);
			std::getline(oauthFile, oauth);
			oauthFile.close();
			return oauth;
		}

		int TwitchSocket::sendToSocket(std::string message)
		{
			message = message + "\r\n";
			int bytesSend = send(m_twitchSocket, message.c_str(), message.length(), NULL);
			if (bytesSend == SOCKET_ERROR)
			{
				std::cout << "Send SOCKET ERROR" << std::endl;
			}
			return bytesSend;
		}

		int TwitchSocket::receiveFromSocket(char* buffer, int buffersize)
		{
			int bytesRecv = recv(m_twitchSocket, buffer, buffersize, NULL);
			if (bytesRecv == SOCKET_ERROR)
			{
				std::cout << "Receive SOCKET ERROR" << std::endl;
				return bytesRecv;
			}
			if (bytesRecv < BUFFER_SIZE)
				buffer[bytesRecv] = '\0';

			std::cout << buffer << std::endl;
			return bytesRecv;
		}
	}
}