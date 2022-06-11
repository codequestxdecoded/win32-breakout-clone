#ifndef HEADER_A18FC31AF8CDA564
#define HEADER_A18FC31AF8CDA564

#include "blockdef.h"

void block_create(LPBLOCK* block, u32 x, u32 y, u32 w, u32 h);
void block_color(LPBLOCK block,u32 border_size, COLORREF border, COLORREF background);
void block_create_body(LPBLOCK block, b2World* world);
void block_render(HDC hdc, LPBLOCK block);

#endif // header guard

