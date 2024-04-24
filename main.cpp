#include "DrawPictures.h"
#include "Factory.h"
#include "FoodInterface.h"


using namespace sf;

const int Num0 = sf::Keyboard::Num1;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    window.clear(sf::Color::White);
    Factory fact;
    DrawPictures obj;
    bool mousePress = false;
    bool mousePressRight = false;
    int object = -1;
    bool isJumping = false;
    Clock clock;
    
    FoodInterface food(1);
    food.gen();
    sf::Vector2i mousePosition;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
       
        time = time / 800;
        sf::Event event;
        while (window.pollEvent(event))
        {      
            switch (event.type) {
                case sf::Event::Closed:window.close();
                case sf::Event::KeyPressed:
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        std::ofstream out("data.bin");
                        obj.save(out);
                        std::ofstream outJ("data.json");
                        obj.saveJson(outJ);
                        break;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        std::ifstream in("data.bin");
                        obj.load(in);
                        break;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        std::ifstream in("data.json");
                        obj.loadJson(in);
                        break;
                    }
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int key = event.key.code;
                    obj.add(fact.createAnimal(Animal_type(key - Num0), sf::Vector2f(mousePosition.x, mousePosition.y)));
                    if (key == sf::Keyboard::Delete) { 
                        obj.del(sf::Vector2f(mousePosition.x, mousePosition.y)); 
                        object = -1;
                    }
                    
                    break;
                }

                case sf::Event::MouseButtonPressed:
                {
                    mousePosition = sf::Mouse::getPosition(window); 
                    object = obj.getObj(sf::Vector2f(mousePosition.x, mousePosition.y)); 

                    if (event.mouseButton.button == sf::Mouse::Left)
                    {

                        if (object != -1) {
                            mousePress = true;
                        }                       
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (object != -1) {
                            mousePressRight = true;
                        }
                    }
                    break;
                }
                case sf::Event::MouseMoved:
                {
                    if (mousePress)
                    {   
                        obj.resize(object, sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                    }
                    else if (mousePressRight) {
                            obj.newPos(object, sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                        }             
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    mousePress = false;
                    mousePressRight = false;
                }
                                      
            }        
                
        }

        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { 
            obj.GoLeft( time, object);
        }

        if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
            obj.GoRight( time, object);

        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
        
            if (!isJumping) {
                isJumping = true;
                obj.restartClock(object);
            }

        }
        if (isJumping) {
            isJumping = obj.Jump(object);
        }
        food.moveall();
      
        window.clear(sf::Color(176, 196, 222));
        food.draw(window);
        obj.draw(window);
        window.display();
    }
   


    return 0;
}