#include "Camera.h"
#include "glm/glm.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glfw/include/GLFW/glfw3.h>

Camera::Camera()
{
	//Setting Camera Pos
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);


	//Setting Camera Dir (look at to scene center)
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);


	//Set Right Axis (represents positive X)
	//use cross product to get perpendicular of up
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	//Set Up Axis
	//use same method as right axis
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	//Look At
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
								glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.0f, 1.0f, 0.0f));

	//Rotation
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

Camera::~Camera()
{
}

void Camera::Update()
{
}