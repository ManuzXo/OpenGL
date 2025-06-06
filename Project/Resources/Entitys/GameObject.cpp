#include "../../STDInclude.hpp"

Resources::Entitys::GameObject::GameObject()
{
	SetName("unkown");
	m_vertexData = new Entitys::GL::VertexBuffer();
	m_transform = Math::Transform();
}

Resources::Entitys::GameObject::GameObject(const std::string& _name)
{
	SetName(_name);
	m_vertexData = new Entitys::GL::VertexBuffer();
	m_transform = Math::Transform();
}

Resources::Entitys::GameObject::~GameObject()
{
	delete m_vertexData;
}

void Resources::Entitys::GameObject::SetName(const std::string& _name)
{
	m_Name = _name;
}

const std::string& Resources::Entitys::GameObject::GetName()
{
	return m_Name;
}

Resources::Entitys::Math::Transform* Resources::Entitys::GameObject::GetTransform()
{
	return &m_transform;
}

