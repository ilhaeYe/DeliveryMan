#pragma once
#include <vector>
#include <iostream>
#include "InputManager.h"

class LevelManager
{
public:
    LevelManager(const int level);
    ~LevelManager();

public:
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }

    void ResetLevel();
    void Render();

    //
    void MoveLogic(const eINPUT_STATE inputState);
    bool IsWin();

private:
    int GetMapData(const int x, const int y) const;
    void SetMapData(const int x, const int y, const int data);

    void LoadLevel(const int level);

    //
    int GetPlayerPos();
    void MovePlayer(const int dx, const int dy);

private:
    std::vector<int> _map;
    int _level;
    int _width;
    int _height;

    int _playerPos;

};