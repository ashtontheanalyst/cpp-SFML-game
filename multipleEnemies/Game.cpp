// This file implements the logic for the Game class
// this->enemy is like writing Game::enemy, the 'this' is referencing Game!!

#include "Game.h" // Brings in the declarations of the Game class

// PRIVATE FUNCTIONS --------------------------------------------------------------------------
void Game::initVariables() {
    // Initializes the window pointer to hold a value of nullptr
    this->window = nullptr;

    // Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax; // timer starts at its max value
    this->maxEnemies = 5;
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

    // Move all the enemies downward
    for (size_t i = 0; i < this->enemies.size(); ++i) {
        this->enemies[i].move(0.f, 1.f);
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
    for (size_t i = 0; i < this->enemies.size(); ++i) {
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