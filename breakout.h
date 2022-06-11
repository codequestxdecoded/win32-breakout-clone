#ifndef HEADER_5F479F324304F52C
#define HEADER_5F479F324304F52C

#include "gameobjects.h"
#include "boardgame.h"

void breakout_init_blocks(b2World* world, LPBLOCK** block, const u32 block_count, vector2 location, bsize box_size, bsize box_margin, u32 max_column);
void breakout_free_blocks(b2World* world, LPBLOCK* blocks, const u32 block_count);
void breakout_init_game(vector2 p1, vector2 p2,b2World* world, LPPAD* pad, LPBLOCK** blocks);
//void breakout_init_section(LPSECTION* section, vector2 position, bsize size, THEME theme);

#endif // header guard

