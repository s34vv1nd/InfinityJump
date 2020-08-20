#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

enum TILING_TYPE {
	REPEAT,
	CLAMP_TO_EDGE
};

enum TEXTURE_TYPE {
	TEXTURE_2D,
	TEXTURE_CUBE
};

class Texture
{
	int m_iID;
	GLuint m_iTextureID;
	GLint m_iWidth, m_iHeight, m_iBPP;
	TILING_TYPE m_tiling;
	TEXTURE_TYPE m_type;

public:
	Texture();
	Texture(int id, TILING_TYPE tiling = REPEAT, TEXTURE_TYPE type = TEXTURE_2D);
	~Texture();

	TEXTURE_TYPE getType() { return m_type; }
	int getID() { return m_iID; }
	GLuint* getTextureID() { return &m_iTextureID; }
	GLint getWidth() { return m_iWidth; }
	GLint getHeight() { return m_iHeight; }
	GLint getBPP() { return m_iBPP; }

	void loadTexture(const char* srcFile);
	void loadCubeTexture(std::vector<const char*> srcFiles);
	
};

