#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    bool mouseReleased = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)        // x button is pushed
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                std::cout << "Mouse button pressed" << std::endl;
            }

            if (event.type == sf::Event::KeyReleased){
                std::cout << "A key was pressed" << std::endl;
                if(event.key.code == sf::Keyboard::W){
                    std::cout<< "\t specifically the w key" << std::endl;
                }
            }
            
            mouseReleased = false;
            if (event.type == sf::Event::MouseButtonReleased){
                mouseReleased= true;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseReleased){
            std::cout << "Left mouse pressed" <<std::endl;
        }

        window.clear();         // erase the page
        window.draw(shape);     // draw on the page
        window.display();       // display the page
    }

    return 0;
}

// sudo apt-get install libsfml-dev


// 1. Setup
//     Window
//     Shapes

// 2. Applicaiton Loop--- 3 steps run on a loop
//      1. input
//              create events and put them in a queue
//      2. updates
//      3. Display/Rendr

// 3. Cleanup