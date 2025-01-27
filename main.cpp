
#include <SFML/Network.hpp>
#include <windows.h>
#include "GameMenu.h"
#include "HandlerNetwork.h"
#include "Input.h"
#include "TextLabel.h"
#include "ControllerKeyBoard.h"
#include "ControllerDisk.h"


static int Game(int type, int numOfPlayers);

sf::IpAddress S_Ip;
unsigned short S_port;
std::string clientName;
bool DiskContr = false;

static int ChoosePlayer()
{

    sf::RenderWindow window(sf::VideoMode(1080, 760), "Eat food pls!");

    std::vector<sf::String> name_menu{ "NEXT" };
  
    game::GameMenu Button(window, 400, 570, 100, 120, name_menu);
    InputBox inputBox1(100, 100, 800, 50,"IP");
    InputBox inputBox2(100, 300, 800, 50, "PORT");
    InputBox inputBox3(100, 500, 800, 50, "NAME");

    int returnVAL = 2;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            inputBox1.handleEvent(event);
            inputBox2.handleEvent(event);
            inputBox3.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed) {

                if (Button.MouseClick(window) == 0)
                { 
                    S_Ip = inputBox1.getInput();
                    S_port = static_cast<unsigned short>(std::stoi(inputBox2.getInput()));
                    clientName = inputBox3.getInput();
                    if ((S_port == 0) || (clientName == "")) {
                        break;
                    }
                    else {

                        window.close();
                    }
                }
            }
			if (event.type == sf::Event::Closed) {
				window.close();
				return -1;
			}
        }
        
        window.clear();
        Button.draw();
        inputBox1.draw(window);
        inputBox2.draw(window);
        inputBox3.draw(window);
        window.display();
    }
    return returnVAL;
}

static void Settings();



int main()
{

    sf::RenderWindow window(sf::VideoMode(1080, 760), "Eat food pls!");

	std::vector<sf::String> name_menu{ "EAT FOOD","DONT CAUGHT","SETTINGS","EXIT" };

	game::GameMenu mymenu(window,540, 150, 100, 120, name_menu);

	mymenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
	mymenu.AlignMenu(2);

	while (window.isOpen())
	{
        sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
			{

				if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); }
				if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); }
				if (event.key.code == sf::Keyboard::Return)
				{
					switch (mymenu.getSelectedMenuNumber())
					{
					case 0:
					{
						int returnVal = ChoosePlayer();
						if (returnVal == -1) break;
						Game(1, returnVal);
						break;
					}

					case 1:
					{
						//Game(1, 1);
						break;
					}
					case 2:Settings(); break;
					case 3:window.close(); break;
				    default:break;
					}

				}
				break;
			}

			case sf::Event::MouseButtonPressed:
			{

				switch (mymenu.MouseClick(window))
				{
				case 0: Game(1, ChoosePlayer());  break;
				case 1:Game(2, ChoosePlayer());  break;
				case 2:Settings(); break;
				case 3:window.close(); break;
				default:break;
				}
				break;
			}
			case sf::Event::Closed: {
				window.close();
				break;
			}
			default:
				break;
			}
			
		}

		window.clear();
		mymenu.draw();
		window.display();
	}
	return 0;
}



int Game(int type,int numOfPlayers)
{
	sf::IpAddress serverIp("192.168.150.3");
	unsigned short port = 9998;
	ControllerBase* ctr = new ControllerKeyboard();
	//DiskContr = true;
	if (DiskContr) {
		ctr = new ControllerDisk(serverIp, port);
	}
    HandlerNetwork* handlerNet = new HandlerNetwork(S_Ip, S_port, clientName,ctr);
    handlerNet->main_loop();
	delete ctr, handlerNet;
    return 0;
}

void Settings()
{

	sf::RenderWindow window(sf::VideoMode(1080, 760), "Settings");
	//TextLabel* labelSettings = new TextLabel("Settings", "font/troika.otf", 90, sf::Color::White, { 30, 10 });
	TextLabel* labelContr = new TextLabel("Controller", "font/troika.otf", 60, sf::Color::White, sf::Color::Black, { 1080,80 }, { 0, 80 },TextLabel::Alignment::Left);

	std::vector<sf::String> name_menu{ "OFF" };

	game::GameMenu mymenu(window, 500,75, 70, 120, name_menu);

	mymenu.setColorTextMenu(sf::Color::Magenta, sf::Color::Red, sf::Color::Black);
	mymenu.AlignMenu(2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
			{

				if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); }
				if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); }
				if (event.key.code == sf::Keyboard::Return)
				{
					switch (mymenu.getSelectedMenuNumber())
					{
					case 0: {
						mymenu.renameCol(0, DiskContr ? "OFF" : "ON");
						DiskContr = !DiskContr;
						break;
					}
					default:break;
					}

				}
				break;
			}

			case sf::Event::MouseButtonPressed:
			{

				switch (mymenu.MouseClick(window))
				{
				case 0: {
					mymenu.renameCol(0, DiskContr ? "OFF" : "ON");
					DiskContr = !DiskContr;
					break;
				}
				default:break;
				}
				break;
			}
			
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			}
			

		}
		window.clear(sf::Color(192, 192, 192));
		labelContr->draw(window);
		//labelSettings->draw(window);
		mymenu.draw();
		window.display();
	}
	return;
}

