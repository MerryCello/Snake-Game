/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Edited by:
 *    Kevin Foniciello
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ***********************************************************************/

#include <string>     /// need you ask?
#include <fstream>
#include <sstream>    /// convert an integer into text
#include <cassert>    /// I feel the need... the need for asserts
#include <unistd.h>


#ifdef __APPLE__
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <cstdio>
#include <cstdlib>
//#include <GL/glut.h>
//#include <GL/glew.h>
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <include/Snake.h>

#endif // _WIN32

#include "include/uiDraw.h"
#include "definitions.h"

using namespace std;

#define deg2rad(value) ((M_PI / 180) * (value))

/**
 * NUMBER OUTLINES
 * We are drawing the text for score and things
 * like that by hand to make it look "old school."
 * These are how we render each individual charactger.
 * Note how -1 indicates "done".  These are paired
 * coordinates where the even are the x and the odd
 * are the y and every 2 pairs represents a point
 */
const char NUMBER_OUTLINES[10][20] = {
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

/**
 * DRAW DIGIT
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 */
void drawDigit(const Point & topLeft, char digit) {
   /// we better be only drawing digits
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;

   /// compute the row as specified by the digit
   int r = digit - '0';
   assert(r >= 0 && r <= 9);

   /// go through each segment.
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4) {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);

      ///Draw a line based off of the num structure for each number
      Point start;
      start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
      start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
      Point end;
      end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
      end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);

      drawLine(start, end, Color());
   }
}

/**
 * DRAW NUMBER
 * Display an integer on the screen using the 7-segment method
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 */
void drawNumber(const Point & topLeft, int number) {
   /// our cursor, if you will. It will advance as we output digits
   Point point = topLeft;
   
   /// is this negative
   bool isNegative = (number < 0);
   number *= (isNegative ? -1 : 1);
   
   /// render the number as text
   ostringstream sout;
   sout << number;
   string text = sout.str();

   /// handle the negative
   if (isNegative) {
      glBegin(GL_LINES);
      glVertex2f(point.getX() + 1, point.getY() - 5);
      glVertex2f(point.getX() + 5, point.getY() - 5);
      glEnd();
      point.addX(11);
   }
   
   /// walk through the text one digit at a time
   for (const char *p = text.c_str(); *p; p++) {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.addX(11);
   }
}

/**
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 */
void drawTextLeft(const Point &topLeft, const char *text, Color color, bool largeFontSize) {
   void *pFont = (largeFontSize ? GLUT_BITMAP_HELVETICA_18 : GLUT_BITMAP_HELVETICA_12);

   /// prepare to draw the text from the top-left corner
   glColor3f(color);
   glRasterPos2f(topLeft.getX(), topLeft.getY());

   glDisable(GL_TEXTURE_2D);
   /// loop through the text
   for (const char *p = text; *p; p++) {
      glutBitmapCharacter(pFont, *p);
   }
   glColor3f(1.0, 1.0, 1.0);
   glEnable(GL_TEXTURE_2D);
}

/**
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 */
void drawTextCenter(const Point &center, const char *text, Color color, bool largeFontSize) {
   void *pFont = (largeFontSize ? GLUT_BITMAP_HELVETICA_18 : GLUT_BITMAP_HELVETICA_12);
   int length = glutBitmapLength(pFont, reinterpret_cast<const unsigned char *>(text));
   Point topLeft(
           center.getX() - (float)length / 2,
           center.getY()
           );

   drawTextLeft(topLeft, text, color, largeFontSize);
}

/**
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 */
void rotate(Point & point, const Point & origin, int rotation) {
   /// because sine and cosine are expensive, we want to call them only once
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));

   /// remember our original point
   Point tmp(false);
   tmp.setX(point.getX() - origin.getX());
   tmp.setY(point.getY() - origin.getY());

   /// find the new values
   point.setX(static_cast<int> (tmp.getX() * cosA -
                                tmp.getY() * sinA) +
              origin.getX());
   point.setY(static_cast<int> (tmp.getX() * sinA +
                                tmp.getY() * cosA) +
              origin.getY());
}

/**
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 */
void drawLine(const Point &begin, const Point &end, Color color) {
   /// Get ready...
   glBegin(GL_LINES);
   glColor3f(color);

   /// Draw the actual line
   glVertex2f(begin.getX(), begin.getY());
   glVertex2f(  end.getX(),   end.getY());

   /// Complete drawing
   glColor3f(1.0, 1.0, 1.0);
   glEnd();
}

/**
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 *  INPUT  center    Center of the rectangle
 *         width     Horizontal size
 *         height    Vertical size
 *         rotation  Orientation
 */
void drawRectangle(const Point &center, int width, int height, Color color, bool fill, int rotation) {
   Point tl(false); /// top left
   Point tr(false); /// top right
   Point bl(false); /// bottom left
   Point br(false); /// bottom right

   ///Top Left point
   tl.setX(center.getX() - (width  / 2));
   tl.setY(center.getY() + (height / 2));

   ///Top right point
   tr.setX(center.getX() + (width  / 2));
   tr.setY(center.getY() + (height / 2));

   ///Bottom left point
   bl.setX(center.getX() - (width  / 2));
   bl.setY(center.getY() - (height / 2));

   ///Bottom right point
   br.setX(center.getX() + (width  / 2));
   br.setY(center.getY() - (height / 2));

   ///Rotate all points the given degrees
   rotate(tl, center, rotation);
   rotate(tr, center, rotation);
   rotate(bl, center, rotation);
   rotate(br, center, rotation);

   if (fill) {
      /// begin drawing
      glBegin(GL_TRIANGLES);
      glColor3f(color.red(), color.green(), color.blue());

      /// Triangle 1
      glVertex2f(tl.getX(), tl.getY());
      glVertex2f(tr.getX(), tr.getY());
      glVertex2f(br.getX(), br.getY());

      /// Triangle 2 opposite of triangle 1
      glVertex2f(tl.getX(), tl.getY());
      glVertex2f(br.getX(), br.getY());
      glVertex2f(bl.getX(), bl.getY());

      /// finish drawing
      glColor3f(1, 1, 1);
      glEnd();

   } else {
      ///Finally draw the rectangle
      glBegin(GL_LINE_STRIP);
      glColor3f(color.red(), color.green(), color.blue());
      glVertex2f(tl.getX(), tl.getY());
      glVertex2f(tr.getX(), tr.getY());
      glVertex2f(br.getX(), br.getY());
      glVertex2f(bl.getX(), bl.getY());
      glVertex2f(tl.getX(), tl.getY());
      glColor3f(1, 1, 1);
      glEnd();
   }
}

void drawTriangle(Point pt1, Point pt2, Point pt3, Color color, int rotation) {
   Point centroid((pt1.getX() + pt2.getX() + pt3.getX()) / 3,
                  (pt1.getY() + pt2.getY() + pt3.getY()) / 3);

   rotate(pt1, centroid, rotation);
   rotate(pt2, centroid, rotation);
   rotate(pt3, centroid, rotation);

   glBegin(GL_TRIANGLES);
   glColor3f(color.red(), color.green(), color.blue());

   glVertex2f(pt1.getX(), pt1.getY());
   glVertex2f(pt2.getX(), pt2.getY());
   glVertex2f(pt3.getX(), pt3.getY());

   glColor3f(1, 1, 1);
   glEnd();
}

/**
 * DRAW CIRCLE
 * Draw a circle on the screen
 *  INPUT point   The position of the circle
 *        radius  The size of the circle
 */
