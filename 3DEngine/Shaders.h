#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
	int m_iID;
public:
	GLuint m_iProgram, m_iVertexShader, m_iFragmentShader;
	char m_sFileVS[260];
	char m_sFileFS[260];
	GLint m_iPositionAttribute;
	GLint m_iTextureAttribute;
	GLint m_iTextureUniform;
	GLint m_iWVPmatrixUniform;
	GLint m_iWVmatrixUniform;
	GLint m_iCubeUniform;
	std::vector<GLint> m_textureUniforms;
	GLint m_iBlendMapUniform;
	GLint m_iDispTextureUniform;
	GLint m_iDispMax;
	GLint m_iMaskTextureUniform;
	GLint m_iTimeUniform;
	GLint m_iFogColor;
	GLint m_iFogMaxDist;
	GLint m_iFogMinDist;
	
	Shaders();
	Shaders(int id);
	int getID() { return m_iID; }
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};