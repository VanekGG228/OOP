#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

struct Client
{
	unsigned status = 0;
	string name;
	IpAddress Ip;
	UdpSocket* dataSocket;
	unsigned short port;
	Packet rDataPacket;
	Packet sDataPacket;
	bool done = true;
	unsigned score = 0;
};

class NetworkServer
{

	short regStep = 0;
	bool modified = false;
	TcpListener listener;
	TcpSocket regSocket;

	Packet packet;

	Clock sendingsRateTimer;
	Int32 sendingsRate = 4;

public:
	vector<Client> clientsVec;
	void setStatus(unsigned st, int i) {
		clientsVec[i].status = st;
	}
	unsigned getStatus(int i) {
		return clientsVec[i].status;
	}

	void setPacket(Packet packet, int i) {
		clientsVec[i].sDataPacket = packet;
	}

	void setModified(bool mod) {
		modified = mod;
	}

	bool getModified() {
		return modified;
	}

	void setDoneFalse() {
		for (int i = 0; i < clientsVec.size(); ++i)
			clientsVec[i].done = false;
	}
	void upScore(int i) {
		clientsVec[i].score++;
	}

	int FindMax() {
		unsigned max = 0;
		for (auto& client : clientsVec) {
			if (max < client.score) {
				max = client.score;
			}
		}

		return max;
	}

	void tets() {
		
		for (int i = 0; i < clientsVec.size(); i++){
			int time = 29;
			clientsVec[i].sDataPacket << "TIMER" << 29;
			if (clientsVec[i].dataSocket->send(clientsVec[i].sDataPacket, clientsVec[i].Ip, clientsVec[i].port) == Socket::Status::Done) {
				std::cout << "SENDED" << std::endl;
			}
			clientsVec[i].sDataPacket.clear();
		}
	}
	NetworkServer();

	Socket::Status init();

	Socket::Status registerNewClients();


	Socket::Status sendConnectedClientsRecords();

	
	Socket::Status receiveData(unsigned int& receivedClientIndex);

	Socket::Status sendDataToAll(Packet dataPacket);

private:

	
	Socket::Status acceptIncomingConnection();

	Socket::Status receiveClientRegData();

	
	Socket::Status sendNewClientDataToAll();

	Socket::Status sendDedicatedDataPort();

};