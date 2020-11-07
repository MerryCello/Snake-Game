//
// Created by Kevin on 8/13/2020.
//

#ifndef UNIT_TESTING_ON_SNAKE_GAME_COLOR_H
#define UNIT_TESTING_ON_SNAKE_GAME_COLOR_H


/************************************************************************
 * COLOR
 * RGB class for Red, Green, and Blue percentages
 *************************************************************************/
class Color {
private:
   float r; /// Red   in percentages (eg. 0.00 - 1.00)
   float g; /// Green in percentages (eg. 0.00 - 1.00)
   float b; /// Blue  in percentages (eg. 0.00 - 1.00)

public:
   Color(float r, float g, float b) : r(r), g(g), b(b) {}
   Color() : r(1.0), g(1.0), b(1.0) {}

   void setR(float r) { Color::r = r; }
   void setG(float g) { Color::g = g; }
   void setB(float b) { Color::b = b; }

   float red() const { return r; }
   float green() const { return g; }
   float blue() const { return b; }
};


#endif ///UNIT_TESTING_ON_SNAKE_GAME_COLOR_H
