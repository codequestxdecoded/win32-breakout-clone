#ifndef HEADER_C4B114C6E5B24AD4
#define HEADER_C4B114C6E5B24AD4

#include "paddef.h"

void pad_create(LPPAD* block, u32 x, u32 y, u32 w, u32 h);
void pad_color(LPPAD block,u32 border_size, COLORREF border, COLORREF background);
void pad_create_body(LPPAD block, b2World* world);
void pad_move(LPPAD pad, int dx);
void pad_render(HDC hdc, LPPAD pad);

#endif // header guard

