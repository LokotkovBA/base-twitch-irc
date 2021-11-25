#include "src/Networking/twitchirc.h"
#include "src/Networking/twitchpubsub.h"

#include <codecvt>
#include <locale>
#include <thread>

#define TWITCH_NICKNAME "Segosh_"
#define PATH_TO_OAUTH "D:\\Stuff\\Include\\oauth.txt" //todo: change absolute path to relative

void DoWork()
{
	PlaySound("D:\\Stuff\\Include\\ohno.wav", NULL, SND_FILENAME);
}

int main()
{
	using namespace ChatThing;
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	//std::thread sounder(DoWork);

	//Networking::TwitchIRC* twitchIRC = new Networking::TwitchIRC(TWITCH_NICKNAME, PATH_TO_OAUTH);
	Networking::TwitchPubSub* twitchIRC = new Networking::TwitchPubSub(TWITCH_NICKNAME, PATH_TO_OAUTH);
	
	/*twitchIRC->joinRoom("segosh_");
	std::string test;
	getline(std::cin, test);

	twitchIRC->sendChatMessage("segosh_", test);
	char* buffer = new char[BUFFER_SIZE];
	while (true)
	{
		
		twitchIRC->receiveFromSocket(buffer, BUFFER_SIZE);
	}*/

	delete twitchIRC;
	return 0;
}
