#include <iostream>
#include <string>
#include <vector>

#include <winsock2.h>

using namespace std;

int main()
{
	cout << "EYESENGINE SERVER" << endl;
	cout << "->Server start: OK" << endl;

	//Variable
	WSADATA WSAData;
	SOCKET sock, csock;
	SOCKADDR_IN sin, csin;
	vector<std::string> clientList;

	cout << "->Server initialisation: In progress..." << endl;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	//Server ini
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4148);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (SOCKADDR*)&sin, sizeof(sin));
	listen(sock, 0);

	cout << "->Server listen..." << endl;
	while (1) //No close
	{
		int sinsize = sizeof(csin);
		if ((csock = accept(sock, (SOCKADDR*)&csin, &sinsize)) != INVALID_SOCKET)
		{
			if (clientList.size() < 200)
			{
				cout << "->Client connect" << endl;

				string playerName = "Player" + to_string(clientList.size());
				clientList.push_back(playerName);
				cout << "Pseudo: " << playerName << " ID: " << clientList.size() << endl;

				string aboutPlayer = to_string(clientList.size()) + playerName + '\0';

				int counter = playerName.size() + 2;
				char *str = new char[counter];
				memset(str, 0, sizeof(str));

				str[0] = clientList.size();
				strcat(str, playerName.c_str());

				send(csock, str, counter, 0);

				delete str;
			}
			else
				cout << "->Server Full, connexion refuse" << endl;
		}
	}

	return 0;
}