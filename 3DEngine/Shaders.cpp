#include "stdafx.h"
#include "Shaders.h"

Shaders::Shaders()
{
}

Shaders::Shaders(int id) :
	m_iID(id)
{
}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	m_iVertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( m_iVertexShader == 0 )
		return -1;

	m_iFragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( m_iFragmentShader == 0 )
	{
		glDeleteShader( m_iVertexShader );
		return -2;
	}

	m_iProgram = esLoadProgram(m_iVertexShader, m_iFragmentShader);

	//finding location of uniforms / attributes
	m_iPositionAttribute = glGetAttribLocation(m_iProgram, "a_posL");
	m_iTextureAttribute = glGetAttribLocation(m_iProgram, "a_uv");
	m_iTextureUniform = glGetUniformLocation(m_iProgram, "u_texture");
	m_iWVPmatrixUniform = glGetUniformLocation(m_iProgram, "u_WVP");
	m_iWVmatrixUniform = glGetUniformLocation(m_iProgram, "u_WV");
	m_iCubeUniform = glGetUniformLocation(m_iProgram, "u_samplerCubeMap");
	m_textureUniforms.resize(3, 0);
	m_textureUniforms[0] = glGetUniformLocation(m_iProgram, "u_texture0");
	m_textureUniforms[1] = glGetUniformLocation(m_iProgram, "u_texture1");
	m_textureUniforms[2] = glGetUniformLocation(m_iProgram, "u_texture2");
	m_iBlendMapUniform = glGetUniformLocation(m_iProgram, "u_blendmap");
	m_iFogColor = glGetUniformLocation(m_iProgram, "u_fogColor");
	m_iFogMaxDist = glGetUniformLocation(m_iProgram, "u_fogMaxDist");
	m_iFogMinDist = glGetUniformLocation(m_iProgram, "u_fogMinDist");
	m_iDispTextureUniform = glGetUniformLocation(m_iProgram, "u_dispTexture");
	m_iDispMax = glGetUniformLocation(m_iProgram, "u_dispMax");
	m_iMaskTextureUniform = glGetUniformLocation(m_iProgram, "u_maskTexture");
	m_iTimeUniform = glGetUniformLocation(m_iProgram, "u_time");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(m_iProgram);
	glDeleteShader(m_iVertexShader);
	glDeleteShader(m_iFragmentShader);
}