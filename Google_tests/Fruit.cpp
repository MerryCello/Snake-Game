//
// Created by Kevin on 8/13/2020.
//

#include "gtest/gtest.h"
#define private public
#include "include/Fruit.h"
#include "include/definitions.h"

TEST(fruit, isNotEaten) {
    Fruit fruit("apple", Point());

    ASSERT_TRUE(fruit.isEaten());
    EXPECT_EQ((float)SQUARE_SIZE, fruit.sizeLimit);
}

TEST(fruit, correctType) {
    std::string types[4] = {"apple", "cherry", "banana", "strawberry"};
    std::string wrongTypes[2] = {"pear", "jehrt989O987ihroi8w((98f39p8&*%#%Jliv7gw9h965344j6u4B%^^"};
    Fruit* pFruit = nullptr;//new Fruit("apple");

    for (const auto& type : types) {
        delete pFruit;
        pFruit = nullptr;
        pFruit = new Fruit(type, Point());
        EXPECT_EQ((std::string)type, pFruit->type);
    }

    for (const auto& wrongType : wrongTypes) {
        delete pFruit;
        pFruit = nullptr;
        pFruit = new Fruit(wrongType, Point());
        EXPECT_NE(wrongType, pFruit->type);
    }

    delete pFruit;
}

TEST(fruit, draw) {
    Fruit fruit("apple", Point());

    ASSERT_TRUE(fruit.draw());
}
