#include "BotServer.h"
#include "BotServer.h"
#include <iostream>
#include <sstream>

bool BotServer::init(int port)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) return false;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, SOMAXCONN);

    return clientSocket != INVALID_SOCKET;
}

void BotServer::sendEnemyPosition(const std::vector<sf::RectangleShape>& positions)
{
	std::ostringstream oss;
	oss << "ENEMIES ";
	for (const auto& pos : positions)
	{
		oss << " " << pos.getPosition().x << " " << pos.getPosition().y << "\n";
	}

	std::string data = oss.str();
	send(clientSocket, data.c_str(), data.size(), 0);
}



bool BotServer::receiveClick(float& x, float& y)
{
	char buf[256];
	int bytesReceived = recv(clientSocket, buf, 256, 0);
	if (bytesReceived <= 0) return false;

	std::istringstream iss(std::string(buf, bytesReceived));
	std::string command;
	iss >> command;
	if (command == "CLICK")
	{
		iss >> x >> y;
		return true;
	}

	return false;
}

void BotServer::close()
{
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
}
