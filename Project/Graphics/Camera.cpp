#include "../STDInclude.hpp"


glm::mat4 Graphics::Camera::m_projection;
glm::mat4 Graphics::Camera::m_cameraView;
glm::vec3 Graphics::Camera::m_cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Graphics::Camera::m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

float Graphics::Camera::m_aspectRatio = (float)800 / (float)600;
float Graphics::Camera::m_fov = 60.0f;
float Graphics::Camera::m_yaw = -90.0f;
float Graphics::Camera::m_pitch = 0.0f;
bool Graphics::Camera::m_limitPitch = true;

float Graphics::Camera::m_maxPitch = 90.0f;
float Graphics::Camera::m_minPitch = -90.0f;

const float Graphics::Camera::m_cameraDefaultSpeed = 2.5f;
float Graphics::Camera::m_cameraSpeed = m_cameraDefaultSpeed;

const float Graphics::Camera::m_cameraSensitivity = 0.1f;

const glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

void Graphics::Camera::Setup()
{
	m_cameraTarget = m_cameraPosition + GetFrontDirection();
	m_projection = glm::perspective(
		glm::radians(m_fov),
		m_aspectRatio,
		0.1f,
		100.0f);

	m_cameraView = glm::lookAt(
		m_cameraPosition, // Posizione della telecamera
		m_cameraTarget, // Punto verso cui guarda la telecamera
		m_up); // Vettore Up
}

void Graphics::Camera::SetAspectRatio(int _width, int _height)
{
	m_aspectRatio = (float)_width / (float)_height;
	Setup();
}

void Graphics::Camera::SetCameraSpeed(float _speed)
{
	m_cameraSpeed = _speed;
}

void Graphics::Camera::ResetCameraSpeed()
{
	m_cameraSpeed = m_cameraDefaultSpeed;
}

float Graphics::Camera::GetCameraDefaultSpeed()
{
	return m_cameraDefaultSpeed;
}

void Graphics::Camera::SetFov(float _fov)
{
	m_fov = _fov;
	Setup();
}

void Graphics::Camera::MoveForward(float _deltaTime)
{
	float _cameraSpeed = m_cameraSpeed * _deltaTime;  // Velocità della telecamera (velocità per frame)
	m_cameraPosition += GetFrontDirection() * _cameraSpeed;
	Setup();
}

void Graphics::Camera::MoveBackward(float _deltaTime)
{
	float _cameraSpeed = m_cameraSpeed * _deltaTime;  // Velocità della telecamera (velocità per frame)
	m_cameraPosition -= GetFrontDirection() * _cameraSpeed;
	Setup();
}

void Graphics::Camera::MoveLeft(float _deltaTime)
{
	float _cameraSpeed = m_cameraSpeed * _deltaTime;  // Velocità della telecamera (velocità per frame)
	m_cameraPosition -= GetRightDirection() * _cameraSpeed;
	Setup();
}

void Graphics::Camera::MoveRight(float _deltaTime)
{
	float _cameraSpeed = m_cameraSpeed * _deltaTime;  // Velocità della telecamera (velocità per frame)
	m_cameraPosition += GetRightDirection() * _cameraSpeed;
	Setup();
}

void Graphics::Camera::ProcessMouseOffset(float _x, float _y)
{
	_x *= m_cameraSensitivity;
	_y *= m_cameraSensitivity;

	m_yaw += _x; // Cambia l'orientamento sinistra-destra
	m_pitch += _y; // Cambia l'orientamento alto-basso

	// Limita il pitch per evitare problemi di "look up" o "look down"
	if (m_limitPitch)
	{
		if (m_pitch > m_maxPitch) m_pitch = m_maxPitch;
		if (m_pitch < m_minPitch) m_pitch = m_minPitch;
	}
	Setup();
}

glm::vec3 Graphics::Camera::GetFrontDirection()
{
	glm::vec3 _front;
	_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	_front.y = sin(glm::radians(m_pitch));
	_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	return glm::normalize(_front);
	/*return glm::normalize(m_cameraTarget - m_cameraPosition);*/
}

glm::vec3 Graphics::Camera::GetRightDirection()
{
	return glm::normalize(glm::cross(GetFrontDirection(), m_up));
}


float Graphics::Camera::GetFov()
{
	return m_fov;
}


glm::mat4* Graphics::Camera::GetProjection()
{
	return &m_projection;
}

glm::mat4* Graphics::Camera::GetCameraView()
{
	return &m_cameraView;
}
