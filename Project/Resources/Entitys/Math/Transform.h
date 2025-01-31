#pragma once
namespace Resources::Entitys::Math {
	class Transform {
	public:
		Transform();
		~Transform();
		void UpdateModelMatrix();
		const glm::mat4& GetModelMatrix();
		glm::vec3& GetPosition();
		glm::vec3& GetRotation();
		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::mat4 m_modelMatrix;
	};
}