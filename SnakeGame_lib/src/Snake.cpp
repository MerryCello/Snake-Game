#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
//
// Created by Kevin on 8/12/2020.
//

#include <cassert>
#include "include/Snake.h"
#include "include/uiDraw.h"

//#define FANCY_SNAKE

Snake::Snake() : direction(LEFT), alive(true), length(3), width(SQUARE_SIZE) {
    Snake newSnake(Point(0, 0), direction);
    this->body = newSnake.body;
}

Snake::Snake(const Point &headPoint, int directionFacing) :
            direction(directionFacing),
            alive(true),
            length(3),
            width(SQUARE_SIZE) {

    assert(directionFacing >= 0 && directionFacing < 4);
    Point newVertebra(headPoint);
    body.push_back(newVertebra);
    for (int i = 0; i < length-1; i++) {
        switch (directionFacing) {
            case UP:
                newVertebra.setY(newVertebra.getY() - width);
                break;
            case DOWN:
                newVertebra.setY(newVertebra.getY() + width);
                break;
            case LEFT:
                newVertebra.setX(newVertebra.getX() + width);
                break;
            case RIGHT:
                newVertebra.setX(newVertebra.getX() - width);
                break;
        }
        body.push_back(newVertebra);
    }
}

int Snake::getTailDirection() {
   int tailDirection = UP;
   Point caudal(body.back());
   body.pop_back(); /// pop to access the vertebra before oldCaudal

/// Determine Caudal (tail) direction of movement based off of vertebra preceding it
   /// UP
   Point vertebraBeforeOldCaudal(caudal.getX(), caudal.getY() + width);
   if (vertebraBeforeOldCaudal == body.back())
      tailDirection = UP;
   /// DOWN
   vertebraBeforeOldCaudal.setY(caudal.getY() - width);
   if (vertebraBeforeOldCaudal == body.back())
      tailDirection = DOWN;
   /// LEFT
   vertebraBeforeOldCaudal.setX(caudal.getX() - width).setY(caudal.getY());
   if (vertebraBeforeOldCaudal == body.back())
      tailDirection = LEFT;
   /// RIGHT
   vertebraBeforeOldCaudal.setX(caudal.getX() + width);
   if (vertebraBeforeOldCaudal == body.back())
      tailDirection = RIGHT;

   body.push_back(caudal); /// put it back

   return tailDirection;
}

void Snake::setHeadPoint(Point newHeadPoint) {
   /// Find the difference
   float dx = (newHeadPoint.getX() - body.front().getX());
   float dy = (newHeadPoint.getY() - body.front().getY());

   /// Shift the whole body
   for (auto& vertebra : body)
      vertebra.setX(vertebra.getX() + dx).setY(vertebra.getY() + dy);
}

void Snake::moveForward() {
    switch (direction) {
        case UP: {
            body.emplace_front(body.front().getX(), body.front().getY() + width);
            break;
        }
        case DOWN: {
            body.emplace_front(body.front().getX(), body.front().getY() - width);
            break;
        }
        case LEFT: {
            body.emplace_front(body.front().getX() - width, body.front().getY());
            break;
        }
        case RIGHT: {
            body.emplace_front(body.front().getX() + width, body.front().getY());
            break;
        }
    }
    body.pop_back();
}

void Snake::moveLeft() {
    switch (direction) {
        case UP: {
            body.emplace_front(body.front().getX() - width, body.front().getY());
            direction = LEFT;
            break;
        }
        case DOWN: {
            body.emplace_front(body.front().getX() + width, body.front().getY());
            direction = RIGHT;
            break;
        }
        case LEFT: {
            body.emplace_front(body.front().getX(), body.front().getY() - width);
            direction = DOWN;
            break;
        }
        case RIGHT: {
            body.emplace_front(body.front().getX(), body.front().getY() + width);
            direction = UP;
            break;
        }
    }
    body.pop_back();
}

