#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	m_position = Vector3(Globals::screenWidth / 2, Globals::screenHeight / 2, 500);
	m_target = Vector3(Globals::screenWidth / 2, Globals::screenHeight / 2, 0);
	//m_position = Vector3(0, 0, 100);
	//m_target = Vector3(0, 0, 0);
	m_up = Vector3(0, 1, 0);
}

Camera::Camera(GLfloat nearPlane, GLfloat farPlane, GLfloat FOV, GLfloat speed, GLfloat rotationSpeed) :
	Camera()
{
	Matrix P;
#ifdef GAME_2D
	m_fSpeed = speed;
	m_fRotationSpeed = rotationSpeed / 180 * PI;
	m_projectionMatrix = P.SetOrthographic(nearPlane, farPlane, Globals::screenWidth / 2, Globals::screenHeight / 2);
	printf("near: %f , far: %f , right: %f , top: %f\n", nearPlane, farPlane, Globals::screenWidth / 2, Globals::screenHeight / 2);
#else
	m_fSpeed = speed;
	m_fRotationSpeed = rotationSpeed / 180 * PI;
	GLfloat _aspect = Globals::screenWidth * 1.0f / Globals::screenHeight;
	m_projectionMatrix = P.SetPerspective(FOV, _aspect, nearPlane, farPlane);
#endif
}

Camera::~Camera()
{
}

Matrix Camera::getWorldMatrix()
{
	Vector3 zaxis = (m_position - m_target).Normalize();
	Vector3 xaxis = (m_up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	Matrix W;
	W.m[0][0] = xaxis.x;	W.m[0][1] = xaxis.y;	W.m[0][2] = xaxis.z;	W.m[0][3] = 0;
	W.m[1][0] = yaxis.x;	W.m[1][1] = yaxis.y;	W.m[1][2] = yaxis.z;	W.m[1][3] = 0;
	W.m[2][0] = zaxis.x;	W.m[2][1] = zaxis.y;	W.m[2][2] = zaxis.z;	W.m[2][3] = 0;
	W.m[3][0] = m_position.x;
	W.m[3][1] = m_position.y;
	W.m[3][2] = m_position.z;
	W.m[3][3] = 1;
	return W;
}

Matrix Camera::getViewMatrix()
{
	Vector3 zaxis = (m_position - m_target).Normalize();
	Vector3 xaxis = (m_up.Cross(zaxis)).Normalize();
	Vector3 yaxis = zaxis.Cross(xaxis).Normalize();
	Matrix V;
	V.m[0][0] = xaxis.x;	V.m[0][1] = yaxis.x;	V.m[0][2] = zaxis.x;	V.m[0][3] = 0;
	V.m[1][0] = xaxis.y;	V.m[1][1] = yaxis.y;	V.m[1][2] = zaxis.y;	V.m[1][3] = 0;
	V.m[2][0] = xaxis.z;	V.m[2][1] = yaxis.z;	V.m[2][2] = zaxis.z;	V.m[2][3] = 0;
	V.m[3][0] = -m_position.Dot(xaxis);
	V.m[3][1] = -m_position.Dot(yaxis);
	V.m[3][2] = -m_position.Dot(zaxis);
	V.m[3][3] = 1;
	return V;
}

Matrix Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

void Camera::moveForward(GLfloat dt)
{
	Vector3 d = (m_target - m_position).Normalize() * dt * m_fSpeed;
	m_position += d;
	m_target += d;
}

void Camera::moveBackward(GLfloat dt)
{
	Vector3 d = (m_position - m_target).Normalize() * dt * m_fSpeed;
	m_position += d;
	m_target += d;
}

void Camera::moveLeft(GLfloat dt)
{
	Vector3 d = (m_position - m_target).Cross(m_up).Normalize() * dt * m_fSpeed;
	m_position += d;
	m_target += d;
}

void Camera::moveRight(GLfloat dt)
{
	Vector3 d = m_up.Cross(m_position - m_target).Normalize() * dt * m_fSpeed;
	m_position += d;
	m_target += d;
}

void Camera::moveUp(GLfloat dt)
{
	Vector3 d = m_up * dt * m_fSpeed;
	m_position += d;
	m_target += d;
}

void Camera::moveDown(GLfloat dt)
{
	Vector3 d = m_up * dt * m_fSpeed;
	m_position -= d;
	m_target -= d;
}

void Camera::rotateUp(GLfloat dt)
{
	Vector4 localTarget(0, 0, -(m_position - m_target).Length(), 1);
	Vector4 localNewTarget = localTarget * Matrix().SetRotationX(dt * m_fRotationSpeed);
	Vector4 worldNewTarget = localNewTarget * getWorldMatrix();
	Vector3 m_newTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	Vector3 zaxis = (m_position - m_newTarget).Normalize();
	if (m_up.Cross(zaxis).Length() > 0.1)
		m_target = m_newTarget;
}

void Camera::rotateDown(GLfloat dt)
{
	Vector4 localTarget(0, 0, -(m_position - m_target).Length(), 1);
	Vector4 localNewTarget = localTarget * Matrix().SetRotationX(-dt * m_fRotationSpeed);
	Vector4 worldNewTarget = localNewTarget * getWorldMatrix();
	Vector3 m_newTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	Vector3 zaxis = (m_position - m_newTarget).Normalize();
	if (m_up.Cross(zaxis).Length() > 0.1)
		m_target = m_newTarget;
}

void Camera::rotateLeft(GLfloat dt)
{
	Vector4 localTarget(0.0, 0.0, -(m_position - m_target).Length(), 1.0);
	Vector4 rotateAxis(0.0, 1.0, 0.0, 0.0);
	rotateAxis = rotateAxis * getViewMatrix();
	Vector4 localNewTarget = localTarget
		* Matrix().SetRotationAngleAxis(dt * m_fRotationSpeed, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	Vector4 worldNewTarget = localNewTarget * getWorldMatrix();
	m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::rotateRight(GLfloat dt)
{
	Vector4 localTarget(0, 0, -(m_position - m_target).Length(), 1);
	Vector4 rotateAxis(0.0, 1.0, 0.0, 0.0);
	rotateAxis = rotateAxis * getViewMatrix();
	Vector4 localNewTarget = localTarget
		* Matrix().SetRotationAngleAxis(-dt * m_fRotationSpeed, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	Vector4 worldNewTarget = localNewTarget * getWorldMatrix();
	m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::update(GLfloat dt, GLuint bitmask)
{
	if (bitmask & BIT_ROTATE_UP) rotateUp(dt);
	if (bitmask & BIT_ROTATE_DOWN) rotateDown(dt);
	if (bitmask & BIT_ROTATE_LEFT) rotateLeft(dt);
	if (bitmask & BIT_ROTATE_RIGHT) rotateRight(dt);

	if (bitmask & BIT_MOVE_FORWARD) moveForward(dt);
	if (bitmask & BIT_MOVE_BACKWARD) moveBackward(dt);
	if (bitmask & BIT_MOVE_UP) moveUp(dt);
	if (bitmask & BIT_MOVE_DOWN) moveDown(dt);
	if (bitmask & BIT_MOVE_LEFT) moveLeft(dt);
	if (bitmask & BIT_MOVE_RIGHT) moveRight(dt);
}
