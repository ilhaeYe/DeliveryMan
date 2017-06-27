#include "InputManager.h"
#include <conio.h>
#include <iostream>

void InputManager::GetInput()
{
    _inputState = eINPUT_STATE::NONE;

    char input = _getch();

    switch (input)
    {
    case 'w': case 'W': _inputState = eINPUT_STATE::UP; break;
    case 's': case 'S': _inputState = eINPUT_STATE::DOWN; break;
    case 'a': case 'A': _inputState = eINPUT_STATE::LEFT; break;
    case 'd': case 'D': _inputState = eINPUT_STATE::RIGHT; break;
    case 'q': case 'Q': _inputState = eINPUT_STATE::QUIT; break;
    case 'r': case 'R':
    case 'u': case 'U': _inputState = eINPUT_STATE::NONE; break;
    default: std::cout << "Wrong input : " << input << std::endl; break;
    }
}
