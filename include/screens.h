#ifndef SCREENS_H
#define SCREENS_H

extern float textureScroll;
extern enum GameScreen currentScreen;
extern struct Sound buttonClickSound;
extern struct Sound gameStartSound;

typedef enum GameScreen
{
    MainMenuScreen,
    DifficultyScreen,
    GameplayScreen,
    MultiplayerMode,
    EasyAIMode,
    MediumAIMode,
    ImpossibleAIMode,
} GameScreen;

// Potentially move this out as tic-tac-toe as an enum already
typedef enum GameplayMode
{
    Multiplayer,
    EasyAI,
    MediumAI,
    ImpossibleAI,
} GameplayMode;

// Main Menu Screens //
void InitMainMenuScreen();
void UpdateMainMenuScreen();
void DrawMainMenuScreen();
void UnloadMainMenuScreen();

// Difficulty Screens //
void InitDifficultyScreen();
void UpdateDifficultyScreen();
void DrawDifficultyScreen();
void UnloadDifficultyScreen();

// Gameplay Screens //
void InitGameplayScreen(GameplayMode mode);
void UpdateGameplayScreen();
void DrawGameplayScreen();
void UnloadGameplayScreen();

#endif