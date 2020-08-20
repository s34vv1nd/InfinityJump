#include "stdafx.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture()
{
}

Texture::Texture(int id, TILING_TYPE tiling, TEXTURE_TYPE type) :
	m_iID(id), m_tiling(tiling), m_type(type)
{
}


Texture::~Texture()
{
	glDeleteBuffers(1, &m_iTextureID);
}

void Texture::loadTexture(const char * srcFile) {
	glGenTextures(1, &m_iTextureID);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);

	if (strcmp(srcFile + strlen(srcFile) - 4, ".tga") == 0) {
		char* imageData = LoadTGA(srcFile, &m_iWidth, &m_iHeight, &m_iBPP);
		if (m_iBPP == 24) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		}
		if (m_iBPP == 32) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iWidth, m_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		}
		delete imageData;
	}
	else {
		int channels;
		unsigned char* imageData = stbi_load(srcFile, &m_iWidth, &m_iHeight, &channels, 0);
		if (channels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iWidth, m_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		}
		stbi_image_free(imageData);
	}

	if (m_tiling == REPEAT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	if (m_tiling == CLAMP_TO_EDGE)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadCubeTexture(std::vector<const char*> srcFiles)
{
	glGenTextures(1, &m_iTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_iTextureID);
	char** cubePixels = new char*[6];
	for (int i = 0; i<6; i++) {
		int width, height, bpp;
		cubePixels[i] = LoadTGA(srcFiles[i], &width, &height, &bpp);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			(bpp == 24) ? GL_RGB : GL_RGBA,
			width,
			height,
			0,
			(bpp == 24) ? GL_RGB : GL_RGBA,
			GL_UNSIGNED_BYTE,
			cubePixels[i]);
	}
	delete[] cubePixels;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
