#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"
#include "define.h"


class Camera
{
	Vector3 m_position;
	Vector3 m_target;
	Vector3 m_up;
	GLfloat m_fSpeed;
	GLfloat m_fRotationSpeed;
	Matrix m_projectionMatrix;

public:
	Camera();
	Camera(GLfloat speed, GLfloat rotationSpeed, Matrix pMatrix);
	~Camera();

	Matrix getWorldMatrix();
	Matrix getViewMatrix();
	Matrix getProjectionMatrix();

	void moveForward(GLfloat dt);
	void moveBackward(GLfloat dt);
	void moveLeft(GLfloat dt);
	void moveRight(GLfloat dt);
	void rotateUp(GLfloat dt);
	void rotateDown(GLfloat dt);
	void rotateLeft(GLfloat dt);
	void rotateRight(GLfloat dt);

	void update(GLfloat dt, GLuint bitmask);
};

