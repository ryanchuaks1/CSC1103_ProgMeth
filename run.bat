gcc src/main.c -c -o objects/main.o -O2 -Wall -std=c99 -Wno-missing-braces -Iinclude/   -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm
gcc src/helpers.c -c -o objects/helpers.o -O2 -Wall -std=c99 -Wno-missing-braces -Iinclude/   -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm
gcc src/tic-tac-toe.c -c -o objects/tic-tac-toe.o -O2 -Wall -std=c99 -Wno-missing-braces -Iinclude/   -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm
gcc src/difficulty_screen.c -c -o objects/difficulty_screen.o -O2 -Wall -std=c99 -Wno-missing-braces -Iinclude/   -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm
gcc src/gameplay_screen.c -c -o objects/gameplay_screen.o -O2 -Wall -std=c99 -Wno-missing-braces -Iinclude/   -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm
gcc src/mainmenu_screen.c -c -o objects/mainmenu_screen.o -O2 -Wall -std=c99 -Wno-missing-braces -Iinclude/   -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm
gcc objects/main.o objects/helpers.o objects/tic-tac-toe.o objects/difficulty_screen.o objects/gameplay_screen.o objects/mainmenu_screen.o -o tictactoe -O2 -Wall -std=c99 -Wno-missing-braces -Llib/   -lraylib -lopengl32 -lgdi32 -lwinmm