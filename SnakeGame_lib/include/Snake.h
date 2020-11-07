//
// Created by Kevin on 8/12/2020.
//

#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H


#include <list>
#include "Point.h"

class Snake {
private:
   float width;           /// Width of individual vertebra of the snake
   int length;            /// How long the snake is
   bool alive;            /// is the snake still alive?
   int direction;         /// The direction the snake is going in
   std::list<Point> body; /// All the individual vertebrae of the snake

public:
   Snake();
   Snake(const Point &headPoint, int directionFacing);

   bool isAlive() const { return alive; }
   int getDirection() const { return direction; }

   /**
    * Calculates the direction tha the tail is being dragged in
    * @return tail direction
    */
   int getTailDirection();
   Point & getHead() { return body.front(); }
   std::list<Point> getBody() { return body; }

   void setAlive(bool alive) { Snake::alive = alive; }

   /**
    * Shifts the whole snake to the new head point
    * @param newHeadPoint
    */
   void setHeadPoint(Point newHeadPoint);

   /**
    * Move snake forward by one square
    */
   void moveForward();

   /**
    * turn snake to the left direction and move it forward in that direction
    */
   void moveLeft();

   /**
    * turn snake to the right direction and move it forward in that direction
    */
   void moveRight();

   /**
    * grow the snake by one square
    */
   void grow();

   /**
    * Draw the snake to the screen
    */
   bool draw();
};


#endif //SNAKE_GAME_SNAKE_H
