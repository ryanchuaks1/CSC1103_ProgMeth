#ifndef HELPERS_H
#define HELPERS_H

#include "../include/raylib.h"
#include "../include/screens.h"

int checkButton(Rectangle buttons[3]);
void navigate(enum GameScreen nextScreen);
int min(int a, int b);
int max(int a, int b);

#endif