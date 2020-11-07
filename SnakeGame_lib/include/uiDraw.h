/**
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 **/

#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include "Point.h"    // Where things are drawn
#include "Color.h"
#include "definitions.h"

using std::string;


/**
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 ***/
void drawDigit(const Point & topLeft, char digit);

/**
 * DRAW NUMBER
 * Display an integer on the screen using the 7-segment method
 */
void drawNumber(const Point & topLeft, int number);

/**
 * DRAW TEXT LEFT/CENTER
 * Draw text using a simple bitmap font
 */
void drawTextLeft(const Point &topLeft, const char *text, Color color, bool largeFontSize = false);
void drawTextCenter(const Point &center, const char *text, Color color, bool largeFontSize = false);

/**
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 */
void rotate(Point & point, const Point & origin, int rotation = 0);

/**
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 */
void drawLine(const Point &begin, const Point &end, Color color);

/**
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 */
void drawRectangle(const Point &center, int width, int height, Color color, bool fill = true, int rotation = 0);

/**
 * Draw a filled triangle on the screen
 * @param pt1 One of the vertices of the triangle
 * @param pt2 One of the vertices of the triangle
 * @param pt3 One of the vertices of the triangle
 * @param color
 * @param rotation degrees of rotation
 */
void drawTriangle(Point pt1, Point pt2, Point pt3, Color color, int rotation = 0);

/**
 * DRAW Circle
 * Draw a circle on the screen
 */
void drawCircle(const Point &center, float radius, Color color, bool fill = true);

/**
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 **/
void drawCircleNoFill(const Point & center, int radius);

/**
 * Checks if file exists and it is not corrupt
 * @param filePath
 * @return Good for use or not
 */
bool isValidFile(const string& filePath);

/**
 * Draws the individual pixels of an image with their corresponding color
 * A very inefficient of doing it, yes
 * Expects a file that has the following structure:
 * Red Green Blue X Y
 * Ex:
 * 1.0 0.0 1.0 42 42
 * @param center of the image
 * @param imagePath filename
 * @param rotation degrees of rotation
 * @param verticalFlip flips the pixels on the x axis
 * @param horizontalFlip flips the pixels on the y axis
 */
void drawImage(Point center,
               const string& imagePath,
               int rotation = 0,
               bool verticalFlip   = false,
               bool horizontalFlip = false);

/**
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 */
int    random(int    min, int    max);
double random(double min, double max);

/**
 * Makes it easier to pass in my Color class
 * @param c the color
 */
void glColor3f(Color c);

/**
 * Finish all the processes, and exit the main GL loop.
 * Closes the OpenGL window
 */
void quit();

#endif // UI_DRAW_H