void drawCircle(const Point &center,
                float radius,
                Color color,
                bool fill) {
   assert(radius > 1.0);

   if (!fill) {
      drawCircleNoFill(center, radius);
      return;
   }

   const double increment = M_PI / 6.0;

   /// begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f(color);

   /// three points: center, pt1, pt2
   Point pt1(false /*check*/);
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Point pt2(pt1);

   /// go around the circle
   for (double radians = increment;
        radians <= M_PI * 2.0 + .5;
        radians += increment) {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f(center.getX(), center.getY());
      glVertex2f(pt1.getX(),    pt1.getY()   );
      glVertex2f(pt2.getX(),    pt2.getY()   );

      pt1 = pt2;
   }

   /// complete drawing
   glColor3f(1.0, 1.0, 1.0);
   glEnd();
}

/**
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the circle
 *          radius   Size of the circle
 */
void drawCircleNoFill(const Point & center, int radius) {
   assert(radius > 1.0);
   const double increment = 1.0 / (double)radius;

   /// begin drawing
   glBegin(GL_LINE_LOOP);
   glColor3f(0.5, 0.5, 0.5); // Color Grey

   Point pt1(false /*check*/);
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));   
   Point pt2(pt1);

   /// go around the circle
   for (double radians = increment;
        radians <= M_PI * 2.0 + .5;
        radians += increment) {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f(center.getX(), center.getY());
      glVertex2f(pt1.getX(),    pt1.getY()   );
      glVertex2f(pt2.getX(),    pt2.getY()   );
      
      pt1 = pt2;
   }

   /// complete drawing
   glColor3f(1.0, 1.0, 1.0); //Reset to white
   glEnd();   
}

bool isValidFile(const string& filePath) {
   int res = access(filePath.c_str(), R_OK);
   if (res < 0) {
      /// File does not exist
      if (errno == ENOENT) {
         cerr << "File not found: \"" << filePath << "\".\n";
      /// File is not readable
      } else if (errno == EACCES) {
         cerr << "Corrupt file: \"" << filePath << "\".\n";
      }
      return false;
   }
   return true;
}

void drawImage(Point center, const string& imagePath, int rotation, bool verticalFlip, bool horizontalFlip) {

   Point topLeft(center.getX() - SQUARE_SIZE / 2, center.getY() + SQUARE_SIZE / 2);
   ifstream fin(imagePath);
   if (fin.fail()) {
      cerr << "Failed to read file \"" << imagePath << "\".\n";
      return;
   }

   string inputText;

   glBegin(GL_POINTS);
   float rgba_xy[5];
   while (!fin.eof()) {
      for (int i = 0; i < 5 && !fin.eof(); i++) {
         fin >> inputText;
         rgba_xy[i] = stof(inputText);
      }
      Point pt;
      if (verticalFlip && horizontalFlip)
         pt = Point(topLeft.getX() - rgba_xy[3] + SQUARE_SIZE, topLeft.getY() + rgba_xy[4] - SQUARE_SIZE);

      else if (verticalFlip)
         pt = Point(topLeft.getX() - rgba_xy[3] + SQUARE_SIZE, topLeft.getY() - rgba_xy[4]);

      else if (horizontalFlip)
         pt = Point(topLeft.getX() + rgba_xy[3], topLeft.getY() + rgba_xy[4] - SQUARE_SIZE);

      else
         pt = Point(topLeft.getX() + rgba_xy[3], topLeft.getY() - rgba_xy[4]);

      if (rotation)
         rotate(pt, center, rotation);

      glColor3f(rgba_xy[0], rgba_xy[1], rgba_xy[2]);
      glVertex2i(pt.getX(), pt.getY());
   }
   glColor3f(1, 1, 1);
   glEnd();

   fin.close();
}

/**
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num < max)
 *    OUTPUT   <return> : Return the integer
 */
int random(int min, int max) {
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/**
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num < max)
 *    OUTPUT   <return> : Return the double
 */
double random(double min, double max) {
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));

   assert(min <= num && num <= max);

   return num;
}

void glColor3f(Color c) {
   glColor3f(c.red(), c.green(), c.blue());
}

void quit() {
   glutLeaveMainLoop();
}
