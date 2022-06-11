
#include "gameobjects.h"

#include <iostream>
using namespace std;

// copided from math.h
#define M_PI		3.14159265358979323846


vector2 rotate_rad(vector2* point, const vector2* origin, f32 rad)
{
    f32 x = point->x - origin->x;
    f32 y = point->y - origin->y;


    //f32 rads = math.radians(angle)
    f32 rads = rad;

    f32 cosvalue = cos(rads);
    f32 sinvalue = sin(rads);

    f32 xprime = x * cosvalue - y * sinvalue;
    f32 yprime = x * sinvalue + y * cosvalue;

    xprime += origin->x;
    yprime += origin->y;

    point->x = xprime;
    point->y = yprime;

    return vector2 {xprime, yprime};
}

vector2 rotate_deg(vector2* point, const vector2* origin, f32 angle)
{
    f32 rads = angle * ( M_PI / 180.0f );
    return rotate_rad(point, origin, rads);
}



void block_create(LPBLOCK* block, u32 x, u32 y, u32 w, u32 h){

    (*block) = (LPBLOCK)malloc(sizeof(BLOCK));

    (*block)->center = (vector2){x, y};
    (*block)->box_size = (bsize){w,h};
    (*block)->bg_color = BREAK_WHITE;
    (*block)->border_color = BREAK_BLACK;
}
void block_color(LPBLOCK block, u32 border_size, COLORREF border, COLORREF background){
    block->border_size = border_size;
    block->border_color = border;
    block->bg_color = background;
}
void block_create_body(LPBLOCK block, b2World* world){

    b2BodyDef bodydef;
    bodydef.position.Set(block->center.x/100.0f, block->center.y/100.0f);
    bodydef.type = b2BodyType::b2_dynamicBody;
    bodydef.angle = 0.0f;

    b2Body* body = world->CreateBody(&bodydef);

    b2PolygonShape shape;
    shape.SetAsBox(block->box_size.w/2.0f/100.0f, block->box_size.h/2.0f/100.0f);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    //fixtureDef.friction = 0.3f;


    body->CreateFixture(&fixtureDef);

    block->body = body;
}

void block_render(HDC hdc, LPBLOCK block){
    //COLOR HANDLE
    DWORD pen_style = PS_SOLID ;//| PS_JOIN_MITER | PS_GEOMETRIC;


    HPEN hPen = CreatePen(pen_style, block->border_size, block->border_color);
    HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

    HBRUSH hBrush1 = CreateSolidBrush(block->bg_color);
    HBRUSH holdBrush = (HBRUSH)SelectObject(hdc, hBrush1);


    //COORDS
    f32 x = block->body->GetPosition().x * 100.0f;
    f32 y = block->body->GetPosition().y * 100.0f;

    f32 left = x - block->box_size.w/2.0f;
    f32 top = y - block->box_size.h/2.0f;
    f32 right = x + block->box_size.w/2.0f;
    f32 bottom = y + block->box_size.h/2.0f;
    Rectangle(hdc, left, top, right, bottom);

    //RESTORE BRUSH
    SelectObject(hdc, holdPen);
    SelectObject(hdc, holdBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush1);
}


//PAD FUNCTIONS

void pad_create(LPPAD* block, u32 x, u32 y, u32 w, u32 h){
    (*block) = (LPPAD)malloc(sizeof(PAD));

    (*block)->start = (vector2){x, y};
    (*block)->box_size = (bsize){w,h};
    (*block)->bg_color = BREAK_WHITE;
    (*block)->border_color = BREAK_BLACK;
}
void pad_color(LPPAD block,u32 border_size, COLORREF border, COLORREF background){
    block->border_size = border_size;
    block->border_color = border;
    block->bg_color = background;
}
void pad_create_body(LPPAD block, b2World* world){
    b2BodyDef bodydef;
    bodydef.position.Set(block->start.x/100.0f, block->start.y/100.0f);
    bodydef.type = b2BodyType::b2_dynamicBody;
    bodydef.angle = 0.0f;

    b2Body* body = world->CreateBody(&bodydef);
    body->SetGravityScale(0);
    body->SetAngularDamping(0);

    b2PolygonShape shape;
    shape.SetAsBox(block->box_size.w/2.0f/100.0f, block->box_size.h/2.0f/100.0f);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    //fixtureDef.friction = 0.3f;


    body->CreateFixture(&fixtureDef);

    block->body = body;

}
void pad_move(LPPAD pad, int dx){
    b2Vec2 vel = pad->body->GetLinearVelocity();
    vel.x += dx;
    pad->body->SetLinearVelocity(vel);
}

void pad_render(HDC hdc, LPPAD pad){
    //COLOR HANDLE
    DWORD pen_style = PS_SOLID ;//| PS_JOIN_MITER | PS_GEOMETRIC;


    HPEN hPen = CreatePen(pen_style, pad->border_size, pad->border_color);
    HPEN holdPen = (HPEN)SelectObject(hdc, hPen);

    HBRUSH hBrush1 = CreateSolidBrush(pad->bg_color);
    HBRUSH holdBrush = (HBRUSH)SelectObject(hdc, hBrush1);

    //angle
    f32 angle = pad->body->GetAngle();
    //COORDS
    f32 x = pad->body->GetPosition().x * 100;
    f32 y = pad->body->GetPosition().y * 100;

    f32 left = x - pad->box_size.w/2.0f;
    f32 top = y - pad->box_size.h/2.0f;
    f32 right = x + pad->box_size.w/2.0f;
    f32 bottom = y + pad->box_size.h/2.0f;
    //Rectangle(hdc, left, top, right, bottom);

    vector2 p1 = {left, top};
    vector2 p2 = {right, top};
    vector2 p3 = {right, bottom};
    vector2 p4 = {left, bottom};

    b2Vec2 v = pad->body->GetPosition();
    vector2 org = {v.x, v.y};

    rotate_rad(&p1, &org, angle);
    rotate_rad(&p2, &org, angle);
    rotate_rad(&p3, &org, angle);
    rotate_rad(&p4, &org, angle);

    MoveToEx(hdc, p1.x, p1.y, NULL);
    LineTo(hdc, p2.x, p2.y);
    LineTo(hdc, p3.x, p3.y);
    LineTo(hdc, p4.x, p4.y);
    LineTo(hdc, p1.x, p1.y);

    //RESTORE BRUSH
    SelectObject(hdc, holdPen);
    SelectObject(hdc, holdBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush1);
}

