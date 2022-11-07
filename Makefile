CC := gcc
CFLAGS := -O2 -Wall -std=c99 -Wno-missing-braces

OBJ := objects
SRC := src

# Main raylib path
RAYLIB_PATH := # Place your raylib src path here. (C:/raylib/src)

INCLUDE := include/  # $(RAYLIB_PATH)
LIB := lib/  # $(RAYLIB_PATH)
LINKERS := -lraylib -lopengl32 -lgdi32 -lwinmm #-mwindows

all: objects main 

objects:
	@mkdir -p objects
	
main : $(OBJ)/main.o $(OBJ)/helpers.o $(OBJ)/tic-tac-toe.o $(OBJ)/difficulty_screen.o $(OBJ)/gameplay_screen.o $(OBJ)/mainmenu_screen.o
	$(CC) $^ -o $@ $(CFLAGS) -L$(LIB) $(LINKERS)

$(OBJ)/main.o : $(SRC)/main.c
	$(CC) $^ -c -o $@ $(CFLAGS) -I$(INCLUDE) -L$(LIB) $(LINKERS)

$(OBJ)/helpers.o : $(SRC)/helpers.c
	$(CC) $^ -c -o $@ $(CFLAGS) -I$(INCLUDE) -L$(LIB) $(LINKERS)

$(OBJ)/tic-tac-toe.o : $(SRC)/tic-tac-toe.c
	$(CC) $^ -c -o $@ $(CFLAGS) -I$(INCLUDE) -L$(LIB) $(LINKERS)

$(OBJ)/difficulty_screen.o : $(SRC)/difficulty_screen.c
	$(CC) $^ -c -o $@ $(CFLAGS) -I$(INCLUDE) -L$(LIB) $(LINKERS)

$(OBJ)/gameplay_screen.o : $(SRC)/gameplay_screen.c
	$(CC) $^ -c -o $@ $(CFLAGS) -I$(INCLUDE) -L$(LIB) $(LINKERS)

$(OBJ)/mainmenu_screen.o : $(SRC)/mainmenu_screen.c
	$(CC) $^ -c -o $@ $(CFLAGS) -I$(INCLUDE) -L$(LIB) $(LINKERS)

clean:
	rm -f $(OBJ)/*.o

run:
	./main

