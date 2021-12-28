#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH sf::VideoMode::getDesktopMode().width
#define SCREEN_HEIGHT sf::VideoMode::getDesktopMode().height

#if SCREEN_HEIGHT < (unsigned)780
#define WINDOW_WIDTH 531
#define WINDOW_HEIGHT 585
#elif SCREEN_HEIGHT < (unsigned)975
#define WINDOW_WIDTH 708
#define WINDOW_HEIGHT 780
#else
#define WINDOW_WIDTH 885
#define WINDOW_HEIGHT 975
#endif

#endif