#include "Network.h"

NetworkClient::NetworkClient()
{
}

sf::Socket::Status NetworkClient::init(unsigned short preferablePort)
{
	sf::Socket::Status status = dataSocket.bind(preferablePort);

	if (status == sf::Socket::Status::Done)
	{
		std::cout << "init(): Successfully binded to port: " << dataSocket.getLocalPort() << std::endl;
		return sf::Socket::Status::Done;
	}
	else
	{
		std::cout << "(!)init(): Failed to bind passed preferred port\n";
		do
		{
			unsigned short newPort = sf::Socket::AnyPort;
			std::cout << "init(): Trying to bind other port - " << newPort << std::endl;
			status = dataSocket.bind(newPort);
			if (status != sf::Socket::Status::Done)
				std::cout << "(!)init(): Failed to bind other port. Retrying...\n";

		} while (status != sf::Socket::Done);

		std::cout << "init(): Successfully binded to other port - " << dataSocket.getLocalPort() << std::endl;
		return sf::Socket::Status::Done;
	}
}

sf::Socket::Status NetworkClient::registerOnServer(sf::IpAddress serverIp, unsigned short serverRegPort, std::string clientName)
{
	if (connectRegTcpSocket(serverIp, serverRegPort) != sf::Socket::Status::Done)
		return sf::Socket::Status::Error;

	if (sendClientRecipientData(clientName) != sf::Socket::Status::Done)
		return sf::Socket::Status::Error;

	if (recieveDedicatedDataServerPort() != sf::Socket::Status::Done)
		return sf::Socket::Status::Error;

}

sf::Socket::Status NetworkClient::receiveConnectedClientsNames(std::vector<Client>& namesVec, int& my_id)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	sf::Packet tempPacket;

	if (regSocket.receive(tempPacket) == sf::Socket::Status::Done)
	{
		if (tempPacket.getDataSize() > 0)
		{
			int id = 0;
			while (!tempPacket.endOfPacket())
			{
				std::string name;
				
				if (tempPacket >> name >> id)
				{
					Client client = { id,name };
					namesVec.push_back(client);
				}
				else
				{
					std::cout << "(!)receiveConnectedClientsNames() : Failed to read packet\n";
					return sf::Socket::Status::Error;
				}
			}
			my_id = id;
			std::cout << "receiveConnectedClientsNames() :Client names read\n";
			return sf::Socket::Status::Done;

		}
		else std::cout << "(!)receiveConnectedClientsNames(): Receives packet is empty, ensure that packet contains: (string name1 << string name2 << ...) or \"FIRST\" if it's first connected client\n";
	}
	else std::cout << "(!)receiveConnectedClientsNames(): Failed to receive clients names\n";

	return sf::Socket::Status::Error;
}

sf::Socket::Status NetworkClient::receiveData(sf::Packet& dataPacket, sf::IpAddress S_Ip, unsigned short S_dataPort)
{
	if (dataSocket.isBlocking())dataSocket.setBlocking(false);

	
	if (dataSocket.receive(dataPacket, S_Ip, S_dataPort) == sf::Socket::Status::Done)
	{


		if (dataPacket.getDataSize() > 0)
		{
			return sf::Socket::Status::Done;
		}
		else
		{
			std::cout << "(!)receiveData(): Received packet is empty\n";
			return sf::Socket::Status::Error;
		}


	}
	return sf::Socket::Status::NotReady;
}

sf::Socket::Status NetworkClient::sendData(sf::Packet dataPacket)
{
	if (sendRateTimer.getElapsedTime().asMilliseconds() > sendRate)
	{
		if (dataSocket.isBlocking())dataSocket.setBlocking(false);

		if (sendPacket.getDataSize() == 0) sendPacket = dataPacket;
		//sendPacket = dataPacket;
		sf::IpAddress tempIp = S_Ip;
		unsigned short tempDataPort = S_dataPort;
		if (dataSocket.send(sendPacket, tempIp, tempDataPort) == sf::Socket::Status::Done)
		{
			sendPacket.clear();
			sendRateTimer.restart();
			return sf::Socket::Status::Done;
		}
		else { 
			std::cout << "socket is no readya";
			return sf::Socket::Status::NotReady;
		}
	}
	else return sf::Socket::Status::NotReady;
}

void NetworkClient::setSendFreq(sf::Int32 milliseconds)
{
	sendRate = milliseconds;
}

sf::Socket::Status NetworkClient::connectRegTcpSocket(sf::IpAddress serverIp, unsigned short serverRegPort)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	if (regSocket.connect(serverIp, serverRegPort, sf::seconds(10)) == sf::Socket::Status::Done)
	{
		std::cout << "connectRegTcpSocket(): Connected to server\n";
		S_Ip = serverIp;
		S_dataPort = serverRegPort;
		return sf::Socket::Status::Done;
	}
	else
	{
		std::cout << "(!)connectRegTcpSocket(): Error connecting to server!\n";
		return sf::Socket::Status::Error;
	}
}

sf::Socket::Status NetworkClient::sendClientRecipientData(std::string clientName)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	sf::Packet tempPacket;
	tempPacket << clientName << static_cast<sf::Uint16>(dataSocket.getLocalPort());
	//std::cout << tempPacket;

	if (regSocket.send(tempPacket) == sf::Socket::Status::Done)
	{
		std::cout << "sendClientRecipientData(): Successfully sent client recipient data\n";
		return sf::Socket::Status::Done;
	}
	else
	{
		std::cout << "(!)sendClientRecipientData(): Failed to send client recipient data\n";
		return sf::Socket::Status::Error;
	}
}

sf::Socket::Status NetworkClient::recieveDedicatedDataServerPort()
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	sf::Packet tempPacket;

	if (regSocket.receive(tempPacket) == sf::Socket::Status::Done)
	{
		if (tempPacket.getDataSize() > 0)
		{
			if (tempPacket.getDataSize() == sizeof(sf::Uint16))
			{
				if (tempPacket >> S_dataPort)
				{
					std::cout << "recieveDedicatedDataServerPort(): Successfully received data client-dedicated port of a server - " << S_dataPort << std::endl;
					return sf::Socket::Status::Done;
				}
				else std::cout << "(!)recieveDedicatedDataServerPort(): Failed to read from received packet\n";
			}
			else std::cout << "(!)recieveDedicatedDataServerPort(): Invalid packet size, ensure that server sends only Uint16 var\n";
		}
		else std::cout << "(!)recieveDedicatedDataServerPort(): Received packet is empty\n";
	}
	else std::cout << "(!)recieveDedicatedDataServerPort(): Failed to receive client-dedicated port of a server\n";

	return sf::Socket::Status::Error;
}