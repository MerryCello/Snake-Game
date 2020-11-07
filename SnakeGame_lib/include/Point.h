//
// Created by Kevin on 8/12/2020.
//

#ifndef SNAKE_GAME_POINT_H
#define SNAKE_GAME_POINT_H

#include <iostream>

class Point {
public:
    /// constructors
    Point()            : x(0.0), y(0.0)  {}
    Point(bool check)  : x(0.0), y(0.0)  {}
    Point(float x, float y);

    /// getters
    float getX()       const { return x;              }
    float getY()       const { return y;              }

    /// setters
    Point & setX(float x);
    Point & setY(float y);
    void addX(float dx)      { setX(getX() + dx);     }
    void addY(float dy)      { setY(getY() + dy);     }

    friend bool operator == (const Point & lhs, const Point & rhs) { return lhs.x==rhs.x && lhs.y==rhs.y; }
    friend bool operator != (const Point & lhs, const Point & rhs) { return !(lhs==rhs);                  }

private:
    float x;           /// horizontal position
    float y;           /// vertical position
};

/// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);


#endif ///SNAKE_GAME_POINT_H
