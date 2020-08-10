#pragma once
#include "../Utilities/utilities.h"

class HeightMap
{
	int m_iID = -1;
	GLint m_iRows = 0, m_iColumns = 0, m_iBPP = 0;
	std::vector<std::vector<GLfloat> > m_iY;
	GLfloat m_fScale;

	void smooth();
	GLfloat getAvg(int x, int y);

public:
	HeightMap();
	HeightMap(int id);
	~HeightMap();

	int getID() { return m_iID; }
	void loadHeightMap(char* srcFile);
	GLfloat getValue(GLfloat posx, GLfloat posz);
};

