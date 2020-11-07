//
// Created by Kevin on 8/12/2020.
//

#ifndef SNAKE_GAME_FRUIT_H
#define SNAKE_GAME_FRUIT_H

#include <string>
#include "definitions.h"
#include "Point.h"

/**
 * Possible fruits are:
 *    apple
 *    cherry
 *    banana
 *    strawberry
 */
class Fruit {
private:
    float sizeLimit = SQUARE_SIZE;
    std::string type;
    Point center;
    bool eaten;
    void drawApple();
    void drawCherry();
    void drawBanana();
    void drawStrawberry();
public:
   /// constructor
   Fruit(const std::string& type, Point center);

   /// setters
   void gotEaten(bool eaten) { Fruit::eaten = eaten; }
   void setCenter(const Point &center) { Fruit::center = center; }

   /// getters
   bool isEaten() const { return eaten; }
   const Point &getCenter() const { return center; }

   bool draw();
};


#endif //SNAKE_GAME_FRUIT_H
