#ifndef HEADER_B451293D25F4C380
#define HEADER_B451293D25F4C380

#include "vector2.h"
#include "box2d/box2d.h"

typedef struct{
    vector2 start;
    u32 radius;
    COLORREF border_color;
    COLORREF bg_color;
    b2Body* body;

}BALL, *LPBALL;

#endif // header guard

