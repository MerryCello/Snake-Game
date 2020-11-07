/*************************************************************
 * File: game.h
 * Author: Br. Burton
 *
 * Description: The game of Skeet. This class holds each piece
 *  of the game (birds, bullets, rifle, score). It also has
 *  methods that make the game happen (advance, interact, etc.)
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>

#include "uiDraw.h"
#include "definitions.h"
#include "uiInteract.h"
#include "Point.h"
#include "Snake.h"
#include "Fruit.h"
#include "Menu.h"


/// The greater the number the slower the game
#define GAME_TICK_SPEED 250
/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game {
private:
   /// The coordinates of the screen
   Point topLeft;
   Point bottomRight;
   int nextAdvanceTime;

   Menu* menus;
   bool isInSecondaryMenu;
   bool isPlaying;
   bool isPaused;
   int score;
   int highScore;

   Snake snake;

   Fruit* fruit;

   /*************************************************
   * Private methods to help with the game logic.
   *************************************************/
   bool isOnScreen(const Point & point);
   void advanceSnake();
   void advanceFruit();

    Fruit * createFruit();

    void handleCollisions();

    void setHighScore(int theScore);
    int getHighScore();

    static void drawScore(Point &scoreLocation, int score);
    static int gameClock() { return (int)(clock() / GAME_TICK_SPEED); }

public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   ~Game();

   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);

   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();

   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);
};

#endif /* GAME_H */
