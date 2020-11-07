//
// Created by Kevin on 8/12/2020.
//

#include "gtest/gtest.h"
#define private public
#include <include/Snake.h>
#include <include/definitions.h>
using namespace std;

/// Test the forward movement
TEST(MoveSnake, forward) {
    Snake snake(Point(0, 0), LEFT);
    list<Point> shouldBeSnakeBody = {
            Point(-1 * SQUARE_SIZE, 0),
            Point( 0              , 0),
            Point( 1 * SQUARE_SIZE, 0)
    };

    snake.moveForward();

    EXPECT_TRUE(shouldBeSnakeBody == snake.body);
}

/// Test the left movement
TEST(MoveSnake, left) {
    Snake snake(Point(0, 0), LEFT);
    list<Point> shouldBeSnakeBody = {
            Point(0              , -1 * SQUARE_SIZE),
            Point(0              ,  0              ),
            Point(1 * SQUARE_SIZE,  0              )
    };

    snake.moveLeft();

    EXPECT_TRUE(shouldBeSnakeBody == snake.body);
}

/// Test the right movement
TEST(MoveSnake, right) {
    Snake snake(Point(0, 0), LEFT);
    list<Point> shouldBeSnakeBody = {
            Point(0              , 1 * SQUARE_SIZE),
            Point(0              , 0              ),
            Point(1 * SQUARE_SIZE, 0              )
    };

    snake.moveRight();

    EXPECT_TRUE(shouldBeSnakeBody == snake.body);
}
