gcc objects/main.o objects/helpers.o objects/tic-tac-toe.o objects/difficulty_screen.o objects/gameplay_screen.o objects/mainmenu_screen.o -o main -O2 -Wall -std=c99 -Wno-missing-braces -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm