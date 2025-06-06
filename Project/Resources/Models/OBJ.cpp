#include "../../STDInclude.hpp"
Resources::Models::OBJ::OBJ() {

}
Resources::Models::OBJ::~OBJ()
{
	Clear();
}

bool Resources::Models::OBJ::Load(std::string _filePath, OBJ* _model, std::vector<Entitys::GameObject*>* _gameObjects)
{
	std::ifstream _fileStream(_filePath);
	if (!_fileStream.is_open()) {
		std::cerr << "Impossibile aprire il file " << _filePath << std::endl;
		return false;
	}

	std::string _line, _materialName;

	Entitys::GameObject* _currentGameObject = new Entitys::GameObject();
	_gameObjects->push_back(_currentGameObject);

	while (std::getline(_fileStream, _line)) {
		std::istringstream _iss(_line);
		std::string _prefix;
		_iss >> _prefix;
		if (_prefix == "mtllib") //creazione MTL
		{
			std::string _mtlName;
			_iss >> _mtlName;
			std::filesystem::path _objPath(_filePath);
			std::filesystem::path _mtlPath = _objPath.parent_path() / _mtlName;
			_model->m_materialTemplateLibrary = new MTL();
			if (_model->m_materialTemplateLibrary->Load(_mtlPath.string())) {
				std::cout << "Caricamento materiali fatto!" << std::endl;
			}
			else
			{
				std::cerr << "Errore nel caricare i materiali" << std::endl;
			}
		}
		else if (_prefix == "usemtl") //material da usare
		{
			_iss >> _materialName;
		}

		else if (_prefix == "o") //Nome Oggetto
		{
			std::string _nameObject;
			_iss >> _nameObject;
			_currentGameObject->SetName(_nameObject);

			//NEW Entity
			_currentGameObject = new Entitys::GameObject();
			_gameObjects->push_back(_currentGameObject);
		}
		else if (_prefix == "v") { // Vertici
			glm::vec3 _vertex;
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

				if (!_vt.empty())
					_face.textureIndices.push_back(std::stoi(_vt) - 1);
				if (!_vn.empty())
					_face.normalIndices.push_back(std::stoi(_vn) - 1);
			}

			if (!_materialName.empty()) {
				_face.materialName = _materialName;
			}
			if (_currentGameObject != NULL) {
				_face.refGameObject = _currentGameObject;
			}

			_model->m_faces.push_back(_face);
		}

	}
	_fileStream.close();
	return true;
}

//void Resources::Models::OBJ::AssignVertexDataGameObjects()
//{
//	auto _map = m_materialTemplateLibrary->GetMaterialsColor();
//	for (const auto& _face : m_faces)
//	{
//		auto _gameObject = (Entitys::GameObject*)_face.refGameObject;
//		auto _vertexRef = _gameObject->m_vertexData;
//
//		Utils::Color _color(1.0f, 1.0f, 1.0f, 1.0f);
//		if (!_face.materialName.empty())
//		{
//			_color.SetRGBA(_map.at(_face.materialName));
//		}
//		
//		if (_face.vertexIndices.size() >= 3) {
//			// Triangola la faccia se è quadrata
//			for (size_t i = 0; i < _face.vertexIndices.size() - 2; ++i) {
//				_vertexRef->AddData({ m_vertices[_face.vertexIndices[0]], _color });
//				_vertexRef->AddData({ m_vertices[_face.vertexIndices[i + 1]],_color });
//				_vertexRef->AddData({ m_vertices[_face.vertexIndices[i + 2]],_color });
//			}
//		}
//
//		// Se la faccia è quadrata, dividila in due triangoli
//		if (_face.vertexIndices.size() == 4) {
//			_vertexRef->AddData({ m_vertices[_face.vertexIndices[0]],_color });
//			_vertexRef->AddData({ m_vertices[_face.vertexIndices[1]],_color });
//			_vertexRef->AddData({ m_vertices[_face.vertexIndices[2]],_color });
//
//			_vertexRef->AddData({ m_vertices[_face.vertexIndices[0]],_color });
//			_vertexRef->AddData({ m_vertices[_face.vertexIndices[2]],_color });
//			_vertexRef->AddData({ m_vertices[_face.vertexIndices[3]],_color });
//		}
//	}
//}
void Resources::Models::OBJ::AssignVertexDataGameObjects()
{
	std::map<std::string, Utils::Color> _map;
	if (m_materialTemplateLibrary != NULL)
		_map = m_materialTemplateLibrary->GetMaterialsColor();

	for (const auto& _face : m_faces)
	{
		auto _gameObject = _face.refGameObject;
		auto _vertexRef = _gameObject->m_vertexData;

		Utils::Color _color(1.0f, 1.0f, 1.0f, 1.0f);
		if (!_face.materialName.empty() && _map.size() > 0)
		{
			_color.SetRGBA(_map.at(_face.materialName));
		}

		// Mappa per evitare vertici duplicati e ottenere gli indici corretti
		std::unordered_map<std::pair<glm::vec3, Utils::Color>, uint32_t, Entitys::GL::VertexBuffer::HashFunction_t> _vertexCache;
		std::vector<uint32_t> _indices;

		// Creazione degli indici senza duplicati
		for (auto vertexIndex : _face.vertexIndices)
		{
			Entitys::GL::VertexBuffer::data_t vertex = { m_vertices[vertexIndex], _color };

			auto key = std::make_pair(vertex.position, vertex.color);
			if (_vertexCache.find(key) == _vertexCache.end())
			{
				uint32_t _newIndex = static_cast<uint32_t>(_vertexRef->GetVertexSize()); // Usa la dimensione attuale come indice
				_vertexCache[key] = _newIndex;
				_vertexRef->AddData(vertex);
			}
			_indices.push_back(_vertexCache[key]);
		}

		// Se la faccia ha 3 vertici ? è già un triangolo
		if (_indices.size() == 3)
		{
			_vertexRef->AddIndex(_indices[0]);
			_vertexRef->AddIndex(_indices[1]);
			_vertexRef->AddIndex(_indices[2]);
		}
		// Se la faccia ha 4 vertici ? dividiamo in due triangoli
		else if (_indices.size() == 4)
		{
			_vertexRef->AddIndex(_indices[0]);
			_vertexRef->AddIndex(_indices[1]);
			_vertexRef->AddIndex(_indices[2]);

			_vertexRef->AddIndex(_indices[0]);
			_vertexRef->AddIndex(_indices[2]);
			_vertexRef->AddIndex(_indices[3]);
		}
		else
		{
			std::cerr << "Errore: faccia con un numero di vertici non supportato (" << _indices.size() << ")" << std::endl;
		}
	}
}



void Resources::Models::OBJ::Clear()
{
	m_vertices.clear();
	m_textureCoords.clear();
	m_normals.clear();
	m_faces.clear();
	delete m_materialTemplateLibrary;
}
