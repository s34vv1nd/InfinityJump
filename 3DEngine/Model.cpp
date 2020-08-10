#include "stdafx.h"
#include "Model.h"

Model::Model()
{
}

Model::Model(int id, char* srcFile) :
	m_iID(id)
{
	strcpy(m_srcFile, srcFile);
}

Model::~Model()
{
	glDeleteBuffers(1, &m_iVBOID);
}

void Model::loadModel(HeightMap* heightmap)
{
	FILE *fi = fopen(m_srcFile, "r");
	if (!fi) {
		printf("FAILED TO OPEN NFG FILE\n");
		return;
	}
	
	int nVertices;
	fscanf(fi, "NrVertices: %d%*c", &nVertices);
	Vertex* verticesData = new Vertex[nVertices];
	for (int i = 0; i < nVertices; ++i) {
		fscanf(fi, "%*s pos:[%f, %f, %f]; ", &verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z);
		fscanf(fi, "norm:[%f, %f, %f]; ", &verticesData[i].normal.x, &verticesData[i].normal.y, &verticesData[i].normal.z);
		fscanf(fi, "binorm:[%f, %f, %f]; ", &verticesData[i].binormal.x, &verticesData[i].binormal.y, &verticesData[i].binormal.z);
		fscanf(fi, "tgt:[%f, %f, %f]; ", &verticesData[i].tangent.x, &verticesData[i].tangent.y, &verticesData[i].tangent.z);
		fscanf(fi, "uv:[%f, %f];%*c", &verticesData[i].uv.x, &verticesData[i].uv.y);
		if (heightmap) {
			verticesData[i].pos.y = heightmap->getValue(verticesData[i].uv.x, verticesData[i].uv.y);
			//printf("%f ", verticesData[i].pos.y);
		}
	}

	int nIndices;
	fscanf(fi, "NrIndices: %d%*c", &nIndices);
	GLuint *indicesData = new GLuint[nIndices];
	for (int i = 0; i < nIndices; i += 3) {
		fscanf(fi, "%*s %d, %d, %d%*c", &indicesData[i], &indicesData[i + 1], &indicesData[i + 2]);
	}

	Init(nVertices, verticesData, nIndices, indicesData);
}

void Model::Init(int nVertices, Vertex* verticesData, int nIndices, GLuint* indicesData)
{
	glGenBuffers(1, &m_iVBOID);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * nVertices, verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iIBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nIndices, indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_iNIndices = nIndices;
}
