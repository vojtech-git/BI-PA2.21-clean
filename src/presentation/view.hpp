#pragma once
#include "curses_wrapper.hpp"
#include <string>

class View
{
private:
    WINDOW *window_;
    int width_;
    int height_;

public:
    View(int width = 80, int height = 24);
    ~View();

    void ClearScreen();
    void DrawText(int x_position, int y_position, const std::string &text);
    void Render();
    int GetInput();
    int GetWidth() const;
    int GetHeight() const;
};