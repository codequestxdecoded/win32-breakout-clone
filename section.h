#ifndef HEADER_FD63FA53D35A8E5
#define HEADER_FD63FA53D35A8E5

#include <windows.h>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  800



#include "vector2.h"
#include "theme.h"


typedef struct {
    vector2 min;
    vector2 max;
    THEME theme;

} SECTION, *LPSECTION;

void section_create(LPSECTION* section, vector2 bmin,vector2 bmax, THEME theme);
void section_render(HDC hdc, LPSECTION section);
void section_resize(LPSECTION section, int w, int h);

#endif // header guard

