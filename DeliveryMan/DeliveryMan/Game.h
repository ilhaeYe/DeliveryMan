#pragma once
#include <memory>
#include "LevelManager.h"
#include "InputManager.h"

class Game
{
public:
    Game(const int level);
    ~Game() = default;

    void Run();

private:
    void Render();
    void GetInput();
    void UpdateGame();

    bool InitInputManager();
    bool InitLevelManager(const int level);

private:
    int _level;
    bool _isPlaying;
    bool _isLoaded;
    std::unique_ptr<LevelManager> pLevelMgr;
    std::unique_ptr<InputManager> pInputMgr;

};