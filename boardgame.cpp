#include "boardgame.h"

void boardgame_init(LPBOARDGAME* board, vector2 min, vector2 max, b2World* world )
{
			b2BodyDef bd;
			b2Body* ground = world->CreateBody(&bd);

            //added
            bd.type = b2BodyType::b2_staticBody;


			b2EdgeShape shape;



			f32 x1 = min.x/100.0f;
			f32 y1 = min.y/100.0f;
			f32 x2 = max.x/100.0f;
			f32 y2 = max.y/100.0f;

			// Roof
			shape.SetTwoSided(b2Vec2(x1, y1), b2Vec2(x2, y1));
			ground->CreateFixture(&shape, 0.0f);

			// Right wall
			shape.SetTwoSided(b2Vec2(x2, y1), b2Vec2(x2, y2));
			ground->CreateFixture(&shape, 0.0f);

			// Floor
			shape.SetTwoSided(b2Vec2(x2, y2), b2Vec2(x1, y2));
			ground->CreateFixture(&shape, 0.0f);

			// Left wall
			shape.SetTwoSided(b2Vec2(x1, y2), b2Vec2(x1, y1));
			ground->CreateFixture(&shape, 0.0f);

            (*board) = (LPBOARDGAME) malloc(sizeof(BOARDGAME));
            (*board)->min = min;
            (*board)->max = max;
            (*board)->body = ground;
            (*board)->theme = {1, 0xffffff, 0x00};
}
