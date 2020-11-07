#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-emplace"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/



#include <vector>
#include <cassert>
#include <fstream>
#include <sstream>
#include "include/Game.h"

/// for debugging
//#include <iomanip>
//#include "include/uiDraw.h"

using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT -5

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br),
   fruit(nullptr), isPlaying(false), score(0) {
   /// Set up the initial conditions of the game
   nextAdvanceTime = gameClock() + 1;

   /// Main Menu setup
   menus = new Menu[3];
   menus[0] = Menu("Main Menu", "Snake", Point());
   list<string> options;
   options.push_back("Start");
   options.push_back("How to Play");
   options.push_back("Quit");
   menus[0] = options;
   menus[0].setOptionSelected(menus[0].begin());

   /// "How to Play" Menu setup
   menus[1] = Menu("How to Play", "Snake Game", Point());
   options.clear();
   options.push_back("[Left   arrow] Move the snake left  ");
   options.push_back("[Right arrow] Move the snake right");
   options.push_back("           [Esc] Pause                     ");
   options.push_back("Eat fruit until you beat the game!   ");
   options.push_back("<- back");
   menus[1] = options;
   isInSecondaryMenu = false;

   /// Pause Menu setup
   menus[2] = Menu("Game Paused", "Snake Game", Point());
   options.clear();
   options.push_back("Resume");
   options.push_back("Quit");
   menus[2] = options;
   isPaused = false;

   /// Snake setup
   Snake newSnake(Point(), RIGHT);
   snake = newSnake;

   /// Scores setup
   highScore = getHighScore();
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game() {
   if (fruit != nullptr) {
      delete fruit;
      fruit = nullptr;
   }
   if (menus != nullptr) {
      delete menus;
      menus = nullptr;
   }
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance() {
   if (isPlaying && !isPaused) {
      advanceSnake();
      advanceFruit();
   }

   nextAdvanceTime = (gameClock() + 1);
   handleCollisions();
}

/**************************************************************************
 * GAME :: ADVANCE SNAKE
 * Move snake at the appropriate time according to snake speed
 **************************************************************************/
void Game :: advanceSnake() {
   if (snake.isAlive()) {
      if (gameClock() == nextAdvanceTime) {
         snake.moveForward();
      }
   }
}

/**************************************************************************
 * GAME :: ADVANCE FRUIT
 * If there is no fruit, create one with some probability
 **************************************************************************/
void Game :: advanceFruit() {
   if (fruit == nullptr) {
      /// there is no fruit right now, possibly create one
      /// create it with some random chance
      if (random(0, 30) == 0) {
         /// create a new fruit
         fruit = createFruit();
      }
   }
}

/**************************************************************************
 * GAME :: CREATE FRUIT
 * Create a fruit of a random type.
 **************************************************************************/
Fruit * Game :: createFruit() {
   Fruit* newFruit = nullptr;

   /// Get the point of the new fruit
   Point center;
   bool isInvalidPosition;
   do {
      isInvalidPosition = false;

      /// Make sure the fruit is at the center of a SQUARE
      int x = random((topLeft.getX() + SQUARE_SIZE) / SQUARE_SIZE,
                     ((bottomRight.getX() - SQUARE_SIZE) / SQUARE_SIZE) + 1);
      int y = random((bottomRight.getY() + SQUARE_SIZE) / SQUARE_SIZE,
                     ((topLeft.getY() - SQUARE_SIZE) / SQUARE_SIZE) + 1);

      center.setX(x * SQUARE_SIZE).setY(y * SQUARE_SIZE);

      /// Don't place the fruit on the snake!
      for (auto aVertebra : snake.getBody()) {
         if (center == aVertebra) {
            isInvalidPosition = true;
            break;
         }
      }
   } while (isInvalidPosition);

   /// Cherry 10%, Strawberry 25%, Banana 30%, Apple 35%
   float lottery = random(1, 101);
   if (lottery > 65 && lottery <= 100) {
      newFruit = new Fruit("apple", center);
   } else if (lottery > 35 && lottery <= 65) {
      newFruit = new Fruit("banana", center);
   } else if (lottery > 10 && lottery <= 35) {
      newFruit = new Fruit("strawberry", center);
   } else if (lottery > 0 && lottery <= 10) {
      newFruit = new Fruit("cherry", center);
   }

   return newFruit;
}

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game :: isOnScreen(const Point & point) {
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between the snake and itself, and a fruit.
 **************************************************************************/
void Game :: handleCollisions() {
   /// if snake bites itself, then it dies
   auto body = snake.getBody();
   for (auto vertebra = ++(body.begin()); vertebra != body.end(); vertebra++) {
      if (*vertebra == snake.getHead())
         snake.setAlive(false);
   }

   /// did the snake hit a wall?
   if (!isOnScreen(snake.getHead()))
      snake.setAlive(false);

   if (!snake.isAlive() && score > highScore)
      setHighScore(score);

   /// did the snake eat the fruit?
   if (fruit != nullptr && snake.getHead() == fruit->getCenter()) {
      delete fruit;
      fruit = nullptr;

      snake.grow();

      score += 10;
   }
}

/**************************************************************************
 * GAME :: GET HIGH SCORE
 **************************************************************************/
void Game::setHighScore(int theScore) {
   assert(theScore > highScore);
   highScore = theScore;
   string filename = "highscore.txt";

   /// write new high score to file
   ofstream fout(filename);
   if (fout.fail()) {
      cerr << "Could not open \"" << filename << "\" to read.\n";
      return;
   }
   fout << highScore;
   fout.close();
}
/**************************************************************************
 * GAME :: GET HIGH SCORE
 **************************************************************************/
int Game::getHighScore() {
   string txtHighscore;
   string filename = "highscore.txt";

   /// read high score from file
   ifstream fin(filename);
   if (fin.fail()) {
      cerr << "Could not open \"" << filename << "\" to read.\n";
      return 0;
   }
   fin >> txtHighscore;
   fin.close();

   stringstream strToInt(txtHighscore);
   strToInt >> highScore;
   return highScore;
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui) {
   /// Change the direction of the snake
   if (snake.isAlive() && !isPaused) {
      if (ui.isLeftShort())
         snake.moveLeft();
      if (ui.isRightShort())
         snake.moveRight();
      if (ui.isESC())
         isPaused = true;
   } else if (!snake.isAlive()) {
      isPlaying = false;
   }

   /// Menu controls
   if(!isPlaying || isPaused) {
      if (ui.isUpShort()) {
         if (isPaused)
            --menus[2];
         else if (isInSecondaryMenu)
            --menus[1];
         else
            --menus[0];
      }
      if (ui.isDownShort()) {
         if (isPaused)
            ++menus[2];
         else if (isInSecondaryMenu)
            ++menus[1];
         else
            ++menus[0];
      }
      if (ui.isEnter()) {
         /// Reset the game
         if (menus[0].getOptionSelected() == menus[0].begin() && !isInSecondaryMenu && !isPaused) {
            isPlaying = true;
            isPaused = false;
            delete fruit;
            fruit = nullptr;
            snake = Snake(Point(), LEFT);
            score = 0;

         /// Pause resume option
         } else if (isPaused && menus[2].getOptionSelected() == menus[2].begin()) {
            isPaused = false;

         /// Display game instructions
         } else if (menus[0].getOptionSelected() == ++(menus[0].begin()) && !isInSecondaryMenu && !isPaused) {
            isInSecondaryMenu = true;
            menus[1].setOptionSelected(menus[1].end());

         /// Close the game
         } else if (menus[0].getOptionSelected() == menus[0].end() ||
                    menus[1].getOptionSelected() == menus[1].end() ||
                    menus[2].getOptionSelected() == menus[2].end()) {
            if (isInSecondaryMenu) {
               isInSecondaryMenu = false;
               menus[0].setOptionSelected(++(menus[0].begin()));
            } else {
               quit();
            }
         }
      }
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui) {
   /// draw the fruit
   if(fruit != nullptr && !(fruit->isEaten()))
      fruit->draw();

   /// draw the snake
   snake.draw();

   /// Draw score
   Point scoreLocation;
   scoreLocation.setX(topLeft.getX() + 5);
   scoreLocation.setY(topLeft.getY() - 5);

   drawScore(scoreLocation, score);
   scoreLocation.addX(22);
   drawTextLeft(Point(scoreLocation.getX(), scoreLocation.getY() - 10), "HIGHSCORE:", Color());
   scoreLocation.addX(88);
   drawScore(scoreLocation, highScore);


   /// draw Menu
   if (!isPlaying || isPaused) {
      /// Game over menu
      if (!snake.isAlive())
         menus[0].setTitle("GAME OVER");

      if (isPaused)
         menus[2].draw();
      else if (isInSecondaryMenu)
         menus[1].draw();
      else
         menus[0].draw();
   }
}

void Game::drawScore(Point &scoreLocation, int score) {
   for (int digitPlace = 1000, greaterDigitPlaceNumber = score / (digitPlace * 10);
        digitPlace > 0;
        digitPlace /= 10, greaterDigitPlaceNumber = score / ((digitPlace * 10) == 0 ? 1 : (digitPlace * 10))) {

      int digit = (score - greaterDigitPlaceNumber * digitPlace * 10) / digitPlace;
      drawDigit(scoreLocation, (char)digit + '0');
      scoreLocation.addX(11);
   }
}


#pragma clang diagnostic pop