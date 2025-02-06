#pragma once
#include "../Utilities/utilities.h"

class Camera {
public:
	Vector3
		position, target, up;
	GLfloat
		moveSpeed, rotateSpeed, nearPlane,
		farPlane, fov, deltaTime;
	Vector3
		xAxis, yAxis, zAxis;
	Matrix
		viewMatrix, worldMatrix, perspectiveMatrix;
	int Id;

	Camera();
	Camera(Vector3 position, Vector3 target, Vector3 up,
		GLfloat moveSpeed = 0.1f, GLfloat rotateSpeed = 0.1f, GLfloat nearPlane = 0.2f,
		GLfloat farPlane = 10.0f, GLfloat fov = 45.0f);

	void moveOx(int sens);
	void moveOy(int sens);
	void moveOz(int sens);
	void rotateOx(int sens);
	void rotateOy(int sens);
	void rotateOz(int sens);
	void updateAxes();
	void updateWorldView();
	void setDeltaTime(GLfloat deltaTime);
	void setId(int id);
	int getId();
};