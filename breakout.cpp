#include "breakout.h"

void breakout_init_blocks(b2World* world, LPBLOCK** block, const u32 block_count, vector2 location, bsize box_size, bsize box_margin, u32 max_column){

    (*block) = (LPBLOCK*) malloc( sizeof(BLOCK*) * block_count);
    f32 bw = box_size.w;
    f32 bh = box_size.h;
    //cout<<"box size x: "<<box_size.w<<" y: "<<box_size.h<<endl;
    f32 xx = location.x;
    f32 yy = location.y;
    COLORREF cr = 0x8833cc;
    for(int i=0; i<block_count; i++){

        block_create(&(*block)[i], xx , yy, bw, bh);
        block_create_body((*block)[i], world);
        cr = cr + 0x000712;
        block_color((*block)[i], 1, BREAK_WHITE, cr);

        xx += bw + box_margin.w;

        if(xx >= (location.x + bw*max_column)){
            xx = location.x;
            yy += bh + box_margin.h;
            cr += 0x010533;
        }
    }

}

void breakout_init_game(vector2 p1, vector2 p2,b2World* world, LPPAD* pad, LPBLOCK** blocks){

    int x = p1.x;
    int y = p1.y;
    int w = p2.x - p1.x;
    int h = p2.y - p1.y;

    int margin_width = 1;
    int margin_height = 1;
    int column_count = 6;
    int block_count = 24;
    int block_width = w/column_count - margin_width * column_count*2;
    int block_height = h/3/column_count - margin_height*column_count*2;

    f32 blockx = x + block_width;
    f32 blocky = y + block_height;

    f32 padx = x + w/2;
    f32 pady = h;// - h*.01f;
    f32 padw = block_width*1.8f;
    f32 padh = block_height*.8f;

    breakout_init_blocks(world, blocks, block_count, {blockx,blocky},{block_width, block_height}, {margin_width, margin_height}, column_count);
    pad_create(pad, padx, pady, padw, padh);
    pad_create_body(*pad, world);
    pad_color(*pad, 1, BREAK_BLUE, BREAK_GREEN);

    LPBOARDGAME board;
    boardgame_init(&board, p1, p2, world );

}


void breakout_free_blocks(b2World* world, LPBLOCK* blocks, const u32 block_count){

    for(int i=0; i<block_count; i++){
        world->DestroyBody(blocks[i]->body);
        blocks[i]->body = nullptr;
    }

    free(blocks);
}


