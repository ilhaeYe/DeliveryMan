#include "LevelManager.h"
#include "InputManager.h"
#include <algorithm>

enum eDATA_TYPE
{
    SPACE = 0,
    WALL = 1,
    PLAYER = 2,
    BOX = 3,
    GOAL = 4,
    PLAYER_ON_GOAL = 5,
    BOX_ON_GOAL = 6,
};

LevelManager::LevelManager(const int level) : _level(level), _playerPos(-1)
{
    LoadLevel(level);
    _playerPos = GetPlayerPos();
}

LevelManager::~LevelManager()
{
    
}

void LevelManager::ResetLevel()
{
    LoadLevel(_level);
    _playerPos = GetPlayerPos();
}

void LevelManager::Render()
{
    static const char chars[7] = { ' ', '#', 'p', 'o', '.', 'p', 'o' };

    int cnt = 0;
    for (const int data : _map)
    {
        std::cout << chars[data];
        cnt = (cnt + 1) % _width;
        if (cnt == 0)
            std::cout << std::endl;
    }
}

void LevelManager::MoveLogic(const eINPUT_STATE inputState)
{
    int dx = 0;
    int dy = 0;
    switch (inputState)
    {
    case eINPUT_STATE::UP: dy = -1; break;
    case eINPUT_STATE::DOWN: dy = 1; break;
    case eINPUT_STATE::LEFT: dx = -1; break;
    case eINPUT_STATE::RIGHT: dx = 1; break;
    }

    MovePlayer(dx, dy);
}

bool LevelManager::IsWin()
{
    for (const int data : _map)
    {
        if (data == eDATA_TYPE::BOX)
        {
            return false;
        }
    }

    return true;
}

int LevelManager::GetMapData(const int x, const int y) const
{
    if (x >= _width || y >= _height)
    {
        std::cout << "out of range : " << x << ", " << y << std::endl;
        return -1;
    }

    return _map[x + y *_width];
}

void LevelManager::SetMapData(const int x, const int y,const int data)
{
    if (x >= _width || y >= _height)
    {
        std::cout << "out of range : " << x << ", " << y << std::endl;
        return;
    }

    _map[x + y * _width] = data;
}

int LevelManager::GetPlayerPos()
{
    for (int i = 0; i < _map.size(); ++i)
    {
        const int data = _map[i];
        if (data == eDATA_TYPE::PLAYER || data == eDATA_TYPE::PLAYER_ON_GOAL)
        {
            return i;
        }
    }

    return -1;
}

void LevelManager::MovePlayer(const int dx, const int dy)
{
    const int playerX = _playerPos % _width;
    const int playerY = _playerPos / _width;

    const int infrontTargetX = playerX + dx;
    const int infrontTargetY = playerY + dy;
    const int infrontTargetPos = infrontTargetX + infrontTargetY * _width;

    if (infrontTargetPos < 0 || infrontTargetPos >= _map.size())
        return;

    const int infrontTargetPosData = _map[infrontTargetPos];
    const int playerPosData = _map[_playerPos];

    if (infrontTargetPosData == eDATA_TYPE::SPACE
        || infrontTargetPosData == eDATA_TYPE::GOAL)
    {
        _map[infrontTargetPos] = (infrontTargetPosData == eDATA_TYPE::GOAL) ? 
            eDATA_TYPE::PLAYER_ON_GOAL : eDATA_TYPE::PLAYER;
        _map[_playerPos] = (playerPosData == eDATA_TYPE::PLAYER_ON_GOAL) ?
            eDATA_TYPE::GOAL : eDATA_TYPE::SPACE;
        _playerPos = infrontTargetPos;
    }
    else if (infrontTargetPosData == eDATA_TYPE::BOX
        || infrontTargetPosData == eDATA_TYPE::BOX_ON_GOAL)
    {
        const int behindTargetX = infrontTargetX + dx;
        const int behindTargetY = infrontTargetY + dy;
        const int behindTargetPos = behindTargetX + behindTargetY * _width;

        if (behindTargetPos < 0 || behindTargetPos >= _map.size())
            return;

        const int behindTargetPosData = _map[behindTargetPos];

        if (behindTargetPosData == eDATA_TYPE::SPACE
            || behindTargetPosData == eDATA_TYPE::GOAL)
        {
            _map[behindTargetPos] = (behindTargetPosData == eDATA_TYPE::GOAL) ?
                eDATA_TYPE::BOX_ON_GOAL : eDATA_TYPE::BOX;
            _map[infrontTargetPos] = (infrontTargetPosData == eDATA_TYPE::BOX_ON_GOAL) ?
                eDATA_TYPE::PLAYER_ON_GOAL : eDATA_TYPE::PLAYER;
            _map[_playerPos] = (playerPosData == eDATA_TYPE::PLAYER_ON_GOAL) ?
                eDATA_TYPE::GOAL : eDATA_TYPE::SPACE;
            _playerPos = infrontTargetPos;
        }
    }

}

void LevelManager::LoadLevel(const int level)
{
    // TODO : read xml file

    // temp data
    _map.clear();
    _level = level;
    _width = 10;
    _height = 5;
    _map = {
        1,1,1,1,1,1,1,1,1,1,
        1,0,4,4,0,0,0,2,0,1,
        1,0,3,3,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1
    };
}

