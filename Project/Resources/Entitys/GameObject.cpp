#include "../../STDInclude.hpp"

Resources::Entitys::GameObject::GameObject()
{
	SetPosition(glm::vec3(0, 0, 0));
	m_vertexData = new Entitys::GL::VertexBuffer();
}

Resources::Entitys::GameObject::GameObject(const std::string& _name)
{
	SetPosition(glm::vec3(0, 0, 0));
	m_Name = _name;
	m_vertexData = new Entitys::GL::VertexBuffer();
}

Resources::Entitys::GameObject::~GameObject()
{
	delete m_vertexData;
}

const std::string& Resources::Entitys::GameObject::GetName()
{
	return m_Name;
}

void Resources::Entitys::GameObject::UpdateModelMatrix()
{
	m_modelMatrix = glm::translate(glm::mat4(1.0f), GetPosition());
}

const glm::mat4& Resources::Entitys::GameObject::GetModelMatrix()
{
	return m_modelMatrix;
}

glm::vec3& Resources::Entitys::GameObject::GetPosition() 
{
	return m_position;
}

void Resources::Entitys::GameObject::SetPosition(const glm::vec3& position)
{
	m_position = position;
	UpdateModelMatrix();
}

