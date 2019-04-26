
#include "GLCommon/OpenGLCamera.h"

using namespace OpenGLCamera;

FPCamera::FPCamera(glm::vec3 position,glm::vec3 worldUp,float yaw,float pitch)
{
	m_position = position;
	m_worldUp = worldUp;
	m_yaw = yaw;
	m_pitch = pitch;

	UpdateCameraVectors();
}


FPCamera::FPCamera(float posX, float posY, float posZ,
	float worldUpX, float worldUpY, float worldUpZ,
	float yaw, float pitch)
{
	m_position = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);
	m_yaw = yaw;
	m_pitch = pitch;

	UpdateCameraVectors();
}
FPCamera::~FPCamera()
{

}

glm::mat4 FPCamera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
	//return glm::lookAt(m_position, m_position + m_front, m_worldUp);
}

glm::mat4 FPCamera::GetProjMatrix(float ratio, float nearZ, float farZ)
{
	return glm::perspective(glm::radians(m_zoom), ratio, nearZ, farZ);
}

void FPCamera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = m_movementSpeed*deltaTime;

	switch (direction)
	{
	case OpenGLCamera::FORWARD:
		m_position += m_front*velocity;
		break;
	case OpenGLCamera::BACKWARD:
		m_position -= m_front*velocity;
		break;
	case OpenGLCamera::LEFT:
		m_position -= m_right*velocity;
		break;
	case OpenGLCamera::RIGHT:
		m_position += m_right*velocity;
		break;
	}
}

void FPCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void FPCamera::ProcessMouseScroll(float yoffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= yoffset;

	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;

	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
}


void FPCamera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw))*cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw))*cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}