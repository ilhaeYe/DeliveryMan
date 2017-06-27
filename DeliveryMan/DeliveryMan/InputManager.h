#pragma once

//class Command;

enum eINPUT_STATE
{
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
    QUIT = 5,
};

class InputManager
{
public:
    InputManager() = default;
    ~InputManager() = default;

    //void Reset();
    //void AddCommand();
    //void RemoveCommand();
    //void Undo();
    //void Redo();

    void GetInput();
    eINPUT_STATE GetInputState() const { return _inputState; }

private:
    //std::stack<Command> _queue;
    eINPUT_STATE _inputState;

};
