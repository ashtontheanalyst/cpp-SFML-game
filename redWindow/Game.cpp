// This file implements the logic for the Game class

#include "Game.h" // Brings in the declarations of the Game class

// PRIVATE FUNCTIONS --------------------------------------------------------------------------
void Game::initVariables() {
    // Initializes the window pointer to hold a value of nullptr
    this->window = nullptr;
}

void Game::initWindow() {
    // Setting the screen size
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    // Creates a new SFML window using the pointer this->window
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
}

// Constructor, this will run once Game game; is called in main.cpp
Game::Game() {
    // Calls these private functions to initialize the window and variables
    this->initVariables();
    this->initWindow();
}

// Destructor, runs at the end of main
Game::~Game() {
    delete this->window; // frees the memory we used to create the new window
}


// PUBLIC FUNCTIONS ---------------------------------------------------------------------------

// Accessor, main.cpp is asking if the window is still open or not
const bool Game::running() const {
    return this->window->isOpen();
}

// Get's all the pending events
// Event polling, SFMLs event system allows us to react to things like key inputs, the mouse, etc.
void Game::pollEvents() {
    while(this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            // If the close button is pressed in the window, close it
            case sf::Event::Closed:
                this->window->close();
                break;
            
            // If the 'ESC' key is pressed, do the same thing
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
            break;
        }
    }
}

// Updates the game logic every frame. Could be player movement, an attack, screen explosion, etc.
void Game::update() {
    this->pollEvents(); // Right now we're just updating with this function
}

// Putting out all the pizels on the screen
void Game::render() {
    /*
    - Clear the old frame
    - Render the objects
    - Display frame in the window
    */

    this->window->clear(sf::Color(255, 0, 0, 255)); // Just fills the screen with a color
    // Draw game object
    this->window->display();
}