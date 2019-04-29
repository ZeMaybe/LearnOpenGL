
#ifndef OpenGLCamera_h__
#define OpenGLCamera_h__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GLCommon
{
	enum CameraMovement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class FPCamera
	{
	public:
		FPCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW, float pitch = PITCH);
		FPCamera(float posX, float posY, float posZ, float worldUpX, float worldUpY, float worldUpZ,
			float yaw, float pitch);

		~FPCamera();

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjMatrix(float ratio,float nearZ,float farZ);

		void ProcessKeyboard(CameraMovement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);

	private:
		void UpdateCameraVectors();

	public:
		glm::vec3 m_position = glm::vec3(0.0f,0.0f,0.0f);
		glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);;
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;

		float m_yaw = YAW;
		float m_pitch = PITCH;

		float m_movementSpeed = SPEED;
		float m_mouseSensitivity = SENSITIVITY;
		float m_zoom = ZOOM; 
	};

};


#endif // OpenGLCamera_h__