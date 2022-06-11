#ifndef HEADER_EBCA4CB1339F998D
#define HEADER_EBCA4CB1339F998D

#include "vector2.h"
#include "box2d/box2d.h"

typedef struct{
    vector2 start;
    bsize box_size;
    u32 border_size;
    COLORREF border_color;
    COLORREF bg_color;
    b2Body* body;
}PAD, *LPPAD;

#endif // header guard

