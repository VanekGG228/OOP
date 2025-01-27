#include "Handler.h"

Handler::Handler()
{
	netS.init();
	timer = new CountdownTimer(30);
	running = true;
	food = new Food(1900,1000);
	send = thread(&Handler::sendQueue, this);
	recieve = thread(&Handler::recieved_data, this);
}

void Handler::main_loop()
{
	while (true)
	{
		if (netS.clientsVec.size() <= 4) {
			netS.registerNewClients();
			netS.sendConnectedClientsRecords();
		}
		//netS.tets();
		game();
	}
}

Handler::~Handler()
{
	send.join();
	recieve.join();
	running = false;
}

void Handler::game()
{
	switch (state) {
	case 0: {
		start_game();
		break;
	}
	case 1: {
		state1();
		break;
	}
	case 2: {
		state2();
		break;
	}
	case 3: {
		state3();
		break;
	}
	case 4: {
		state4();
		break;
	}

	}

}

void Handler::start_game()
{
	if (netS.clientsVec.size() > 0) {

		if (!timer->isRunning()) timer->start();
		else time = timer->getRemainingTime();
		Packet packet;
		packet << "TIMER" << time;
		netS.setDoneFalse();
		if (netS.getModified()) {
			if (netS.sendDataToAll(packet) == sf::Socket::Status::Done) {
				std::cout<<"SENT TIMER"<<std::endl;
			};
			netS.setModified(false);
		}
		if (timer->update() && !timer->isRunning())
			state++;
		packet.clear();
	}

}

void Handler::state1()
{
	for (int i = 0; i < netS.clientsVec.size(); ++i) {
		if (netS.getStatus(i) != 1) {
			return;
		}
	}
	int x = 100;
	Packet packet;
	std::vector<sf::Vector2f> ff = food->getPostions();
	packet << "start_pos" << x << x;
	for (const auto& pos : ff) {
		packet << pos.x << pos.y;
	}
	if (netS.sendDataToAll(packet) == Socket::Status::Done) {
		state++;
	}

}

void Handler::state2()
{
	Packet packet;
	packet << "GO" << GameTime;
	timer->setDuration(GameTime);
	timer->start();
	if (netS.sendDataToAll(packet) == Socket::Status::Done) {
		state++;
	}
}

void Handler::state3()
{
	if (timer->update() && !timer->isRunning()) {
		Packet packet;
		packet << "OVER";

		int max = netS.FindMax();
		for (int i = 0; i < netS.clientsVec.size(); ++i) {
			bool winner;
			winner = (max == netS.clientsVec[i].score);
			packet << i << winner << netS.clientsVec[i].score;
		}
		if (netS.sendDataToAll(packet) == Socket::Status::Done) {
			state++;
			std::cout << "Send over to all";
		}
	}
}

void Handler::state4()
{

}

void Handler::recieved_data()
{
	while (running) {
		if (netS.receiveData(recieve_num) != sf::Socket::Status::Done) continue;

		string action;
		if (netS.clientsVec[recieve_num].rDataPacket >> action) {
			if (action == "START") {

				netS.setStatus(1, recieve_num);
			}
			else if (action == "move") {
				sf::Packet packet;
				float time = 0.0f;
				int moveto = 0;

				packet << "move" << recieve_num;
				while (netS.clientsVec[recieve_num].rDataPacket >> moveto >> time) {
					packet << moveto << time;
					//cout << moveto << "\t";
				}
				//cout << endl;
				que.push(packet);
			}
			else if (action == "interact") {
				Packet packet;
				int foodNum;
				netS.clientsVec[recieve_num].rDataPacket >> foodNum;
				sf::Vector2f pos = food->moveToOppositeSide(foodNum);
				netS.upScore(recieve_num);
				
				packet <<"new_pos"<< foodNum << pos.x << pos.y << recieve_num;
				que.push(packet);
			}

		}
	}
}

void Handler::sendQueue()
{
	while (running) {
		if (!que.empty()) {
			if (netS.sendDataToAll(que.front()) == sf::Socket::Status::Done) {
				que.pop();
			}
		}
	}
}