// This file implements the logic for the Game class
// this->enemy is like writing Game::enemy, the 'this' is referencing Game!!

#include "Game.h" // Brings in the declarations of the Game class

// PRIVATE FUNCTIONS --------------------------------------------------------------------------
void Game::initVariables() {
    // Initializes the window pointer to hold a value of nullptr
    this->window = nullptr;

    // Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f; // Making this smaller means enemies spawn faster, larger number is the opp.
    this->enemySpawnTimer = this->enemySpawnTimerMax; // timer starts at its max value
    this->maxEnemies = 30;
    this->mouseHeld = false; // not currently holding down on the mouse, looking for indiv. clicks
}


void Game::initWindow() {
    // Setting the screen size
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    // Creates a new SFML window using the pointer this->window
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60); // Set the refresh rate at 60Hz
}


void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(20.f, 20.f)); // Sets the potion of the enemy at (60, 100)
    // For positioning, the x is from left (0) to right (max), the y is from top (0) to bottom (max)
    
    // the setSize function makes us use this Vector2f one, then we put in const sizes (h/w pixels)
    this->enemy.setSize(sf::Vector2f(100.f, 100.f)); // the .f signifies it's a float value
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f)); // cuts the size in half since this is a scaling function

    // The rest of these are filling out what the enemy is, what it looks like, etc.
    this->enemy.setFillColor(sf::Color::Blue);
    this->enemy.setOutlineColor(sf::Color::Magenta);
    this->enemy.setOutlineThickness(2.f);
}


// Constructor, this will run once Game game; is called in main.cpp
Game::Game() {
    // Calls these private functions to initialize the window and variables
    this->initVariables();
    this->initWindow();
    this->initEnemies();
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


// Spawns our enemies and sets random positions, adds it to the vector
void Game::spawnEnemy() {
    this->enemy.setPosition(
        // boundary values between 0 and the window sizing, static cast to int's
        // pick a random value between those int's and static cast that value into a float
        // the y value is just the top of the screen, 0.f
        static_cast<float> (rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );
    
    this->enemies.push_back(this->enemy); // adds the just made enemy to the enemies vector
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


// Updates and stores the mouse positions within the game window
void Game::updateMousePositions() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow); // window coords casted to view in floats
}


// Updates the enemy spawn timer and spawns enemies when the on-screen amount is smaller than the max
void Game::updateEnemies() {
    // if we have less enemies than the max amount...
    if (this->enemies.size() < this->maxEnemies) {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy(); // spawn an enemy
            this->enemySpawnTimer = 0.f; // this resets the timer
        }
        else {
            this->enemySpawnTimer += 1.f; // or increase it if it's less than the max
        }
    }

    // Move and update the enemies, check if they're under screen
    for (int i = 0; i < this->enemies.size(); i++) {
        this->enemies[i].move(0.f, 5.f); // moving them downward at a rate of 5 pixels/second

        // if the top pixel of the enemy falls below the screen, delete
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i); // delete the enemy at it's potion in the vector
        }
    }

    // Kill the enemy
    // Check if the enemy has been clicked, if the left mouse button returns true from isButtonPressed()...
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        
        // making sure the mouse isn't being held, has to be an indiv. click
        if (this->mouseHeld == false) {
            
            this->mouseHeld = true; // saying there's a click for ONLY this iteration
            bool deleted = false; // contitonal for killing the enemy

            for (int i = 0; i < this->enemies.size() && deleted == false; i++) {
                // getGlobalBounds gets the coordinates of the enemy, where is it and how large ish
                // contains will then check our vector to see if the mouse is inside the enemy box
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    this->points += 10.f; // 10 points per enemy
                }
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}


// Updates the game logic every frame. Could be player movement, an attack, screen explosion, etc.
void Game::update() {
    this->pollEvents(); // looking for inputs
    this->updateMousePositions(); // capture mouse movement data
    this->updateEnemies(); // get enemy positions and backend
}


void Game::renderEnemies() {
    // Rendering all the enemies
    for (int i = 0; i < this->enemies.size(); i++) {
        this->window->draw(this->enemies[i]);
    }
}


// Putting out all the pizels on the screen
void Game::render() {
    /*
    - Clear the old frame
    - Render the objects
    - Display frame in the window
    */

    this->window->clear(); // clears the screen to black between frames
    this->renderEnemies(); // draw the enemies on the screen
    this->window->display();
}