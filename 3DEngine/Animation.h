#pragma once
#include <vector>
#include <memory>
#include "Texture.h"

class Animation
{
    int m_iID;
    std::vector<std::shared_ptr<Texture>> m_frames;
    int m_iCurrentFrame;
    GLfloat m_fSPF;
    GLfloat m_fTime;
    bool m_isStopped = false;
public:
    Animation(int id, std::vector<std::shared_ptr<Texture>> frames = std::vector<std::shared_ptr<Texture>>(), int frameIndex = 0);
    virtual ~Animation();
    
    void setID(int id);
    void pushFrame(std::shared_ptr<Texture> frame);
    void setSPF(GLfloat SPF);
    void setCurrentFrame(int frameIndex);
    void Pause();
    void Resume();

    int getID();
    int getCountFrames();
    std::shared_ptr<Texture> getFrame(int index);
    int getCurrentFrame();
    GLfloat getSPF();
    GLfloat getTime();

    void Init(int frameIndex = 0);
    void Update(GLfloat dt);
};