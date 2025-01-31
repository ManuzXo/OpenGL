#pragma once
namespace Resources::Entitys {
	class GameObject {
	public:
		GameObject();
		GameObject(const std::string & _name);
		~GameObject();
		const std::string& GetName();
		void UpdateModelMatrix();
		const glm::mat4& GetModelMatrix();
		glm::vec3& GetPosition() ;
		void SetPosition(const glm::vec3& position);
		GL::VertexBuffer *m_vertexData;
	private:
		std::string m_Name;
		glm::vec3 m_position;
		glm::mat4 m_modelMatrix;
	};
}