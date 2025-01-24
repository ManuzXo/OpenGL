#pragma once
namespace Resources::Entitys {
	class GameObject {
	public:
		GameObject();
		~GameObject();
		void AddData(Utils::vertexData_t _data);
		void CopyData(std::vector<Utils::vertexData_t> _data);
		void CopyData(Utils::vertexData_t * _data, size_t _size);
		int GetVertexSize();
		GLuint GetVertexArray();
		GLuint GetVertexBuffer();
		bool BuildVertex();
	private:
		GLuint m_vertexArrayObject, m_vertexBufferObject;
		std::vector<Utils::vertexData_t> m_vertexData;
	};
}