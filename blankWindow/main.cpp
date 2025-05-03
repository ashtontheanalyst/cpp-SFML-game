#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main() {

    // sf is a namespace for sfml
    // Making a basic pop up window with width, height, title of the window,
    // with a title bar, close button, and it's NOT resizeable
    sf::RenderWindow window(sf::VideoMode(640, 480), "My First Blank Window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    
    // Make an event, this captures things that happen on the computer like key press, etc.
    sf::Event ev;

    // Game loop, if the window is open, do this...
    while(window.isOpen()) {
        
        // Events
        // While something happens in the window, track the event to ev
        while(window.pollEvent(ev)) {
            
            // Depending on the type of event that happens like a click, key, do this...
            switch (ev.type) {
                // When we click the close button, it sends a signal to close the window
                case sf::Event::Closed:
                    window.close();
                    break;
                
                // When a key is pressed, do this...
                case sf::Event::KeyPressed:
                    // If the event key is the esacpe key..
                    if (ev.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
            }
        }

        // Update, this is where you'd update anything in a normal game loop

        // Rendering, clear the frame, draw new stuff, display it
        window.clear(sf::Color::Green); // clears the old frame, makes the frame a color
        // This works too 'window.clear(sf::Color(255,255,255,255));'
        // This is where you'd do any building, rendering, etc. in between
        window.display(); // tell the app that the window is done drawing, displays it
    }

    // End of game
    return 0;
}