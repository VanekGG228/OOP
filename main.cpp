#include "TInteract.h"
#include <windows.h>
#include "Factory.h"
#include "GameMenu.h"
#include "AdapterInterface.h"
#include "Timer.h"
#include <thread>
#include <atomic>

std::atomic<bool> running(true);

void controlCat(DrawPictures* obj) {
    Clock clock; 
    while (running) { 
        float time = clock.getElapsedTime().asMicroseconds(); 
        clock.restart(); 

        time = time / 800; 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            obj->GoLeft(time, 0); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            obj->GoRight(time, 0); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            obj->GoUp(time, 0); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            obj->GoDown(time, 0); 
        }
    }
}

void controlRabbit(DrawPictures* obj) {
    Clock clock; 
    while (running) { 
        float time = clock.getElapsedTime().asMicroseconds(); 
        clock.restart(); 

        time = time / 800; 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            obj->GoLeft(time, 1); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            obj->GoRight(time, 1); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            obj->GoUp(time, 1); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            obj->GoDown(time, 1); 
        }
    }
}

void controlHorse(DrawPictures* obj) {
    Clock clock; 
    while (running) {
        float time = clock.getElapsedTime().asMicroseconds(); 
        clock.restart();

        time = time / 800;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            obj->GoLeft(time, 2); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            obj->GoRight(time, 2); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
            obj->GoUp(time, 2); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            obj->GoDown(time, 2); 
        }
    }
}

void controlParrot(DrawPictures* obj) {
    Clock clock;
    while (running) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 800;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
            obj->GoLeft(time, 3); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
            obj->GoRight(time, 3); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
            obj->GoUp(time, 3); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
            obj->GoDown(time, 3);
        }
    }
}


using namespace sf;

typedef AdapterInterface* (*CreateInstanceFunc)(); 
void JsonXmlLib(LPCWSTR  lib,std::string in,std::string out,bool type)
{
    LPCWSTR wfilename =lib;
    HMODULE pluginHandle = LoadLibraryW(wfilename);

    if (!pluginHandle) {
        return ;
    }
    CreateInstanceFunc createFunc = (CreateInstanceFunc)GetProcAddress(pluginHandle, "CreateGunInstance");
    if (createFunc == NULL) {
        FreeLibrary(pluginHandle);
        return ;
    }
    AdapterInterface* gunInstance = createFunc();

    if (gunInstance == NULL) {
        FreeLibrary(pluginHandle);
        return ;
    }
    if (type)
        gunInstance->convertJsonToXml(in, out);
    else
        gunInstance->convertXmlToJson(in, out);
    gunInstance->clear();
    
    FreeLibrary(pluginHandle);
    return ;
}

static int Game(int type, int numOfPlayers);

static int ChoosePlayer()
{

    sf::RenderWindow window(sf::VideoMode(1080, 760), "Eat food pls!");

    std::vector<String> name_menu{ "2","3","4" };

    game::GameMenu mymenu(window, 540, 150, 100, 120, name_menu);

    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    mymenu.AlignMenu(2);
    int returnVAL = 2;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased)
            {

                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                if (event.key.code == Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0: {               
                        window.close();  break; 
                    }
                    case 1: { 
                        returnVAL = 3;
                        window.close();  break; 
                    }

                    case 2: {
                        returnVAL = 4;
                        window.close();  break;
                    }
                    default:break;
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {

                switch (mymenu.MouseClick(window))
                {
                case 0: {
                    window.close();  break;
                }

                case 1: {
                    returnVAL = 3;
                    window.close();  break;
                }

                case 2: {
                    returnVAL = 4;
                    window.close();  break;
                }
                default:break;
                }
            }
        }

        window.clear();
        mymenu.draw();
        window.display();
    }
    return returnVAL;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(1080, 760), "Eat food pls!");

	std::vector<String> name_menu{ "EAT FOOD","DONT CAUGHT","EXIT" };

	game::GameMenu mymenu(window,540, 150, 100, 120, name_menu);

	mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
	mymenu.AlignMenu(2);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::KeyReleased)
			{

				if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
				if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
				if (event.key.code == Keyboard::Return)
				{
					switch (mymenu.getSelectedMenuNumber())
					{
                    case 0: Game(1,ChoosePlayer());  break;
                    
					case 1:Game(2, ChoosePlayer());  break;
					case 2:window.close(); break; 
					default:break;
					}

				}
			}
			if (event.type == Event::MouseButtonPressed) {

				switch (mymenu.MouseClick(window))
				{
                case 0: Game(1, ChoosePlayer());  break;
                case 1:Game(2, ChoosePlayer());  break;
				case 2:window.close(); break;
				default:break;
				}
			}
		}

		window.clear();
		mymenu.draw();
		window.display();
	}
	return 0;
}

static int Game(int type,int numOfPlayers)
{
    
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Eat food pls!");
    window.clear(sf::Color::White);
    running = true;
    DrawPictures obj;
    Timer* timer = new Timer(60, 40, 940, 0);
    timer->start();
    
    FoodInterface* food = new FoodInterface(type);
    food->gen();
    TInteract* interact =TInteract::getInstance();
    Table* table; 
    if (type == 1) 
        table = new Table(100, 100);
    else
        table = new Table(100, 100, std::vector<int>{3, 3, 3, 3}); 


    interact->addObserver(table);

    std::thread catThread(controlCat, &obj);  
    std::thread rabbitThread(controlRabbit, &obj);  
    std::thread horseThread(controlHorse, &obj);  
    std::thread parrotThread(controlParrot, &obj);  


    obj.genPlayers(numOfPlayers, 1920, 1080);

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
            case sf::Event::KeyPressed:{
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        std::string x = "data.json";
                        obj.saveJson(x);
                        break;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        std::string in = "data.json";
                        obj.loadJson(in);
                        break;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {

                        JsonXmlLib(L"plugins/JsonToXmlDLL.dll", std::string("data.json"), std::string("converted.xml"), true);
                        break;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                        JsonXmlLib(L"plugins/JsonToXmlDLL.dll",  std::string("converted.xml"), std::string("data.json"), false);                     
                        break;
                    }

                    break;
            }
                                      
            }                    
        }
        /*if ((Keyboard::isKeyPressed(Keyboard::Space))) {
        
            if (!isJumping) {
                isJumping = true;
                obj->restartClock(object);
            }

        }
        if (isJumping) {
            isJumping = obj->Jump(object);
        }*/

        food->moveall(); 
        timer->update();
        interact->interactObjects(obj.animals, food->food);
        interact->update();

        window.clear(sf::Color(176, 196, 222));
        if (timer->getEnd()) {
            table->finalScore(1920, 1080);
            table->draw(window);
            window.display();
            running = false;
            sf::sleep(sf::seconds(4));
            window.close();
        }

        food->draw(window);
        timer->draw(window);
        if (Keyboard::isKeyPressed(Keyboard::Tab)) table->draw(window);
        interact->draw(window);
        obj.draw(window);
        window.display();
    }
    
    catThread.join();
    rabbitThread.join();
    horseThread.join();
    parrotThread.join();
    delete interact, table, food, timer;
    return 0;
}