#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
//
// Created by Kevin on 8/12/2020.
//

#include "gtest/gtest.h"
#define private public
#include "include/Snake.h"
#include "include/definitions.h"
#include "include/Point.h"
using namespace std;

/**
 * Is the snake created as expected?
 */

/// It should be alive when first created
TEST(NewSnake, isAlive) {
    Snake snake(Point(0, 0), UP);

    EXPECT_TRUE(snake.isAlive());
}


/// Test the direction of the body
TEST(NewSnake, bodyIsInOrder) {
    auto *snake = new Snake(Point(0, 0), UP);
    list<Point> shouldBeSnakeBody;

    for (int direction = 0;;) {

        shouldBeSnakeBody.emplace_back(0, 0);
        switch (direction) {
            case UP: {
                shouldBeSnakeBody.emplace_back(0, -1 * SQUARE_SIZE);
                shouldBeSnakeBody.emplace_back(0, -2 * SQUARE_SIZE);
                break;
            }
            case DOWN: {
                shouldBeSnakeBody.emplace_back(0, 1 * SQUARE_SIZE);
                shouldBeSnakeBody.emplace_back(0, 2 * SQUARE_SIZE);
                break;
            }
            case LEFT: {
                shouldBeSnakeBody.emplace_back(1 * SQUARE_SIZE, 0);
                shouldBeSnakeBody.emplace_back(2 * SQUARE_SIZE, 0);
                break;
            }
            case RIGHT: {
                shouldBeSnakeBody.emplace_back(-1 * SQUARE_SIZE, 0);
                shouldBeSnakeBody.emplace_back(-2 * SQUARE_SIZE, 0);
                break;
            }
        }

        EXPECT_TRUE(shouldBeSnakeBody == snake->body);

        shouldBeSnakeBody.clear();
        delete snake;
        snake = nullptr;
        direction++;
        if (direction < 4) snake = new Snake(Point(0, 0), direction);
        else break;
    }
    delete snake;
}

#pragma clang diagnostic pop