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
	m_fWidth = obj->getWidth();
	m_fHeight = obj->getHeight();

	m_animations = obj->getAnimations();
	for (auto& anim : m_animations) {
		anim->setCurrentFrame(0);
	}
	m_currentAnimation = 0;

	calculateWorldMatrix();
	calculateWVPmatrix();
	InitBody();
}

Character::~Character()
{
	// m_world->DestroyBody(m_body);
}

inline GLfloat Character::getWidth() {
	return Sprite::getWidth();
	// return CHARACTER_HITBOX_WIDTH;
}

inline GLfloat Character::getHeight() {
	return Sprite::getHeight();
	// return CHARACTER_HITBOX_HEIGHT;
}

void Character::setPos2D(Vector2 pos2D)
{
	Sprite::setPos2D(pos2D);
	m_body->SetTransform(CoordinateConverter::to_b2coord(dynamic_cast<Sprite*>(this)), 0);
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
	if (pad != NULL && (m_previousPad == NULL || pad->getID() != m_previousPad->getID())) {
		Singleton<SoundManager>::GetInstance()->playSFX(LAND);
		//printf("new pad %d\n", pad->getID());
		m_previousPad = pad;
	}
	m_currentPad = pad;
	//if (pad) esLogMessage("On Pad: %d\n", pad->getID());
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
	FILE *fo = fopen(HIGHSCORE_FILE, "w");
	fprintf(fo, "%d", score);
	fclose(fo);
}

void Character::getCurrentHighScore()
{
	FILE *fi = fopen(HIGHSCORE_FILE, "r");
	if (!fi) {
		printf("FAILED TO OPEN FILE \"%s\"\n", HIGHSCORE_FILE);
		setHighScore(0);
		return;
	}
	fscanf(fi, "%d", &m_HighScore);
	fclose(fi);
}

void Character::InitBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 b2pos = CoordinateConverter::to_b2coord(dynamic_cast<Sprite*>(this));
	bodyDef.position.Set(b2pos.x, b2pos.y);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	m_hitbox = { CHARACTER_HITBOX_WIDTH, CHARACTER_HITBOX_HEIGHT };
	dynamicBox.SetAsBox(getHitbox().x / 200.0f, getHitbox().y / 200.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

void Character::Update(GLfloat dt)
{
	setPos2D({ CHARACTER_DEFAULT_X_COORD + getWidth(), CoordinateConverter::to_glcoord(*m_body).y});
	
	if (m_isDead) {
		//printf("Character: x = %f , y = %f\n", m_position.x, m_position.y);
		setCurrentAnimation(2);
		if (m_animations[m_currentAnimation]->getCurrentFrame() + 1 == m_animations[m_currentAnimation]->getCountFrames()) {
			Pause();
		}
	}

	if (m_needToJump) {
		m_needToJump = false;
	}
	else if ((m_isJumpingFirst || m_isJumpingSecond) && m_currentPad != NULL) {
		//printf("RESET JUMP\n");
		m_isJumpingFirst = false;
		m_isJumpingSecond = false;
		setCurrentAnimation(0);
	}
	setCurrentPad(NULL);
	AnimSprite::Update(dt);
}

void Character::JumpFirst()
{
	if (!m_isDead && !m_isJumpingFirst && !m_isJumpingSecond) {
		m_needToJump = true;
		m_isJumpingFirst = true;
		m_isJumpingSecond = false;
		//printf("JUMP FIRST\n");
		Singleton<SoundManager>::GetInstance()->playSFX(JUMP);
		setCurrentAnimation(1);
		m_body->SetLinearVelocity({ 0, 0 });
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0, m_body->GetMass() * IMPULSE_FIRSTJUMP), true);
	}
}

void Character::JumpSecond()
{
	if (!m_isDead && !m_isJumpingSecond && m_isJumpingFirst) {
		m_needToJump = true;
		m_isJumpingFirst = false;
		m_isJumpingSecond = true;
		//printf("JUMP SECOND\n");
		Singleton<SoundManager>::GetInstance()->playSFX(JUMP);
		setCurrentAnimation(1);
		m_body->SetLinearVelocity({ 0, 0 });
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0, m_body->GetMass() * IMPULSE_SECONDJUMP), true);
	}
}
