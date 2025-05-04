// This file declares and defines the structure of the Game class
// Declares what the class will have and do

#pragma once // meaning, during compile time, only include this file once, common in .h files

#include <iostream>
#include <vector> // This is to dynamically store enemies
#include <ctime> // so we can use the random function with time as our seed

// Pre-compiled headers, makes it faster
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    Think of a class as a way to bundle data and functions together, it's the blueprint
    for creating a game object. This is a primary part of Object Oriented Programming (OOP)
*/

class Game {
    // Only code inside the class can access this stuff, hides internal details
    private:
        // Variables
        // Window
        sf::RenderWindow * window; // a pointer to the SFML window object
        sf::VideoMode videoMode;
        sf::Event ev; // we don't need to make this a pointer. Sidenote, it already initializes for us

        // Mouse positions
        sf::Vector2i mousePosWindow; // usually not used
        sf::Vector2f mousePosView; // this is our game window

        // Game Logic
        int points;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies; // max amount on screen at one time

        // Game Objects
        std::vector<sf::RectangleShape> enemies; // Think of a vector as a flexible/dynamic array, it can grow and shrink. This one stores 'enemy' objects
        sf::RectangleShape enemy; // Makes a SFML object
        
        // This are private because no one really needs to use them except in here
        // They're defined in Game.cpp
        void initVariables();
        void initWindow();
        void initEnemies();

    // Code outside the class like main.cpp can access this stuff
    public:
        Game(); // Constructor, sets up the initial values and prepares the object
        virtual ~Game(); // Destructor, destroys the object when done with it, frees memory

        // Accessors, just checking stuff not modifying anything
        const bool running() const;

        // Functions
        void spawnEnemy();
        void pollEvents();
        void updateMousePositions();
        
        void updateEnemies();
        void update();
        
        void renderEnemies();
        void render();
};