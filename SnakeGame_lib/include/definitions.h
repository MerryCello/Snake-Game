//
// Created by Kevin on 8/12/2020.
//

#ifndef TESTING_TEST_DEFINITIONS_H
#define TESTING_TEST_DEFINITIONS_H


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define SQUARE_SIZE (WINDOW_WIDTH * 0.04)
#define ABS_PATH "C:/Users/kevin/Documents/C++_projects/Unit-testing/Snake-Game/SnakeGame_lib/"

/**
 * COLORS
 */
/// #85AE05
#define GREEN(rgb) \
              (rgb == "r" ? 0.52 : \
              (rgb == "g" ? 0.68 : \
              (rgb == "b" ? 0.02 : \
              /* default */ 1.00)))

/// #921A00
#define BROWN(rgb) \
              (rgb == "r" ? 0.57 : \
              (rgb == "g" ? 0.10 : \
              (rgb == "b" ? 0.00 : \
              /* default */ 1.00)))

/// #C5784C
#define BEIGE(rgb) \
              (rgb == "r" ? 0.77 : \
              (rgb == "g" ? 0.47 : \
              (rgb == "b" ? 0.30 : \
              /* default */ 1.00)))

/// #4C8EC5
#define BLUE(rgb) \
              (rgb == "r" ? 0.30 : \
              (rgb == "g" ? 0.56 : \
              (rgb == "b" ? 0.77 : \
              /* default */ 1.00)))

/// #CC2500
#define RED_LIGHT(rgb) \
              (rgb == "r" ? 0.97 : \
              (rgb == "g" ? 0.18 : \
              (rgb == "b" ? 0.00 : \
              /* default */ 1.00)))

/// #F72D00
#define RED_DARK(rgb) \
              (rgb == "r" ? 0.80 : \
              (rgb == "g" ? 0.15 : \
              (rgb == "b" ? 0.00 : \
              /* default */ 1.00)))

/// #1BCC00
#define GREEN_LIGHT(rgb) \
              (rgb == "r" ? 0.11 : \
              (rgb == "g" ? 0.80 : \
              (rgb == "b" ? 0.00 : \
              /* default */ 1.00)))

/// #323232
#define GRAY_DARK(rgb) \
              (rgb == "r" ? 0.20 : \
              (rgb == "g" ? 0.20 : \
              (rgb == "b" ? 0.20 : \
              /* default */ 1.00)))

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3


#endif //TESTING_TEST_DEFINITIONS_H
