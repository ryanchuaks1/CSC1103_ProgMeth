#ifndef SCREENS_H
#define SCREENS_H

extern float textureScroll;

enum GameScreen {
    MainMenuScreen,
    DifficultyScreen,
    GameplayScreen,
    MultiplayerMode,
    NormalAIMode,
    ImpossibleAIMode,
};

enum GameplayMode {
    Multiplayer,
    MediumAI,
    ImpossibleAI,
};

// Main Menu Screens //
void InitMainMenuScreen();
void UpdateMainMenuScreen();
void DrawMainMenuScreen();
void UnloadMainMenuScreen();
int FinishMainMenuScreen();

// Difficulty Screens //
void InitDifficultyScreen();
void UpdateDifficultyScreen();
void DrawDifficultyScreen();
void UnloadDifficultyScreen();
int FinishDifficultyScreen();


// Gameplay Screens //
void InitGameplayScreen(enum GameplayMode mode);
void UpdateGameplayScreen();
void DrawGameplayScreen();
void UnloadGameplayScreen();
int FinishGameplayScreen();

#endif