#include "Game.h"
#include <iostream>
#include <conio.h>
#include "LevelManager.h"
#include "InputManager.h"

Game::Game(const int level) : _level(level), _isPlaying(true), _isLoaded(false)
{
    _isLoaded = InitInputManager();
    _isLoaded &= InitLevelManager(_level);
}

void Game::Run()
{
    while (_isLoaded && _isPlaying)
    {
        Render();
        GetInput();
        UpdateGame();
    }
}

void Game::Render()
{
    system("cls");

    if (pLevelMgr == nullptr)
    {
        std::cout << "pLevelMgr is nullptr" << std::endl;
        _isPlaying = false;
        return;
    }

    pLevelMgr->Render();
}

void Game::GetInput()
{
    if (pInputMgr == nullptr)
    {
        std::cout << "pInputMgr is nullptr" << std::endl;
        _isPlaying = false;
        return;
    }

    pInputMgr->GetInput();
}

void Game::UpdateGame()
{
    if (pInputMgr == nullptr)
    {
        std::cout << "pInputMgr is nullptr" << std::endl;
        _isPlaying = false;
        return;
    }
    if (pLevelMgr == nullptr)
    {
        std::cout << "pLevelMgr is nullptr" << std::endl;
        _isPlaying = false;
        return;
    }

    const eINPUT_STATE inputState = pInputMgr->GetInputState();
    switch (inputState)
    {
    case eINPUT_STATE::QUIT: _isPlaying = false; return;
    case eINPUT_STATE::UP: case eINPUT_STATE::DOWN:
    case eINPUT_STATE::LEFT: case eINPUT_STATE::RIGHT:
        pLevelMgr->MoveLogic(inputState); // TODO
        break;
    case eINPUT_STATE::NONE: break;
    }

    if (pLevelMgr->IsWin())
    {
        std::cout << "You win" << std::endl;
        _isPlaying = false;
        return;
    }

}

bool Game::InitInputManager()
{
    pInputMgr = std::make_unique<InputManager>();
    if (pInputMgr == nullptr)
        return false;

    return true;
}

bool Game::InitLevelManager(const int level)
{
    pLevelMgr = std::make_unique<LevelManager>(level);
    if (pLevelMgr == nullptr)
        return false;

    return true;
}
