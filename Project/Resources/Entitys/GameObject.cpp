#include "../../STDInclude.hpp"

Resources::Entitys::GameObject::GameObject()
{
	m_modelMatrix = glm::mat4(1.0f);
	m_vertexData = new Entitys::GL::VertexBuffer();
}

Resources::Entitys::GameObject::GameObject(const std::string& _name)
{
	m_Name = _name;
	m_modelMatrix = glm::mat4(1.0f);
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

const glm::mat4& Resources::Entitys::GameObject::GetModelMatrix()
{
	return m_modelMatrix;
}

