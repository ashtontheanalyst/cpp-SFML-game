/* 
https://www.youtube.com/watch?v=5aWMIpRiuww
https://www.sfml-dev.org/tutorials/3.0/getting-started/linux/

To compile this program run: 
g++ test.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

To run it:
./prog

The output should be a small black window with a green circle
*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}