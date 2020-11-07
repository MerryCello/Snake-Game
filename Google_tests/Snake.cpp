//
// Created by Kevin on 8/12/2020.
//

#include "gtest/gtest.h"
#define private public
#include "include/Snake.h"
#include "include/definitions.h"
#include "include/Point.h"
using namespace std;

/// Test getHead
TEST(Snake, getHeadPoint) {
    Point snakeHeadPoint(0,0);
    Snake snake(snakeHeadPoint, LEFT);

    EXPECT_TRUE(snake.getHead() == snakeHeadPoint);
}

TEST(Snake, setHeadPoint) {
    Snake snake(Point(0, 0), LEFT);
    list<Point> shouldBeNewSnakeBody = {
            Point(3 * SQUARE_SIZE, 0 * SQUARE_SIZE), /// Head
            Point(4 * SQUARE_SIZE, 0 * SQUARE_SIZE),
            Point(5 * SQUARE_SIZE, 0 * SQUARE_SIZE)  /// Tail
    };

    snake.setHeadPoint(Point(3 * SQUARE_SIZE, 3 * SQUARE_SIZE));
}

/// Test Dependent on MoveSnake.right
TEST(Snake, growWhileUP) {
    Snake snake(Point(0, 0), UP);
    list<Point> shouldBeSnakeBody = {
            Point(0,  0 * SQUARE_SIZE), /// Head
            Point(0, -1 * SQUARE_SIZE),
            Point(0, -2 * SQUARE_SIZE),
            Point(0, -3 * SQUARE_SIZE)  /// Tail
    };

    snake.grow();

    EXPECT_TRUE(shouldBeSnakeBody == snake.body);
}

/// Test Dependent on MoveSnake.left
TEST(Snake, growWhileDown) {
    Snake snake(Point(0, 0), DOWN);
    list<Point> shouldBeSnakeBody = {
            Point(0, 0 * SQUARE_SIZE), /// Head
            Point(0, 1 * SQUARE_SIZE),
            Point(0, 2 * SQUARE_SIZE),
            Point(0, 3 * SQUARE_SIZE)  /// Tail
    };

    snake.grow();

    EXPECT_TRUE(shouldBeSnakeBody == snake.body);
}

/// Test Dependent on MoveSnake.forward
TEST(Snake, growWhileLeft) {
    Snake snake(Point(0, 0), LEFT);
    list<Point> shouldBeSnakeBody = {
            Point(0 * SQUARE_SIZE, 0), /// Head
            Point(1 * SQUARE_SIZE, 0),
            Point(2 * SQUARE_SIZE, 0),
            Point(3 * SQUARE_SIZE, 0)  /// Tail
    };

    snake.grow();

    EXPECT_TRUE(shouldBeSnakeBody == snake.body);
}

/// Test Dependent on MoveSnake.forward
TEST(Snake, growWhileRight) {
    Snake snake(Point(0, 0), RIGHT);
    list<Point> shouldBeSnakeBody = {
            Point( 0 * SQUARE_SIZE, 0), /// Head
            Point(-1 * SQUARE_SIZE, 0),
            Point(-2 * SQUARE_SIZE, 0),
            Point(-3 * SQUARE_SIZE, 0)  /// Tail
    };

    snake.grow();

    EXPECT_TRUE(shouldBeSnakeBody == snake.body);
}

/// Test draw snake
TEST(Snake, draw) {
    Snake snake(Point(0, 0), LEFT);

    EXPECT_TRUE(snake.draw());
}
