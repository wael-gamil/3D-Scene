#pragma once
#include "libs.h"

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };
class Camera
{
private:
	mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	vec3 worldUp;
	vec3 position;
	vec3 front;
	vec3 right;
	vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;


	void updateCameraVectors();
public:
	Camera(vec3 position,vec3 direction, vec3 worldUp);
	//Accessors
	const mat4 getViewMatrix();

	const vec3 getPosition();
	void move(const float& dt, const int direction);
	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);
};

