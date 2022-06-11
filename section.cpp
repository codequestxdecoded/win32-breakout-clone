

#include "section.h"


void section_create(LPSECTION* section, vector2 bmin,vector2 bmax, THEME theme){
    (*section) = (LPSECTION)malloc(sizeof(SECTION));
    (*section)->min = bmin;
    (*section)->max = bmax;
    (*section)->theme = theme;
}

void section_render(HDC hdc, LPSECTION section){

    int x = section->min.x;
    int y =section->min.y;
    int w = section->max.x - x;
    int h = section->max.y - y;

    Rectangle(hdc, x, y, w, h);
}

void section_resize(LPSECTION section, int w, int h){
    section->max.x += w;
    section->max.y += h;
}
