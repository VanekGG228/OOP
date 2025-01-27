#include "HandlerNetwork.h"
#include "GameMenu.h"

HandlerNetwork::HandlerNetwork(sf::IpAddress t_S_Ip, unsigned short t_S_port, std::string clientName, ControllerBase* ctr)
	: window(sf::VideoMode::getDesktopMode(), "Eat food pls!", sf::Style::Fullscreen),
	timer1(60, 40, 940, 0),  
	timer2(60, 100, 900, 500),  
	food(1),                 
	animals(),                
	result(window),          
	controller(ctr),
	table(100, 100),
	S_Ip(t_S_Ip),
	S_port(t_S_port)
{
	netC.init();
	netC.registerOnServer(S_Ip, S_port, clientName);
	netC.receiveConnectedClientsNames(clients, id);

	window.clear(sf::Color::White);
	interact = TInteract::getInstance();  
	

	interact->addObserver(&table);

	recieveThread = std::thread(&HandlerNetwork::recieve_data, this);
	sendThread = std::thread(&HandlerNetwork::sendQueue, this);
}

sf::Socket::Status HandlerNetwork::send_data(sf::Packet packet)
{
	return netC.sendData(packet);
}

void HandlerNetwork::main_loop()
{
	sf::Clock clock;
	float time;
	window.setFramerateLimit(144);
	std::vector<sf::String> name_menu{"EXIT" };

	game::GameMenu mymenu(window, 940, 450, 100, 120, name_menu);

	mymenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
	mymenu.AlignMenu(2);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed: {
					running = false;
					window.close();
				}

			
				case sf::Event::MouseButtonPressed:
				{

					switch (mymenu.MouseClick(window))
					{
					case 0: {
						running = false;
						window.close();  
						break;
					}
					default:break;
					}
					break;
				}
			}
		}
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		if (state == 2) {
			//std::cout << timer1.getTime()<< std::endl;
			control(time);
		}

		if (state == 2) {
			timer1.update();
		}
				
		if (timer2.getEnd() && state == 1) {
			sendStart();
		}
		sf::Packet packet = interact->interactObjects(animals.animals, food.food, this->id);
		if (packet.getDataSize() != 0) {
			packetQueue.push(packet);
		}
		interact->update();

		window.clear(sf::Color(176, 196, 222));

		if (timer1.getEnd()) {

		}
	    
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) table.draw(window);
		
		
		if (state ==1){
			timer2.update();
			timer2.draw(window);
		}
		if (state == 2) {
			food.draw(window);
			timer1.draw(window);
			animals.draw(window);
			interact->draw(window);
		}
		if (state == 3) {
			result.draw();
			//sleep(3);
			mymenu.draw();
		}
		
		
		
		window.display();
	}
	state = 0;
	//catThread.join();
	recieveThread.join();
	sendThread.join();
	delete interact;
	return;
}

void HandlerNetwork::sendStart()
{
	sf::Packet packet;
	packet << "START";
	netC.sendData(packet);
}

void HandlerNetwork::control(float time)
{
	controller->control(time, packetQueue, window, &animals, id);
}


void HandlerNetwork::sendQueue()
{
		while (running) {
			if (!packetQueue.empty()){
				if (send_data(packetQueue.front()) == sf::Socket::Status::Done) {
					packetQueue.pop();
				}
			}
		}
}


void HandlerNetwork::recieve_data()
{
	while (state > 0) {
		sf::Packet packet;
		if (netC.receiveData(packet, S_Ip, S_port) == sf::Socket::Status::Done) {
			std::string action;
			if (packet >> action) {
				if (action == "move") {	
					int t_id;
					float time = 0.0f;
					int moveto = 0;
					packet >> t_id;
					while (packet >> moveto >> time) {
					
						if (t_id != this->id) {
							switch (moveto) {
							case 2: {
								animals.GoLeft(time, t_id);
								break;
							}
							case 3: {
								animals.GoRight(time, t_id);
								break;
							}
							case 4: {
								animals.GoUp(time, t_id);
								break;
							}
							case 5: {
								animals.GoDown(time, t_id);
								break;
							}
							}
						}
					}					
				}
				else if (action == "new_pos") {
					unsigned player;
					int num;
					float x, y;
					packet >> num >> x >> y >> player;
					interact->notifyTable(player);
					food.update(num, x, y);

				}
				else if (action == "TIMER") {
					int time;
					packet >> time;
					timer2.setStartTime(time);
					timer2.start();

				}
				else if (action == "start_pos") {
					int x, y;
					packet >> x >> y;
					animals.setXY(x, y);
					std::vector<sf::Vector2f> ff;
					while (!packet.endOfPacket()) {
						float x, y;
						packet >> x >> y;
						ff.push_back(sf::Vector2f(x, y));
					}
					food.gen(ff);
					controller->setState(2);

				}
				else if (action == "GO") {
					int time;
					packet >> time;
					timer1.setStartTime(time);
					timer1.start();
					state = 2;
					animals.genPlayers(clients);

				}
				else if (action == "NEW") {
					std::string name;
					int id;
					packet >> name >> id;
					Client cli{ id, name };
					clients.push_back(cli);
				}
				else if (action == "OVER") {
					while (!packet.endOfPacket()) {
						unsigned score;
						int id;
						bool winner;
						packet >> id >> winner >> score;
						if (id == this->id) result.setResult(winner);
						result.addRow(animals.getName(id),score);
					}
					std::cout << "OVER";
					state = 3;
					controller->setState(0);
				}
			}
			packet.clear();
		}
	}
}