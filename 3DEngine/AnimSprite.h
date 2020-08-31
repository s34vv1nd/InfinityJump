#pragma once
#include "Animation.h"
#include "Sprite.h"
class AnimSprite :
    public Sprite
{
protected:
    vector<Animation*> m_animations;
    int m_currentAnimation;
public:
    AnimSprite();
    virtual ~AnimSprite();

    virtual void setAnimations(vector<Animation*> animations, int animationID = 0);
    virtual void pushAnimation(Animation* animation);
    virtual void setCurrentAnimation(int animationID);

    virtual Animation* getAnimationByID(int animationID);
    virtual int getCountAnimations();

    virtual std::vector<Animation*>& getAnimations();
    virtual int getCurrentAnimation();

    virtual void Pause();
    virtual void Resume();

    virtual void Draw();
    virtual void Update(GLfloat dt);
};

