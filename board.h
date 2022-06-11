#ifndef HEADER_EE1BE8F5E4FC919B
#define HEADER_EE1BE8F5E4FC919B


#include "box2d/box2d.h"

#include<windows.h>

//BOX2D



    // Color constants.
    const COLORREF rgbRed   =  0x000000FF;
    const COLORREF rgbGreen =  0x0000FF00;
    const COLORREF rgbBlue  =  0x00FF0000;
    const COLORREF rgbBlack =  0x00000000;
    const COLORREF rgbWhite =  0x00FFFFFF;

    #define BOARD_WIDTH 450
    #define BOARD_HEIGHT 700
    #define MARGIN_RIGHT 250

    #define SCREEN_WIDTH  1280
    #define SCREEN_HEIGHT  800
    //world



    b2Body* createBorder(b2World* world, float x, float y, float w, float h);

    const int floor_x = SCREEN_WIDTH/2;
    const int floor_y = SCREEN_HEIGHT - 45;
    const int floor_w = SCREEN_WIDTH/2;
    const int floor_h = 5;


    const int left_wall_x = 15;
    const int left_wall_y = (SCREEN_HEIGHT-40)/2;
    const int left_wall_w = 15;
    const int left_wall_h = (SCREEN_HEIGHT-40)/2;



    const int right_wall_x = SCREEN_WIDTH - 30;
    const int right_wall_y = (SCREEN_HEIGHT-40)/2;
    const int right_wall_w = 15;
    const int right_wall_h = (SCREEN_HEIGHT-40)/2;



    const float box_width = 10;
    const float box_height = 10;

    typedef b2Body Box;
    typedef b2Body* LPBox;




typedef b2Body* BORDER;

typedef struct {
    BORDER left;
    BORDER top;
    BORDER right;
    BORDER bottom;
}BPHYSIC, *LPBPYSIC;

typedef struct{
    RECT margin;
    RECT area;
    BPHYSIC physc_border;
    COLORREF bg;
    COLORREF border_color;
    size_t border_size;
    bool resizable;
}GAMEBOARD, *LPGAMEBOARD ;


void board_init(LPGAMEBOARD* board, RECT margin, RECT wnd_rect);
void board_render(HDC hdc, LPGAMEBOARD board);
void board_resize(LPGAMEBOARD board, int w, int h);

void board_physics_init(b2World* world, LPGAMEBOARD board);


LPBox createBox(b2World* world, int x, int y, float width, float height, bool isStatic);


void render_rect(HDC hdc, float x, float y, float w, float h);


#endif // header guard

