//
// Created by Kevin on 8/12/2020.
//

#include "include/Point.h"

/**
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the pointOfHead to the passed position
 */
Point::Point(float x, float y) : x(0.0), y(0.0) {
    setX(x);
    setY(y);
}

/**
 * POINT : SET X
 * Set the x position if the value is within range
 */
Point & Point::setX(float x) {
    this->x = x;
    return *this;
}

/**
 * POINT : SET Y
 * Set the y position if the value is within range
 */
Point & Point::setY(float y) {
    this->y = y;
    return *this;
}

/**
 * POINT insertion
 *       Display coordinates on the screen
 */
std::ostream & operator << (std::ostream & out, const Point & pt) {
    out << "(" << pt.getX() << ", " << pt.getY() << ")";
    return out;
}

/**
 * POINT extraction
 *       Prompt for coordinates
 */
std::istream & operator >> (std::istream & in, Point & pt) {
    float x;
    float y;
    in >> x >> y;

    pt.setX(x);
    pt.setY(y);

    return in;
}
