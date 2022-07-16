#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

namespace Mouse {
    typedef enum
    {
        Released,
        Pressed,
    } ButtonState;

    typedef enum
    {
        Default,
        Hand
    }CursorType;

    extern uint8_t cur_normal[13][11];
    extern uint8_t cur_link[13][11];
    extern uint8_t cur_move[13][11];

    extern uint8_t currentCursorData[13][11];

    void    install(uint32_t scr_width, uint32_t scr_height);
    void    draw();
    bool    isLeftPressed();
    bool    isRightPressed();
    int32_t getX();
    int32_t getY();
    void    set_cursor(CursorType cursor);
    bool    isWithin(int x, int y, int width, int height);
}