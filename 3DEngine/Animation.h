#pragma once
#include "Texture.h"

class Animation
{
    int m_iID;
    std::vector<Texture*> m_frames;
    int m_iCurrentFrame;
    GLfloat m_fSPF;
    GLfloat m_fTime;
public:
    Animation(int id, std::vector<Texture*> frames = vector<Texture*>(), int frameIndex = 0);
    virtual ~Animation();
    
    void setID(int id);
    void pushFrame(Texture* frame);
    void setSPF(GLfloat SPF);
    void setCurrentFrame(int frameIndex);

    int getID();
    int getCountFrames();
    Texture* getFrame(int index);
    int getCurrentFrame();
    GLfloat getSPF();
    GLfloat getTime();

    void Init(int frameIndex = 0);
    void Update(GLfloat dt);
};