#include "stdafx.h"
#include "HeightMap.h"


HeightMap::HeightMap()
{
	m_iY.clear();
	m_fScale = 25;
}

HeightMap::HeightMap(int id):
	HeightMap()
{
	m_iID = id;
}


HeightMap::~HeightMap()
{
}

void HeightMap::loadHeightMap(char * srcFile)
{
	char *data = LoadTGA(srcFile, &m_iRows, &m_iColumns, &m_iBPP);
	for (int i = 0; i < m_iRows; ++i) {
		m_iY.push_back(std::vector<GLfloat>());
		for (int j = 0; j < m_iColumns; ++j) {
			m_iY[i].push_back((float)data[(i * (m_iColumns)+j) * (m_iBPP / 8)]);
		}
	}
	smooth();
	delete[] data;
}

void HeightMap::smooth()
{
	auto temp = m_iY;
	for (int i = 0; i < m_iRows; ++i) {
		for (int j = 0; j < m_iColumns; ++j) {
			temp[i][j] = getAvg(i, j);
		}
	}
	m_iY = temp;
}

GLfloat HeightMap::getAvg(int x, int y)
{
	GLfloat sum = 0.0f, cnt = 0.0f;
	for (int i = x - 1; i <= x + 1; ++i) {
		for (int j = y - 1; j <= y + 1; ++j)
		if (i >= 0 && i < m_iRows && j >= 0 && j < m_iColumns) {
			sum += m_iY[i][j];
			cnt += 1.0f;
		}
	}
	return sum / cnt;
}

GLfloat HeightMap::getValue(GLfloat posx, GLfloat posz)
{
	int row = min(m_iRows - 1, max(0, (int) (posx * m_iRows)));
	int column = min(m_iColumns - 1, max(0, (int) (posz * m_iColumns)));
	return m_iY[row][column] / m_fScale;
}
