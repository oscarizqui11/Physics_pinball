#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	// Pivot 0, 0
	/*b2Vec2 NES_Pinball_Table[67];
		NES_Pinball_Table[0].Set(54.0f, 448.0f);
		NES_Pinball_Table[1].Set(2.0f, 448.0f);
		NES_Pinball_Table[2].Set(2.0f, 0.0f);
		NES_Pinball_Table[3].Set(170.0f, 0.0f);
		NES_Pinball_Table[4].Set(170.0f, 448.0f);
		NES_Pinball_Table[5].Set(102.0f, 448.0f);
		NES_Pinball_Table[6].Set(149.0f, 401.0f);
		NES_Pinball_Table[7].Set(149.0f, 343.0f);
		NES_Pinball_Table[8].Set(135.0f, 328.0f);
		NES_Pinball_Table[9].Set(142.0f, 320.0f);
		NES_Pinball_Table[10].Set(142.0f, 256.0f);
		NES_Pinball_Table[11].Set(149.0f, 243.0f);
		NES_Pinball_Table[12].Set(149.0f, 236.0f);
		NES_Pinball_Table[13].Set(146.0f, 232.0f);
		NES_Pinball_Table[14].Set(134.0f, 232.0f);
		NES_Pinball_Table[15].Set(127.0f, 218.0f);
		NES_Pinball_Table[16].Set(126.0f, 192.0f);
		NES_Pinball_Table[17].Set(119.0f, 184.0f);
		NES_Pinball_Table[18].Set(118.0f, 176.0f);
		NES_Pinball_Table[19].Set(130.0f, 165.0f);
		NES_Pinball_Table[20].Set(138.0f, 172.0f);
		NES_Pinball_Table[21].Set(145.0f, 172.0f);
		NES_Pinball_Table[22].Set(149.0f, 168.0f);
		NES_Pinball_Table[23].Set(149.0f, 159.0f);
		NES_Pinball_Table[24].Set(134.0f, 144.0f);
		NES_Pinball_Table[25].Set(134.0f, 131.0f);
		NES_Pinball_Table[26].Set(139.0f, 129.0f);
		NES_Pinball_Table[27].Set(144.0f, 124.0f);
		NES_Pinball_Table[28].Set(147.0f, 116.0f);
		NES_Pinball_Table[29].Set(147.0f, 68.0f);
		NES_Pinball_Table[30].Set(142.0f, 56.0f);
		NES_Pinball_Table[31].Set(138.0f, 52.0f);
		NES_Pinball_Table[32].Set(130.0f, 49.0f);
		NES_Pinball_Table[33].Set(120.0f, 49.0f);
		NES_Pinball_Table[34].Set(114.0f, 52.0f);
		NES_Pinball_Table[35].Set(110.0f, 56.0f);
		NES_Pinball_Table[36].Set(102.0f, 56.0f);
		NES_Pinball_Table[37].Set(101.0f, 41.0f);
		NES_Pinball_Table[38].Set(117.0f, 25.0f);
		NES_Pinball_Table[39].Set(129.0f, 25.0f);
		NES_Pinball_Table[40].Set(140.0f, 30.0f);
		NES_Pinball_Table[41].Set(146.0f, 39.0f);
		NES_Pinball_Table[42].Set(152.0f, 55.0f);
		NES_Pinball_Table[43].Set(152.0f, 416.0f);
		NES_Pinball_Table[44].Set(166.0f, 416.0f);
		NES_Pinball_Table[45].Set(166.0f, 54.0f);
		NES_Pinball_Table[46].Set(163.0f, 40.0f);
		NES_Pinball_Table[47].Set(158.0f, 29.0f);
		NES_Pinball_Table[48].Set(154.0f, 23.0f);
		NES_Pinball_Table[49].Set(146.0f, 16.0f);
		NES_Pinball_Table[50].Set(131.0f, 9.0f);
		NES_Pinball_Table[51].Set(40.0f, 9.0f);
		NES_Pinball_Table[52].Set(25.0f, 17.0f);
		NES_Pinball_Table[53].Set(18.0f, 24.0f);
		NES_Pinball_Table[54].Set(14.0f, 30.0f);
		NES_Pinball_Table[55].Set(10.0f, 38.0f);
		NES_Pinball_Table[56].Set(7.0f, 48.0f);
		NES_Pinball_Table[57].Set(7.0f, 67.0f);
		NES_Pinball_Table[58].Set(21.0f, 110.0f);
		NES_Pinball_Table[59].Set(21.0f, 145.0f);
		NES_Pinball_Table[60].Set(6.0f, 160.0f);
		NES_Pinball_Table[61].Set(6.0f, 233.0f);
		NES_Pinball_Table[62].Set(14.0f, 255.0f);
		NES_Pinball_Table[63].Set(14.0f, 321.0f);
		NES_Pinball_Table[64].Set(22.0f, 328.0f);
		NES_Pinball_Table[65].Set(6.0f, 343.0f);
		NES_Pinball_Table[66].Set(6.0f, 401.0f);
		*/
	int NES_Pinball_Table[134]{
	54, 448,
	2, 448,
	2, 0,
	170, 0,
	170, 448,
	102, 448,
	149, 401,
	149, 343,
	135, 328,
	142, 320,
	142, 256,
	149, 243,
	149, 236,
	146, 232,
	134, 232,
	127, 218,
	126, 192,
	119, 184,
	118, 176,
	130, 165,
	138, 172,
	145, 172,
	149, 168,
	149, 159,
	134, 144,
	134, 131,
	139, 129,
	144, 124,
	147, 116,
	147, 68,
	142, 56,
	138, 52,
	130, 49,
	120, 49,
	114, 52,
	110, 56,
	102, 56,
	101, 41,
	117, 25,
	129, 25,
	140, 30,
	146, 39,
	152, 55,
	152, 416,
	166, 416,
	166, 54,
	163, 40,
	158, 29,
	154, 23,
	146, 16,
	131, 9,
	40, 9,
	25, 17,
	18, 24,
	14, 30,
	10, 38,
	7, 48,
	7, 67,
	21, 110,
	21, 145,
	6, 160,
	6, 233,
	14, 255,
	14, 321,
	22, 328,
	6, 343,
	6, 401,
	};

	for (int i = 0; i < 134; i++)
	{
		NES_Pinball_Table[i] *= 2;
	}

	pinball.add(CreateChain(0, 0, NES_Pinball_Table, 134));


	//b2ChainShape chain;
	
	//chain.CreateLoop(NES_Pinball_Table, 67);
	
	muelle.add(CreateRectangle(159 * 2, 805, 25, 10));
	
	b2Vec2 dockAxis(0.0f, 1.0f);
	dock.Initialize(dock.bodyA, dock.bodyB, dock.bodyA->GetWorldCenter(), dockAxis);

	/*
	b2Body* big_ball = world->CreateBody(&body);

	b2ChainShape shape;
	//shape.CreateChain(PIXEL_TO_METERS(NES_Pinball_Table), 134);
	//	m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	//big_ball->CreateFixture(&fixture);*/

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	//body.gravityScale = 0.0f;

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property


	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points

	// TODO 4: If the player releases the mouse button, destroy the joint

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}