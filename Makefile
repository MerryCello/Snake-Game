###############################################################
# Program:
#     Snake Game
# Author:
#     Kevin Foniciello
# Summary:
#
###############################################################


LFLAGS = -lglut -lGLU -lGL
OBJDIR = ./.makefileObjects

###############################################################
# Build the main game
###############################################################
a.out: directories ${OBJDIR}/main.o ${OBJDIR}/Game.o ${OBJDIR}/uiInteract.o \
				   ${OBJDIR}/uiDraw.o ${OBJDIR}/Point.o ${OBJDIR}/Snake.o \
				   ${OBJDIR}/Fruit.o ${OBJDIR}/Color.o ${OBJDIR}/Menu.o
	g++ ${OBJDIR}/*.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    Point.o       The position on the screen
#    Game.o        Handles the game interaction
#	 Fruit.o
# 	 Snake.o
#    Color.o
#    Menu.o
###############################################################
${OBJDIR}/uiDraw.o: SnakeGame_lib/src/uiDraw.cpp SnakeGame_lib/include/uiDraw.h SnakeGame_lib/include/Point.h
	g++ -c SnakeGame_lib/uiDraw.cpp -o $@

${OBJDIR}/uiInteract.o: SnakeGame_lib/src/uiInteract.cpp SnakeGame_lib/include/uiInteract.h
	g++ -c SnakeGame_lib/uiInteract.cpp -o $@

${OBJDIR}/Point.o: SnakeGame_lib/src/Point.cpp SnakeGame_lib/include/Point.h
	g++ -c SnakeGame_lib/Point.cpp -o $@

${OBJDIR}/Game.o: SnakeGame_lib/src/Game.cpp SnakeGame_lib/include/Game.h SnakeGame_lib/include/uiDraw.h SnakeGame_lib/include/uiInteract.h SnakeGame_lib/include/Point.h SnakeGame_lib/include/Snake.h SnakeGame_lib/include/Fruit.h
	g++ -c SnakeGame_lib/Game.cpp -o $@

${OBJDIR}/main.o: SnakeGame_lib/include/Game.h SnakeGame_lib/include/uiInteract.h main.cpp
	g++ -c main.cpp -o $@

${OBJDIR}/Snake.o: SnakeGame_lib/include/Snake.h SnakeGame_lib/include/Point.h SnakeGame_lib/include/uiDraw.h SnakeGame_lib/src/Snake.cpp
	g++ -c SnakeGame_lib/Snake.cpp -o $@

${OBJDIR}/Fruit.o: SnakeGame_lib/src/Fruit.cpp SnakeGame_lib/include/Fruit.h SnakeGame_lib/include/Point.h
	g++ -c SnakeGame_lib/Fruit.cpp -o $@

${OBJDIR}/Color.o: SnakeGame_lib/src/Color.cpp SnakeGame_lib/include/Color.h
	g++ -c SnakeGame_lib/Color.cpp -o $@

${OBJDIR}/Menu.o: SnakeGame_lib/src/Menu.cpp SnakeGame_lib/include/Menu.h SnakeGame_lib/include/Point.h SnakeGame_lib/include/uiDraw.h SnakeGame_lib/include/definitions.h
	g++ -c SnakeGame_lib/Menu.cpp -o $@

###############################################################
# General rules
###############################################################
clean:
	@rm ${OBJDIR}/*
	@rm a.out *.o

# Make OBJDIR if needs be
directories:
	@mkdir -p ${OBJDIR}
