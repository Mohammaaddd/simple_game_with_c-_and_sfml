#pragma once

#define NOMINMAX

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>



#pragma comment(lib, "ws2_32.lib")

class BotServer
{
private:
	SOCKET serverSocket, clientSocket;
	sockaddr_in serverAddr, clientAddr;

public:
	bool init(int port = 54000);
	void sendEnemyPosition(const std::vector<sf::RectangleShape>& positions);
	bool receiveClick(float& x, float& y);
	void close();
};

