#include "../../../STDInclude.hpp"

Resources::Entitys::Math::Transform::Transform()
{
	SetPosition(glm::vec3(0, 0, 0));
	SetRotation(glm::vec3(0, 0, 0));
}

Resources::Entitys::Math::Transform::~Transform()
{
}

void Resources::Entitys::Math::Transform::UpdateModelMatrix()
{
	m_modelMatrix = glm::translate(glm::mat4(1.0f), GetPosition());
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));  // Rotazione X
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotazione Y
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));  // Rotazione Z
}

const glm::mat4& Resources::Entitys::Math::Transform::GetModelMatrix()
{
	return m_modelMatrix;
}

glm::vec3& Resources::Entitys::Math::Transform::GetPosition()
{
	return m_position;
}

glm::vec3& Resources::Entitys::Math::Transform::GetRotation()
{
	return m_rotation;
}

void Resources::Entitys::Math::Transform::SetPosition(const glm::vec3& position)
{
	m_position = position;
	UpdateModelMatrix();
}

void Resources::Entitys::Math::Transform::SetRotation(const glm::vec3& rotation)
{
	m_rotation = rotation;
	UpdateModelMatrix();
}
