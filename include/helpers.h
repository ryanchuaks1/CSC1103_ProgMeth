#ifndef HELPERS_H
#define HELPERS_H

#include "../include/raylib.h"

int mouseCollide(Vector2 mousePos, Vector2 gridPos, int gridSize, int gridThickness);
int checkButton(Rectangle buttons[3]);

#endif