#include "../STDInclude.hpp"

float Graphics::Camera::m_aspectRatio = (float)800 / (float)600;
float Graphics::Camera::m_fov = 60.0f;
glm::mat4 Graphics::Camera::m_projection;

void Graphics::Camera::Setup()
{
	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 100.0f);
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
