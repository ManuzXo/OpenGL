#include "../STDInclude.hpp"

float Graphics::Camera::m_aspectRatio = (float)800 / (float)600;
float Graphics::Camera::m_fov = 60.0f;
glm::mat4 Graphics::Camera::m_projection;
glm::mat4 Graphics::Camera::m_cameraView;

void Graphics::Camera::Setup()
{
	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 100.0f);
	m_cameraView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), // Posizione della telecamera
		glm::vec3(0.0f, 0.0f, 0.0f), // Punto verso cui guarda la telecamera
		glm::vec3(0.0f, 1.0f, 0.0f)); // Vettore Up
}

void Graphics::Camera::SetAspectRatio(int _width, int _height)
{
	m_aspectRatio = (float)_width / (float)_height;
	Setup();
}

void Graphics::Camera::SetFov(float _fov)
{
	m_fov = _fov;
	Setup();
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
