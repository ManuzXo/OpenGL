#pragma once
namespace Resources::Models {
	class OBJ : public BaseModel {
	public:
		OBJ();
		~OBJ();
		static bool Load(std::string _filePath, OBJ* _model);
		void Clear();

		std::vector<Utils::vertexData_t> GetVertexData();
	private:
		MTL *m_materialTemplateLibrary;
		std::vector<glm::vec3> m_vertices;
		std::vector<Utils::TextureCoord> m_textureCoords;
		std::vector<Utils::Normal> m_normals;
		std::vector<Utils::Face> m_faces;
	};
}