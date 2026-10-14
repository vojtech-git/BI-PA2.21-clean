#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include <curses.h>
#else
    #include <ncurses.h>
#endif