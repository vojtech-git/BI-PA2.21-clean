#include "view.hpp"
#include "curses_wrapper.hpp"

View::View(int width, int height)
    : width_(width), height_(height)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();

    int term_h = 0, term_w = 0;
    getmaxyx(stdscr, term_h, term_w);

    int start_y = (term_h > height_) ? (term_h - height_) / 2 : 0;
    int start_x = (term_w > width_) ? (term_w - width_) / 2 : 0;

    window_ = newwin(height_, width_, start_y, start_x);
    keypad(window_, TRUE);
    nodelay(window_, TRUE);
}

View::~View()
{
    if (window_)
    {
        delwin(window_);
    }
    endwin();
}

void View::ClearScreen()
{
    werase(window_);
}

void View::DrawText(int x_position, int y_position, const std::string &text)
{
    int xCentered = x_position - (static_cast<int>(text.length()) / 2);
    if (xCentered < 1) xCentered = 1;
    if (y_position < 1) y_position = 1;

    mvwprintw(window_, y_position, xCentered, "%s", text.c_str());
}

void View::Render()
{
    wrefresh(window_);
}

int View::GetInput()
{
    return wgetch(window_);
}

int View::GetWidth() const
{
    return width_;
}

int View::GetHeight() const
{
    return height_;
}