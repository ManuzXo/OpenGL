#include "../../STDInclude.hpp"

Resources::Models::OBJ::~OBJ()
{
	Clear();
}

bool Resources::Models::OBJ::Load(std::string _filePath, OBJ* _model)
{
	std::ifstream _fileStream(_filePath);
	if (!_fileStream.is_open()) {
		std::cerr << "Impossibile aprire il file " << _filePath << std::endl;
		return false;
	}

	std::string _line;
	while (std::getline(_fileStream, _line)) {
		std::istringstream _iss(_line);
		std::string _prefix;
		_iss >> _prefix;

		if (_prefix == "v") { // Vertici
			Utils::vec3_t _vertex;
			_iss >> _vertex.x >> _vertex.y >> _vertex.z;
			_model->m_vertices.push_back(_vertex);
		}
		else if (_prefix == "vt") { // Coordinate texture
			Utils::TextureCoord _texCoord;
			_iss >> _texCoord.u >> _texCoord.v;
			_model->m_textureCoords.push_back(_texCoord);
		}
		else if (_prefix == "vn") { // Normali
			Utils::Normal _normal;
			_iss >> _normal.x >> _normal.y >> _normal.z;
			_model->m_normals.push_back(_normal);
		}
		else if (_prefix == "f") { // Facce
			Utils::Face _face;
			std::string _vertexInfo;
			while (_iss >> _vertexInfo) {
				// Divide "v/vt/vn" in parti separate
				std::istringstream _vertexStream(_vertexInfo);
				std::string _v, _vt, _vn;
				std::getline(_vertexStream, _v, '/');
				std::getline(_vertexStream, _vt, '/');
				std::getline(_vertexStream, _vn, '/');

				_face.vertexIndices.push_back(std::stoi(_v) - 1); // Gli indici .obj partono da 1
				if (!_vt.empty()) _face.textureIndices.push_back(std::stoi(_vt) - 1);
				if (!_vn.empty()) _face.normalIndices.push_back(std::stoi(_vn) - 1);
			}
			_model->m_faces.push_back(_face);
		}
	}

	_fileStream.close();
	return true;
}

std::vector<Utils::vertexData_t> Resources::Models::OBJ::GetVertexData()
{
	std::vector<Utils::vertexData_t> _data;
	for (const auto& face : m_faces)
	{
		// Verifica che la faccia abbia almeno 3 vertici
		if (face.vertexIndices.size() >= 3) {
			// Triangola la faccia se è quadrata
			for (size_t i = 0; i < face.vertexIndices.size() - 2; ++i) {
				_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[0]],{1.0f,1.0f,1.0f,1.0f} });
				_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[i + 1]],{1.0f,1.0f,1.0f,1.0f} });
				_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[i + 2]],{1.0f,1.0f,1.0f,1.0f} });
			}
		}

		// Se la faccia è quadrata, dividila in due triangoli
		if (face.vertexIndices.size() == 4) {
			_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[0]],{1.0f,1.0f,1.0f,1.0f} });
			_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[1]],{1.0f,1.0f,1.0f,1.0f} });
			_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[2]],{1.0f,1.0f,1.0f,1.0f} });

			_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[0]],{1.0f,1.0f,1.0f,1.0f} });
			_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[2]],{1.0f,1.0f,1.0f,1.0f} });
			_data.push_back(Utils::vertexData_t{ m_vertices[face.vertexIndices[3]],{1.0f,1.0f,1.0f,1.0f} });
		}
	}
	return _data;
}



void Resources::Models::OBJ::Clear()
{
	m_vertices.clear();
	m_textureCoords.clear();
	m_normals.clear();
	m_faces.clear();
}
