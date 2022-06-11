#ifndef HEADER_91D05F3735B78192
#define HEADER_91D05F3735B78192

#include "vector2.h"
#include "box2d/box2d.h"
#include "theme.h"


typedef struct{
    vector2 min;
    vector2 max;
    b2Body* body;
    b2Fixture* fixture;
    THEME theme;
}BOARDGAME, *LPBOARDGAME;

#endif // header guard

