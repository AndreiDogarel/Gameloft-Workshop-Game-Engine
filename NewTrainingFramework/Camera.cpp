#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"


Camera::Camera() {
	this->position = Vector3(0, 0, -1);
	this->target = Vector3(0, 0, 0);
	this->up = Vector3(0, 1, 0);
	this->moveSpeed = 20.0f;
	this->rotateSpeed = 2.0f;
	this->nearPlane = 0.2f;
	this->farPlane = 2000.0f;
	this->fov = 0.785398f;

	perspectiveMatrix.SetPerspective(this->fov, Globals::screenWidth / Globals::screenHeight, this->nearPlane, this->farPlane);
	updateWorldView();
}

Camera::Camera(Vector3 position, Vector3 target, Vector3 up,
	GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat nearPlane,
	GLfloat farPlane, GLfloat fov)
{
	this->position = position;
	this->target = target;
	this->up = up;
	this->moveSpeed = moveSpeed;
	this->rotateSpeed = rotateSpeed;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	this->fov = fov;

	perspectiveMatrix.SetPerspective(this->fov, Globals::screenWidth / Globals::screenHeight, this->nearPlane, this->farPlane);
	updateWorldView();
}

void Camera::moveOx(int sens) {
	Vector3
		forward, vectorDeplasare;

	forward = xAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;

	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::moveOy(int sens) {
	Vector3
		forward, vectorDeplasare;

	forward = yAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;

	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::moveOz(int sens) {
	Vector3
		forward, vectorDeplasare;

	forward = zAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;

	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::rotateOx(int sens) {
	Matrix
		mRotateOX;
	GLfloat
		angleRotation;
	Vector4
		localUp, rotatedLocalUp, localTarget, rotatedTarget;

	angleRotation = sens * rotateSpeed * deltaTime;
	mRotateOX.SetRotationX(angleRotation);

	localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	rotatedLocalUp = localUp * mRotateOX;
	up = Vector3(rotatedLocalUp * worldMatrix);
	up.Normalize();

	localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	rotatedTarget = localTarget * mRotateOX;
	target = Vector3(rotatedTarget * worldMatrix);

	updateWorldView();
}

void Camera::rotateOy(int sens) {
	Matrix
		mRotateOY;
	GLfloat
		angleRotation;
	Vector4
		localTarget, rotatedTarget;

	angleRotation = sens * rotateSpeed * deltaTime;
	mRotateOY.SetRotationY(angleRotation);

	localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	rotatedTarget = localTarget * mRotateOY;
	target = Vector3(rotatedTarget * worldMatrix);

	updateWorldView();
}

void Camera::rotateOz(int sens) {
	Matrix
		mRotateOZ;
	GLfloat
		angleRotation;
	Vector4
		localUp, rotatedLocalUp, localTarget, rotatedTarget;

	angleRotation = sens * rotateSpeed * deltaTime;
	mRotateOZ.SetRotationZ(angleRotation);

	localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	rotatedLocalUp = localUp * mRotateOZ;
	up = Vector3(rotatedLocalUp * worldMatrix);
	up.Normalize();

	updateWorldView();
}

void Camera::updateWorldView() {
	updateAxes();

	Matrix R;
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0.0f;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0.0f;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0.0f;
	R.m[3][0] = 0.0f;       R.m[3][1] = 0.0f;       R.m[3][2] = 0.0f;       R.m[3][3] = 1.0f;

	Matrix T;
	T.m[0][0] = 1.0f; T.m[0][1] = 0.0f; T.m[0][2] = 0.0f; T.m[0][3] = 0.0f;
	T.m[1][0] = 0.0f; T.m[1][1] = 1.0f; T.m[1][2] = 0.0f; T.m[1][3] = 0.0f;
	T.m[2][0] = 0.0f; T.m[2][1] = 0.0f; T.m[2][2] = 1.0f; T.m[2][3] = 0.0f;
	T.m[3][0] = position.x; T.m[3][1] = position.y; T.m[3][2] = position.z; T.m[3][3] = 1.0f;

	worldMatrix = R * T;

	Matrix T_inv;
	T_inv.m[0][0] = 1.0f; T_inv.m[0][1] = 0.0f; T_inv.m[0][2] = 0.0f; T_inv.m[0][3] = 0.0f;
	T_inv.m[1][0] = 0.0f; T_inv.m[1][1] = 1.0f; T_inv.m[1][2] = 0.0f; T_inv.m[1][3] = 0.0f;
	T_inv.m[2][0] = 0.0f; T_inv.m[2][1] = 0.0f; T_inv.m[2][2] = 1.0f; T_inv.m[2][3] = 0.0f;
	T_inv.m[3][0] = -position.x; T_inv.m[3][1] = -position.y; T_inv.m[3][2] = -position.z; T_inv.m[3][3] = 1.0f;

	Matrix R_t = R.Transpose();

	viewMatrix = T_inv * R_t;
}

void Camera::setDeltaTime(GLfloat deltaTime) {
	this->deltaTime = deltaTime;
}

void Camera::updateAxes() {
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}
