#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>


struct Client {
	unsigned int id;
	std::string name;
};


class NetworkClient
{
	sf::UdpSocket dataSocket;
	sf::TcpSocket regSocket;

	sf::Packet sendPacket;

	sf::Clock sendRateTimer;
	sf::Int16 sendRate = 2;

	sf::IpAddress S_Ip;
	unsigned short S_regPort;
	unsigned short S_dataPort;
	

public:
	NetworkClient();

	
	sf::Socket::Status init(unsigned short preferablePort = sf::Socket::AnyPort);


	sf::Socket::Status registerOnServer(sf::IpAddress serverIp, unsigned short serverRegPort, std::string clientName);

	sf::Socket::Status receiveConnectedClientsNames(std::vector<Client>& namesVec, int& my_id);


	sf::Socket::Status receiveData(sf::Packet& dataPacket, sf::IpAddress S_Ip, unsigned short S_dataPort);

	sf::Socket::Status sendData(sf::Packet dataPacket);


	void setSendFreq(sf::Int32 milliseconds);
private:
	
	sf::Socket::Status connectRegTcpSocket(sf::IpAddress serverIp, unsigned short serverRegPort);

	sf::Socket::Status sendClientRecipientData(std::string clientName);

	sf::Socket::Status recieveDedicatedDataServerPort();


};