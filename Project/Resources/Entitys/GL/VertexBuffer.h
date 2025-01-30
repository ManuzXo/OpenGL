#pragma once
namespace Resources::Entitys::GL {
	class VertexBuffer {
	public:
		struct data_t {
			glm::vec3 position;
			Utils::Color color;
		};
		struct HashFunction_t
		{
			size_t operator()(const std::pair<glm::vec3, Utils::Color>& pair) const;
		};
		VertexBuffer();
		~VertexBuffer();

		void AddData(data_t _data);

		void AddIndex(unsigned int _index);

		void CopyData(std::vector<data_t> _data);

		void CopyData(data_t* _data, size_t _size);
		
		void InsertData(std::vector<data_t> & _vector);

		data_t* GetVertexData();
		std::vector<data_t> & GetVertexRef();

		int GetVertexSize();
		int GetIndicesSize();
		unsigned int* GetIndeces();

		GLuint GetIndexBuffer();

		GLuint GetVertexArray();

		GLuint GetVertexBuffer();

		bool BuildVertex();

		void Bind();
		void UnBind();
	private:
		/// <summary>
		/// IBO
		/// </summary>
		GLuint m_indexBuffer;
		/// <summary>
		/// VAO
		/// </summary>
		GLuint m_vertexArrayObject;
		/// <summary>
		/// VBO
		/// </summary>
		GLuint m_vertexBufferObject;
		/// <summary>
		/// Index buffer
		/// </summary>
		std::vector<unsigned int> m_indices;
		/// <summary>
		/// Vettore che contiene dati
		/// </summary>
		std::vector<data_t> m_vertexData;
	};

}