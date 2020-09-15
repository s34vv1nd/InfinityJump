#include "stdafx.h"
#include "Pad.h"


Pad::Pad(std::shared_ptr<b2World> world, shared_ptr<Sprite> obj, bool canKill, int level) :
	m_world(world),
	m_body(NULL),
	m_canKill(canKill),
	m_iLevel(level),
	m_passedCharacter(false),
	m_isInUse(false)
{
	m_model = obj->getModel();
	m_textures = obj->getTextures();
	m_shaders = obj->getShaders();
	m_position = obj->getPosition();
	m_position.x = PAD_DEFAULT_X_COORD;
	if (m_iLevel == 0) m_position.y = PAD_Y_COORD_LEVEL_0;
	if (m_iLevel == 1) m_position.y = PAD_Y_COORD_LEVEL_1;
	m_scale = obj->getScale();
	m_rotation = obj->getRotation();
	m_fWidth = obj->getWidth();
	m_fHeight = obj->getHeight();
	calculateWorldMatrix();
	calculateWVPmatrix();
	InitBody(getPos2D(), { 0.0f, 0.0f });
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

void Pad::setLevel(int level)
{
	m_iLevel = level;
}

int Pad::getLevel()
{
	return m_iLevel;
}

void Pad::setPos2D(Vector2 pos2D)
{
	Sprite::setPos2D(pos2D);
	m_body->SetTransform(CoordinateConverter::to_b2coord(dynamic_cast<Sprite*>(this)), 0);
}

bool Pad::isBehindCharacter(shared_ptr<Character> character)
{
	return getPos2D().x + getWidth() / 2.0f < character->getPos2D().x - character->getHitbox().x / 2.0f;
}

bool Pad::getPassedCharacter()
{
	return m_passedCharacter;
}

void Pad::setPassedCharacter(bool passed)
{
	m_passedCharacter = passed;
}

bool Pad::getInUse()
{
	return m_isInUse;
}

void Pad::setInUse(bool inUse)
{
	m_isInUse = inUse;
}

void Pad::InitBody(Vector2 pos2D, b2Vec2 velocity)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	b2Vec2 b2pos = CoordinateConverter::to_b2coord(dynamic_cast<Sprite*>(this));
	bodyDef.position.Set(b2pos.x, b2pos.y);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape kinematicBox;
	m_hitbox = { PAD_HITBOX_WIDTH, PAD_HITBOX_HEIGHT };
	kinematicBox.SetAsBox(getHitbox().x / 200.0f, getHitbox().y / 200.0f);
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
	Sprite::Update(dt);
	setPos2D(CoordinateConverter::to_glcoord(*m_body));
	//printf("Pad: x = %f , y = %f\n", m_position.x, m_position.y);
	//printf("dt = %f, Character velocity: x = %f , y = %f\n", dt, velocity.x, velocity.y);

	shared_ptr<GSPlay> currentPlayScene = static_pointer_cast<GSPlay>(Singleton<GameStateMachine>::GetInstance()->CurrentState());
	int currentPoint = currentPlayScene->getCharacter()->getPoint();
	auto v = m_body->GetLinearVelocity();
	v.x = max(-5.0, PAD_VELOCITY_X*(1.0f + (PAD_SPEED_INCREASE_RATE * currentPoint / NUM_PAD_PER_INCREASE_SPEED)));
	// printf("velocity: %f\n", v.x);
	if (abs(v.y) > EPSILON) {
		float y = getPos2D().y;
		if (y < PAD_Y_COORD_LEVEL_0) {
			v.y = PAD_VELOCITY_Y;
		}
		if (y > PAD_Y_COORD_LEVEL_2) {
			v.y = -PAD_VELOCITY_Y;
		}
	}
	m_body->SetLinearVelocity(v);
}