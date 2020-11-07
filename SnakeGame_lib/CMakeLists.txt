project(SnakeGame)

include_directories(include src)

set(HEADER_FILES
        include/Snake.h
        include/Point.h
        include/Fruit.h
        include/definitions.h
        include/Game.h
        include/uiDraw.h
        include/uiInteract.h
        include/Color.h
        include/Menu.h)

set(SOURCE_FILES
        src/Snake.cpp
        src/Point.cpp
        src/Fruit.cpp
        src/Game.cpp
        src/uiDraw.cpp
        src/uiInteract.cpp
        src/Menu.cpp)

add_library(SnakeGame_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
