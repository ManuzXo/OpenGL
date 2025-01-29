#pragma once
namespace Resources::Entitys {
	class GameObject {
	public:
		GameObject();
		GameObject(const std::string & _name);
		~GameObject();
		const std::string& GetName();
		const glm::mat4& GetModelMatrix();
		GL::VertexBuffer *m_vertexData;
	private:
		std::string m_Name;
		glm::mat4 m_modelMatrix;
	};
}