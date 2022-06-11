#ifndef HEADER_A0A4C67A96DEA898
#define HEADER_A0A4C67A96DEA898

#include "vector2.h"
#include "box2d/box2d.h"

typedef struct{
    vector2 center;
    bsize box_size;
    u32 border_size;
    COLORREF border_color;
    COLORREF bg_color;
    b2Body* body;

}BLOCK, *LPBLOCK;

#endif // header guard

