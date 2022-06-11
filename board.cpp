#include "board.h"


void board_init(LPGAMEBOARD* board, RECT margin, RECT wnd_rect)
{

    *(board) = (LPGAMEBOARD) malloc(sizeof(GAMEBOARD));

    int w = wnd_rect.right;
    int h = wnd_rect.bottom;

    (*board)->margin = margin;
    (*board)->border_size = 1;

    RECT mrgn = (*board)->margin;
    size_t bsize = (*board)->border_size;

    (*board)->area = (RECT)
    {
        mrgn.left + bsize, mrgn.top + bsize, w - mrgn.right + mrgn.left + bsize, h - mrgn.bottom + mrgn.top + bsize
    };
    (*board)->bg = rgbBlack;
    (*board)->border_color = rgbWhite;

    (*board)->resizable = false;
}
void board_render(HDC hdc, LPGAMEBOARD board)
{

    DWORD pen_style = PS_SOLID ;//| PS_JOIN_MITER | PS_GEOMETRIC;


    HPEN hPen = CreatePen(pen_style, board->border_size, board->border_color);
    HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

    HBRUSH hBrush1 = CreateSolidBrush(board->bg);
    HBRUSH holdBrush = (HBRUSH)SelectObject(hdc, hBrush1);

    Rectangle(hdc, board->area.left, board->area.top, board->area.right,   board->area.bottom);

    SelectObject(hdc, holdPen);
    SelectObject(hdc, holdBrush);

}
void board_resize(LPGAMEBOARD board, int w, int h)
{
    if(!board->resizable) return;
    size_t bsize = board->border_size;
    RECT margin = board->margin;

    board->area.bottom = h - margin.bottom + bsize;
    board->area.right = w - margin.right + bsize;
}

LPBox createBox(b2World* world, int x, int y, float width, float height, bool isStatic){

    b2BodyDef bodydef;
    bodydef.position.Set(x, y);
    bodydef.type = b2BodyType::b2_dynamicBody;
    bodydef.angle = 0.0f;

    LPBox body = world->CreateBody(&bodydef);

    b2PolygonShape shape;
    shape.SetAsBox(width, height);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    //fixtureDef.friction = 0.3f;


    b2Fixture* fixture = body->CreateFixture(&fixtureDef);

    return body;
}

void render_rect(HDC hdc, float x, float y, float w, float h){

    int left = x - w;
    int top = y - h;
    int right = x + w;
    int bottom = y + h;
    Rectangle(hdc, left, top, right, bottom);
}

void board_physics_init(b2World* world, LPGAMEBOARD board){

    LPBPYSIC physc = &board->physc_border;

    //TOP
    int top_x = board->margin.left + (board->area.right-board->area.left)/2 + board->border_size;
    int top_y = board->margin.top;
    int top_width = (board->area.right - board->area.left)/2;
    int top_height = 2;

    physc->top = createBorder(world, top_x, top_y, top_width, top_height);

}

b2Body* createBorder(b2World* world, float x, float y, float w, float h){
    //ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x, y);
    groundBodyDef.type = b2BodyType::b2_staticBody;
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    //ground fixture
    b2PolygonShape groundShape;
    groundShape.SetAsBox(w, h);

    groundBody->CreateFixture(&groundShape, 0.0f);

    return groundBody;
}
//gravity
