#include "stdafx.h"
#include "Character.h"
//
//Character::Character():
//	AnimSprite()
//{
//}

Character::Character(shared_ptr<b2World> world, std::shared_ptr<AnimSprite> obj)/*:
	Character()*/
{
	m_world = world;
	m_model = obj->getModel();
	m_textures = obj->getTextures();
	m_shaders = obj->getShaders();
	m_position = obj->getPosition();
	m_scale = obj->getScale();
	m_rotation = obj->getRotation();
	m_iWidth = obj->getWidth();
	m_iHeight = obj->getHeight();
	m_animations = obj->getAnimations();
	m_currentAnimation = obj->getCurrentAnimation();
	calculateWorldMatrix();
	calculateWVPmatrix();
	InitBody();
}

Character::~Character()
{
	// m_world->DestroyBody(m_body);
}

b2Body* Character::getBody()
{
	return m_body;
}

Pad* Character::getCurrentPad()
{
	return m_currentPad;
}

void Character::setCurrentPad(Pad* pad)
{
	m_currentPad = pad;
	if (pad && pad->isKiller()) die();
}

bool Character::isOnTheGround()
{
	return m_isOnTheGround;
}

void Character::setIsOnTheGround(bool isOnTheGround)
{
	m_isOnTheGround = isOnTheGround;
	die();
}

bool Character::isJumpingFirst()
{
	return m_isJumpingFirst;
}

bool Character::isJumpingSecond()
{
	return m_isJumpingSecond;
}

bool Character::isDead()
{
	return m_isDead;
}

void Character::die()
{
	m_isDead = true;
}

int Character::getPoint()
{
	return m_iPoint;
}

void Character::setPoint(int point)
{
	m_iPoint = point;
}

int Character::getHighScore()
{
	return m_HighScore;
}

void Character::setHighScore(int score)
{
	FILE *fi = fopen(HIGHSCORE_FILE, "w");
	fprintf(fi, "%d", score);
	fclose(fi);
}

void Character::getCurrentHighScore()
{
	FILE *fi = fopen(HIGHSCORE_FILE, "r");
	if (!fi) {
		printf("FAILED TO OPEN FILE \"%s\"\n", HIGHSCORE_FILE);
	}
	fscanf(fi, "%d", &m_HighScore);
	fclose(fi);
}

void Character::InitBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((m_position.x + CHARACTER_HITBOX_WIDTH / 2.0f) / 100.0f, (m_position.y + CHARACTER_HITBOX_HEIGHT / 2.0f) / 100.0f);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(CHARACTER_HITBOX_WIDTH / 200.0f, CHARACTER_HITBOX_HEIGHT / 200.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

void Character::Update(GLfloat dt)
{
	b2Vec2 pos2D = m_body->GetPosition();
	pos2D = { (m_position.x + CHARACTER_HITBOX_WIDTH / 2.0f) / 100.0f, pos2D.y };
	m_body->SetTransform(pos2D, 0);
	setPos2D(pos2D.x * 100.0 - CHARACTER_HITBOX_WIDTH / 2.0, pos2D.y * 100.0 - CHARACTER_HITBOX_HEIGHT / 2.0);
	//printf("Character: x = %f , y = %f\n", m_position.x, m_position.y);

	if (m_isDead) {
		setCurrentAnimation(2);
		if (m_animations[m_currentAnimation]->getCurrentFrame() + 1 == m_animations[m_currentAnimation]->getCountFrames()) {
			Pause();
		}
	}

	if ((m_isJumpingFirst || m_isJumpingSecond) && m_currentPad != NULL) {
		m_isJumpingFirst = false;
		m_isJumpingSecond = false;
		setCurrentAnimation(0);
	}

	AnimSprite::Update(dt);
}

void Character::JumpFirst()
{
	if (!m_isDead && !m_isJumpingFirst && !m_isJumpingSecond) {
		m_isJumpingFirst = true;
		setCurrentAnimation(1);
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0, m_body->GetMass() * IMPULSE_FIRSTJUMP), true);
	}
}

void Character::JumpSecond()
{
	if (!m_isDead && !m_isJumpingSecond && m_isJumpingFirst) {
		m_isJumpingFirst = false;
		m_isJumpingSecond = true;
		setCurrentAnimation(1);
		m_body->SetLinearVelocity({ 0, 0 });
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0, m_body->GetMass() * IMPULSE_SECONDJUMP), true);
	}
}
