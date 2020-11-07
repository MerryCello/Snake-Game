cmake_minimum_required(VERSION 3.17)
project(unit_testing-on-Snake_game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Install CACHE PATH "install here" FORCE)

set(SOURCE_FILES main.cpp)
add_executable(SnakeGame_run ${SOURCE_FILES})

include_directories(SnakeGame_lib)
add_subdirectory(SnakeGame_lib)

target_link_libraries(SnakeGame_run SnakeGame_lib glu32.dll -lOpenGL32 -lfreeGLUT)
#target_link_libraries(SnakeGame_run SnakeGame_lib -lopengl32 -lglew32 -lfreeglut -lglu32)
#target_link_libraries(SnakeGame_run SnakeGame_lib Opengl32.lib glu32.dll)

install(TARGETS SnakeGame_run DESTINATION deb CONFIGURATIONS Debug)
#set(DEPENDENCIES
#        C:/MinGW/bin/freeglut.dll
#        C:/MinGW/include/GL/freeglut.h
#        C:/MinGW/include/GL/freeglut_ext.h
#        C:/MinGW/include/GL/freeglut_std.h
#        C:/MinGW/include/GL/gl.h
#        C:/MinGW/include/GL/glext.h
#        C:/MinGW/include/GL/glu.h
#        C:/MinGW/include/GL/glut.h
#        C:/MinGW/lib/x64/libfreeglut.a
#        C:/MinGW/lib/x64/libfreeglut_static.a
#        C:/Windows/System32/glu32.dll
#        C:/Windows/System32/opengl32.dll
#        )
#foreach(DEPENDENCY ${DEPENDENCIES})
#    install(PROGRAMS "${DEPENDENCY}" DESTINATION deb)
#endforeach()
#install(TARGETS SnakeGame_run DESTINATION rel CONFIGURATIONS Release)

#add_subdirectory(Google_tests)
