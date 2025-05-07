OVERVIEW:
This game is based closely on the first game in the tutorial below:
https://www.youtube.com/watch?v=2FNP3Jce-fc&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=2


GAME DESCRIPTION:
The game itself is a clicking game, there are 5 different types of enemy blocks falling from
the ceiling. The smallest block gives you the most points while the largest gives you the
smallest amount. Failure to kill the enemy will result in health being taken away, missing 10
enemies will result in a FATALITY!!!...


NOTES:
As of now the game is complete and working. If you clone the 'COMPLETE' repository
it should have the main.cpp, Game.cpp, and Game.h files which when compiled will run the game.
To compile on your own, you will need to have all necessary sfml libraries downloaded and C++.
The output file 'game' is a precompiled file that should be executable. The only other file
is a .ttf which is a font file for in game text.


FILES IN DEPTH:
main.cpp
This file holds the main game loop for run Time.

Game.h
This file is the class definition. There is not much more than simple defining and order here.

Game.cpp
This defines the var.'s/functions. The private game objects include variables and functions,
most of these are used for initializing the environment, enemies, and etc. The public objects
include most of the game functonality, backend upfating, and rendering to the screen. This
is the most important file for understanding how this game works. Use Game.h to help if you
get lost, all var.'s and functions on the .h file are in the same order on the .cpp, it's 
like looking at a snapshot.