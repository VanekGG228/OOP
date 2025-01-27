#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "Handler.h"


using namespace sf;
using namespace std;


int main()
{
	std::cout << sf::IpAddress::getLocalAddress()<<std::endl;
	Handler* handler = new Handler();
	handler->main_loop();
	delete handler; 
	return 0;
}