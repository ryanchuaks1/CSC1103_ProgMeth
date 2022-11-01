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

main : $(OBJ)/main.o $(OBJ)/functions.o
	$(CC) $^ -o $@ $(CFLAGS) -L$(LIB) $(LINKERS)

$(OBJ)/main.o : $(SRC)/main.c
	$(CC) $^ -c -o $@ $(CFLAGS) -I$(INCLUDE) -L$(LIB) $(LINKERS)

$(OBJ)/functions.o : $(SRC)/functions.c
	$(CC) $^ -c -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)/*.o

run:
	./main
