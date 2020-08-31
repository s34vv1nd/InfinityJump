#include "stdafx.h"
#include "Pad.h"


Pad::Pad(std::shared_ptr<b2World> world, shared_ptr<Sprite> obj, bool canKill, int level):
	m_world(world),
	m_body(NULL),
	m_canKill(canKill),
	m_iLevel(level)
{
	m_model = obj->getModel();
	m_textures = obj->getTextures();
	m_shaders = obj->getShaders();
	m_position = obj->getPosition();
	if (m_iLevel == 0) m_position.y = PAD_HEIGHT_LEVEL_0;
	if (m_iLevel == 1) m_position.y = PAD_HEIGHT_LEVEL_1;
	m_scale = obj->getScale();
	m_rotation = obj->getRotation();
	m_iWidth = obj->getWidth();
	m_iHeight = obj->getHeight();
	calculateWorldMatrix();
	calculateWVPmatrix();
	InitBody(getPos2D(), { PAD_VELOCITY, 0.0f });
}

Pad::~Pad()
{
	// m_world->DestroyBody(m_body);
}

b2Body* Pad::getBody() {
	return m_body;
}

bool Pad::isKiller()
{
	return m_canKill;
}

int Pad::getLevel()
{
	return m_iLevel;
}

void Pad::InitBody(Vector2 pos2D, b2Vec2 velocity)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set((pos2D.x + m_iWidth / 2.0) / 100.0, (pos2D.y + m_iHeight / 2.0) / 100.0);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape kinematicBox;
	kinematicBox.SetAsBox(m_iWidth / 200.0, 0.0);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &kinematicBox;
	fixtureDef.density = 0.0;
	fixtureDef.friction = 0.0;
	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData((void*) this);

	m_body->SetLinearVelocity(velocity);
}

void Pad::Update(GLfloat dt)
{
	b2Vec2 pos2D = m_body->GetPosition();
	setPos2D(pos2D.x * 100.0 - m_iWidth / 2.0, pos2D.y * 100.0 - m_iHeight / 2.0);
	//printf("Pad: x = %f , y = %f\n", m_position.x, m_position.y);
	//printf("dt = %f, Character velocity: x = %f , y = %f\n", dt, velocity.x, velocity.y);
	Sprite::Update(dt);
}
