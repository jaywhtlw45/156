#include <SFML/Graphics.hpp>
#include <iostream>

const int NUM_BUTTONS = 9;

void createButtons(sf::RectangleShape (&buttons)[NUM_BUTTONS]);
void eventHandler(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape (&buttons)[NUM_BUTTONS]);
void drawButtons(sf::RenderWindow &window, sf::RectangleShape (&buttons)[NUM_BUTTONS]);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe");

    // Create a buttons
    sf::RectangleShape buttons[NUM_BUTTONS];

    createButtons(buttons);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // if window is closed
            if (event.type == sf::Event::Closed)
                window.close();

            eventHandler(window, event, buttons);
        }

        // erase the page
        window.clear();

        // draw the buttons
        // drawButtons(window, buttons, buttonFlag);
        for (int i = 0; i < NUM_BUTTONS; i++)
            window.draw(buttons[i]);

        // display the page
        window.display();
    }

    return 0;
}

void eventHandler(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape (&buttons)[NUM_BUTTONS])
{
    // Handle buttons click
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (int i = 0; i < NUM_BUTTONS; i++)
            {
                sf::FloatRect buttonBounds = buttons[i].getGlobalBounds();
                if (buttonBounds.contains(mousePos.x, mousePos.y))
                {
                    std::cout << "Button " << i << " Clicked" << std::endl;
                    buttons[i].setFillColor(sf::Color::Red);
                }
            }
        }
    }
}

void createButtons(sf::RectangleShape (&buttons)[NUM_BUTTONS])
{
    int x, y;
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (i < 3)
        {
            x = 300 + (i%3)*60, y = 100;
            buttons[i].setSize(sf::Vector2f(50, 50));
            buttons[i].setPosition(x, y);
            buttons[i].setFillColor(sf::Color::Green);
            std::cout << "Button " << i << " x: " << x << " y: " << y << std::endl;
        }
        else if (i < 6)
        {
           x = 300 + (i%3)*60, y = 160;
            buttons[i].setSize(sf::Vector2f(50, 50));
            buttons[i].setPosition(x, y);
            buttons[i].setFillColor(sf::Color::Green);
            std::cout << "Button " << i << " x: " << x << " y: " << y << std::endl;
        }
        else
        {
            x = 300 + (i%3)*60, y = 220;
            buttons[i].setSize(sf::Vector2f(50, 50));
            buttons[i].setPosition(x, y);
            buttons[i].setFillColor(sf::Color::Green);
            std::cout << "Button " << i << " x: " << x << " y: " << y << std::endl;
        }
    }
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