#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include<vector>
#include "HeightMap.h"

class Model {
	char m_srcFile[64];
	int m_iID;
	GLuint m_iVBOID;
	GLuint m_iIBOID;
	int m_iNVertices;
	int m_iNIndices;

public:
	Model();
	Model(int id, char* srcFile);
	~Model();

	int getID() { return m_iID; }
	GLuint* getVBO() { return &m_iVBOID; }
	GLuint* getIBO() { return &m_iIBOID; }
	int getNVertices() { return m_iNVertices; }
	int getNIndices() { return m_iNIndices; }

	void loadModel(HeightMap* heightmap = NULL);
};
