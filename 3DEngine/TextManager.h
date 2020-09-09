#pragma once
#include <map>
#include "../Utilities/utilities.h"
#include "Globals.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "Object.h"

#define TEXT_SHADER_VS_FILE "../Resources/Shaders/TextShaderVS.vs"
#define TEXT_SHADER_FS_FILE "../Resources/Shaders/TextShaderFS.fs"

#define NUM_CHARACTER 128

struct GlyphTexture {
	int textureID;
	int width, height;
	int left, top;
	int advanceX, advanceY;

	GlyphTexture() {}

	GlyphTexture(int _textureID, FT_GlyphSlot _glyph);
};

class TextManager
{
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;

	int m_iProgram = -1;
	int m_iPositionAttribute = -1;
	int m_iTextureUniform = -1;
	int m_iColorUniform = -1;

	map<char, GlyphTexture> m_characters;

public:
	void Init();
	void Init(const char* ttfFile);
	void Render(const char* text, Vector4 color, float x, float y, float scaleX, float scaleY);
};

