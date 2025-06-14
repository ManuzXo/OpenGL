#pragma once
namespace Resources::Entitys {
	class GameObject {
	public:
		GameObject();
		GameObject(const std::string& _name);
		~GameObject();
		void SetName(const std::string& _name);
		const std::string& GetName();
		Math::Transform* GetTransform();
		GL::VertexBuffer* m_vertexData;
	private:
		Math::Transform m_transform;
		std::string m_Name;
	};
}