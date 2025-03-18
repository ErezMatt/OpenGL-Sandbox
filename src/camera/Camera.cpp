#include "Camera.h"

Camera::Camera():
	worldUp{ glm::vec3(0.0f, 1.0f, 0.0f) }
{
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat nTurnSpeed):	
	worldUp{ up },
	position{ position },
	direction{ glm::vec3(0.0f, 0.0f,-1.0) },
	yaw{ yaw },
	pitch{ pitch },
	movmentSpeed{ moveSpeed },
	turnSpeed{ nTurnSpeed }
{
	update();
}

void Camera::keyControl(const Window& window, GLfloat dt)
{
	GLfloat velocity = movmentSpeed * dt;

	if (window.getKey(GLFW_KEY_W)) {
		position += direction * velocity;
	}
	if (window.getKey(GLFW_KEY_S)) {
		position -= direction * velocity;
	}
	if (window.getKey(GLFW_KEY_A)) {
		position -= right * velocity;
	}
	if (window.getKey(GLFW_KEY_D)) {
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + direction, up);
}

Camera::~Camera()
{
}

void Camera::update()
{
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

	right = glm::normalize(glm::cross(direction, worldUp));
	up = glm::normalize(glm::cross(right, direction));
}
