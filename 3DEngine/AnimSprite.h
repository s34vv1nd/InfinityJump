#pragma once
#include "Animation.h"
#include "Sprite.h"
class AnimSprite :
    public Sprite
{
protected:
    vector<shared_ptr<Animation>> m_animations;
    int m_currentAnimation;
public:
    AnimSprite();
    virtual ~AnimSprite();

    virtual void setAnimations(vector<shared_ptr<Animation>> animations, int animationID = 0);
    virtual void pushAnimation(shared_ptr<Animation> animation);
    virtual void setCurrentAnimation(int animationID);

    virtual shared_ptr<Animation> getAnimationByID(int animationID);
    virtual int getCountAnimations();

    virtual std::vector<shared_ptr<Animation>>& getAnimations();
    virtual int getCurrentAnimation();

    virtual void Pause();
    virtual void Resume();

    virtual void Draw();
    virtual void Update(GLfloat dt);
};