void Snake::moveRight() {
    switch (direction) {
        case UP: {
            body.emplace_front(body.front().getX() + width, body.front().getY());
            direction = RIGHT;
            break;
        }
        case DOWN: {
            body.emplace_front(body.front().getX() - width, body.front().getY());
            direction = LEFT;
            break;
        }
        case LEFT: {
            body.emplace_front(body.front().getX(), body.front().getY() + width);
            direction = UP;
            break;
        }
        case RIGHT: {
            body.emplace_front(body.front().getX(), body.front().getY() - width);
            direction = DOWN;
            break;
        }
    }
    body.pop_back();
}

void Snake::grow() {
    length++;
    Point newCaudal(body.back());
    Point oldCaudal(body.back());
    body.pop_back(); /// pop to access the vertebra before oldCaudal

   switch (getTailDirection()) {
      case UP:
         newCaudal.setY(oldCaudal.getY() - width);
         break;
      case DOWN:
         newCaudal.setY(oldCaudal.getY() + width);
         break;
      case LEFT:
         newCaudal.setX(oldCaudal.getX() + width);
         break;
      case RIGHT:
         newCaudal.setX(oldCaudal.getX() - width);
         break;
   }

    body.push_back(oldCaudal); /// put it back
    body.push_back(newCaudal); /// Grow new Caudal
}

/**
 * Snake color 1: r: 146, g:  26, b:  0 => Brown
 *       color 2: r: 197, g: 120, b: 76 => Beige/Tan
 * @return
 */
bool Snake::draw() {
   auto head = body.begin();
   auto tail = (--body.end());
#ifndef FANCY_SNAKE
   Color color1(BROWN("r"), BROWN("g"), BROWN("b"));
   Color color2(BEIGE("r"), BEIGE("g"), BEIGE("b"));
#endif

   /// draw body
   bool isColor1 = false;
   for (auto vertebra = ++(body.begin()); vertebra != --(body.end()); vertebra++, isColor1 = !isColor1) {
#ifndef FANCY_SNAKE
      /// simple body
      drawRectangle(*vertebra, width, width, (isColor1 ? color1 : color2), true);
#else
      /// fancy body
      drawImage(*vertebra, ((string)ABS_PATH) + "media/snakePattern.dat");
#endif
   }

   /// draw tail
#ifndef FANCY_SNAKE
      /// simple tail
   Point top(tail->getX() - SQUARE_SIZE / 2, tail->getY() + SQUARE_SIZE / 2);
   Point center(tail->getX() + SQUARE_SIZE / 2, tail->getY());
   Point bottom(tail->getX() - SQUARE_SIZE / 2, tail->getY() - SQUARE_SIZE / 2);
   int rotation = 0;
#endif
   /// fancy tail
   int tailDirection = getTailDirection();
   string tailImagePath = ((string)ABS_PATH) + "media/snakeTail.dat";
   switch (tailDirection) {
      case UP:
#ifndef FANCY_SNAKE
         rotation = -90;
#else
         drawImage(*tail, tailImagePath, -90);
#endif
         break;
      case DOWN:
#ifndef FANCY_SNAKE
         rotation = 90;
#else
         drawImage(*tail, tailImagePath, 90);
#endif
         break;
      case LEFT:
#ifndef FANCY_SNAKE
         rotation = 0;
#else
         drawImage(*tail, tailImagePath, 0);
#endif
         break;
      case RIGHT:
#ifndef FANCY_SNAKE
         rotation = 180;
#else
         drawImage(*tail, tailImagePath, 180);
#endif
         break;
   }
#ifndef FANCY_SNAKE
   rotate(top, *tail, rotation);
   rotate(center, *tail, rotation);
   rotate(bottom, *tail, rotation);
   drawTriangle(top, bottom, center, (isColor1 ? color1 : color2));

   /// draw head
    drawRectangle(*head, width / 1.2, width / 1.2, color1, true, 45);
#else
   string headImg = ((string)ABS_PATH) + "media/christianFace.dat";
//   string headImg = ((string)ABS_PATH) + "media/nateFace.dat";
//   string headImg = ((string)ABS_PATH) + "media/snakeHead.dat";
   switch (direction) {
      case UP:
      case LEFT:
         drawImage(*head, headImg, 0);
         break;
      case DOWN:
      case RIGHT:
         drawImage(*head, headImg, 0, true);
         break;
   }
#endif

   return true;
}

#pragma clang diagnostic pop