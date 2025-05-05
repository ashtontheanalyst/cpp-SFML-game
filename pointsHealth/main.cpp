// The main file that runs the game

#include <iostream>
#include "Game.h"

int main() {
    // Initialize random, srand
    std::srand(static_cast<unsigned>(time(NULL)));
    
    // Create a game object using the Game class
    Game game;
    
    // Game loop, run the game while the window is open and we haven't died
    while(game.running() && game.getEndGame() == false) {
        // Update, process any input
        game.update();

        // Render, draw to the screen
        game.render();
    }

    // End of game
    return 0;
}