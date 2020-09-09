#include "stdafx.h"
#include "TextManager.h"


GlyphTexture::GlyphTexture(int _textureID, FT_GlyphSlot _glyph) :
    textureID(_textureID)
{
    width = _glyph->bitmap.width;
    height = _glyph->bitmap.rows;
    left = _glyph->bitmap_left;
    top = _glyph->bitmap_top;
    advanceX = _glyph->advance.x;
    advanceY = _glyph->advance.y;
}

void TextManager::Init()
{
    Init("../Resources/Fonts/zorque.ttf");
}

void TextManager::Init(const char* ttfFile)
{
    if (FT_Init_FreeType(&m_ft))
    {
        printf("Could not init freetype library\n");
        return;
    }

    if (FT_New_Face(m_ft, ttfFile, 0, &m_face)) {
        printf("Could not open font %s\n", ttfFile);
        return;
    }

    FT_Set_Pixel_Sizes(m_face, 0, 48);
    m_glyphSlot = m_face->glyph;

    //disable the default 4-byte alignment restrictions that OpenGL uses for uploading textures and other data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // init Shader
    int vertexShader = esLoadShader(GL_VERTEX_SHADER, const_cast<char*>(TEXT_SHADER_VS_FILE));
    if (vertexShader == 0) return;

    int fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, const_cast<char*>(TEXT_SHADER_FS_FILE));
    if (fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        return;
    }

    m_iProgram = esLoadProgram(vertexShader, fragmentShader);
    m_iPositionAttribute = glGetAttribLocation(m_iProgram, "a_pos");
    m_iTextureUniform = glGetUniformLocation(m_iProgram, "u_texture");
    m_iColorUniform = glGetUniformLocation(m_iProgram, "u_color");


    // init Characters
    m_characters.clear();
    for (char c = 0; (unsigned char)c < (unsigned char)NUM_CHARACTER; ++c) {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
        {
            printf("Could not load char %c\n", c);
            continue;
        }

        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            m_glyphSlot->bitmap.width,
            m_glyphSlot->bitmap.rows,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            m_glyphSlot->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        m_characters.insert(std::pair<char, GlyphTexture>(c, GlyphTexture(textureID, m_glyphSlot)));
    }

    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);

}

void TextManager::Render(const char* text, Vector4 color, GLfloat x, GLfloat y, GLfloat scaleX, GLfloat scaleY)
{
    glUseProgram(m_iProgram);

    if (m_iColorUniform != -1) {
        glUniform4f(m_iColorUniform, color.x, color.y, color.z, color.w);
    }
    glUniform1i(m_iTextureUniform, 0);
    glActiveTexture(GL_TEXTURE0);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat sx = 1.0f / Globals::screenWidth * scaleX;
    GLfloat sy = 1.0f / Globals::screenHeight * scaleY;
    x = -1.0f + 2.0f * x / Globals::screenWidth;
    y = -1.0f + 2.0f * y / Globals::screenHeight;
    for (const char* p = text; *p; p++)
    {
        auto& c = m_characters[*p];

        GLfloat x2 = x + c.left * sx;
        GLfloat y2 = -y - c.top * sy;
        GLfloat w = c.width * sx;
        GLfloat h = c.height * sy;
        GLfloat box[4][4] = {
            {x2, -y2 , 0, 0},
            {x2 + w, -y2 , 1, 0},
            {x2, -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };

        glBindTexture(GL_TEXTURE_2D, c.textureID);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(m_iPositionAttribute);
        glVertexAttribPointer(m_iPositionAttribute, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        x += (c.advanceX >> 6) * sx;
        y += (c.advanceY >> 6) * sy;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
