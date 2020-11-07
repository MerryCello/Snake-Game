#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstring-compare"
//
// Created by Kevin on 8/12/2020.
//

#include <string>
#include "include/Fruit.h"
#include "include/uiDraw.h"
using namespace std;

Fruit::Fruit(const std::string& type, Point center) : eaten(false), center(center) {
   if (type == "apple"  ||
       type == "cherry" ||
       type == "banana" ||
       type == "strawberry") {
       Fruit::type = type;
   } else { Fruit::type = "apple"; }
}

bool Fruit::draw() {
   if (type == "apple" ) {
      drawApple();
   } else if (type == "cherry") {
      drawCherry();
   } else if (type == "banana") {
      drawBanana();
   } else if (type == "strawberry") {
      drawStrawberry();
   }
   return true;
}

void Fruit::drawApple() {
   string filePath = ((string)ABS_PATH) + "media/apple.dat";
   if (isValidFile(filePath)) {
      drawImage(center, filePath);
   } else {
      Color red(RED_LIGHT("r"), RED_LIGHT("g"), RED_LIGHT("b"));
      Color darkGreen(GREEN("r"), GREEN("g"), GREEN("b"));
      Color brown(BROWN("r"), BROWN("g"), BROWN("b"));
      Point stalkPt1(center.getX() - 1, center.getY() + SQUARE_SIZE / 2);
      Point stalkPt2(center.getX(), center.getY() + SQUARE_SIZE / 2);
      Point stalkPt3(center.getX() + 1, center.getY() + SQUARE_SIZE / 2);
      Point stamenPt(center.getX(), center.getY() - SQUARE_SIZE / 4);
      Point left_circleCenterPt(center.getX() - SQUARE_SIZE / 8, center.getY());
      Point right_circleCenterPt(center.getX() + SQUARE_SIZE / 8, center.getY());

      /// draw stalk/stamen
      drawLine(center, stalkPt1, brown);
      drawLine(center, stalkPt2, brown);
      drawLine(center, stalkPt3, brown);
      drawRectangle(stamenPt, SQUARE_SIZE / 4, SQUARE_SIZE / 2, darkGreen);

      /// draw apple body
      drawCircle(left_circleCenterPt, SQUARE_SIZE / 5 * 2, red, true);
      drawCircle(right_circleCenterPt, SQUARE_SIZE / 5 * 2, red, true);
   }
}

void Fruit::drawCherry() {
   string filePath = ((string)ABS_PATH) + "media/cherries.dat";
   if (isValidFile(filePath)) {
      drawImage(center, filePath);
   } else {
      Color red(RED_DARK("r"), RED_DARK("g"), RED_DARK("b"));
      Color brown(BROWN("r"), BROWN("g"), BROWN("b"));
      Point centerTop(center.getX(), center.getY() + SQUARE_SIZE / 2);

      /// Left Cherry
      Point blCenter(center.getX() - SQUARE_SIZE / 4, center.getY() - SQUARE_SIZE / 4);
      Point leftCherryTop(blCenter.getX(), blCenter.getY() + SQUARE_SIZE / 4);
      drawLine(leftCherryTop, centerTop, brown);
      drawCircle(blCenter, SQUARE_SIZE / 4, red, true);

      /// Right Cherry
      Point brCenter(center.getX() + SQUARE_SIZE / 4, center.getY() - SQUARE_SIZE / 4);
      Point rightCherryTop(brCenter.getX(), brCenter.getY() + SQUARE_SIZE / 4);
      drawLine(rightCherryTop, centerTop, brown);
      drawCircle(brCenter, SQUARE_SIZE / 4, red, true);
   }
}

void Fruit::drawBanana() {
   string filePath = ((string)ABS_PATH) + "media/banana.dat";
   if (isValidFile(filePath)) {
      drawImage(center, filePath);
   } else {
      drawStrawberry();
   }
}

void Fruit::drawStrawberry() {
   string filePath = ((string)ABS_PATH) + "media/strawberry.dat";
   if (isValidFile(filePath)) {
      drawImage(center, filePath);
   } else {
      Color red(RED_LIGHT("r"), RED_LIGHT("g"), RED_LIGHT("b"));
      Color white(1.0, 1.0, 1.0);
      Color green(GREEN_LIGHT("r"), GREEN_LIGHT("g"), GREEN_LIGHT("b"));

      /// stem
      Point stemCenter(center.getX(), center.getY() + SQUARE_SIZE / 8 * 3);
      drawRectangle(stemCenter,
                    SQUARE_SIZE / 2,
                    SQUARE_SIZE / 2, green);

      /// berry
      Point left_CircleCenter(center.getX() - SQUARE_SIZE / 4, center.getY() + SQUARE_SIZE / 4);
      Point right_CircleCenter(center.getX() + SQUARE_SIZE / 4, center.getY() + SQUARE_SIZE / 4);
      Point center_CircleCenter(center.getX(), center.getY() + SQUARE_SIZE / 4);
      Point pt1(center.getX() - SQUARE_SIZE / 2, center.getY() + SQUARE_SIZE / 4);
      Point pt2(center.getX() + SQUARE_SIZE / 2, center.getY() + SQUARE_SIZE / 4);
      Point pt3(center.getX(), center.getY() - SQUARE_SIZE / 2);
      drawCircle(left_CircleCenter, SQUARE_SIZE / 4, red);
      drawCircle(right_CircleCenter, SQUARE_SIZE / 4, red);
      drawCircle(center_CircleCenter, SQUARE_SIZE / 4, red);
      drawTriangle(pt1, pt2, pt3, red);
   }
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop