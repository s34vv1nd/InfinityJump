#pragma once
#include "Animation.h"
#include "Sprite.h"
class AnimSprite :
    public Sprite
{
    vector<Animation*> m_animations;
    Animation* m_currentAnimation;
public:
    AnimSprite();
    virtual ~AnimSprite();

    virtual void setAnimations(vector<Animation*> animations, int animationID = 0);
    void pushAnimation(Animation* animation);
    void setCurrentAnimation(int animationID);

    Animation* getAnimation(int animationID);
    int getCountAnimations();

    virtual void Draw();
    virtual void Update(GLfloat dt);
};

