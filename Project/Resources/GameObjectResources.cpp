#include "../STDInclude.hpp"

std::vector<Resources::Entitys::GameObject*> Resources::GameObjectResources::m_gameObjects;
static Utils::vertexData_t m_cube[] = {
	// Faccia frontale
	{{-0.5f, -0.5f, 0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{-0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{0.5f, 0.5f, 0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia posteriore
	{{-0.5f, -0.5f, -0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 2 (blu)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 3 (verde)

	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 3 (verde) (ripetuto)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 2 (blu) (ripetuto)
	{{0.5f, 0.5f, -0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia sinistra
	{{-0.5f, -0.5f, -0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{-0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{-0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{-0.5f, 0.5f, 0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia destra
	{{0.5f, -0.5f, 0.5f}, 1.0f, 0.0f, 0.0f},   // Vertice 1 (rosso)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},    // Vertice 3 (blu)

	{{0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},    // Vertice 3 (blu) (ripetuto)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{0.5f, 0.5f, -0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia superiore
	{{-0.5f, 0.5f, 0.5f}, 1.0f, 0.0f, 0.0f},   // Vertice 1 (rosso)
	{{0.5f, 0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},    // Vertice 2 (verde)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{0.5f, 0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},    // Vertice 2 (verde) (ripetuto)
	{{0.5f, 0.5f, -0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia inferiore
	{{-0.5f, -0.5f, -0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{-0.5f, -0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, -0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{0.5f, -0.5f, 0.5f}, 1.0f, 1.0f, 0.0f}    // Vertice 4 (giallo)
};
bool Resources::GameObjectResources::Init()
{
	std::cout << "##### GameObjectResources Init #####" << std::endl;
	std::string _fullPath;
	if (Utils::FileSystem::SubPathFinder("models", _fullPath))
	{
		for (const auto& _entry : fs::directory_iterator(_fullPath))
		{
			if (fs::is_regular_file(_entry))
			{
				FileModelManager(_entry);
			}
		}
		return true;
	}
	return false;
}

void Resources::GameObjectResources::FileModelManager(const std::filesystem::directory_entry& _entry)
{
	std::string _fileData;
	auto _fullPath = _entry.path();
	auto _extension = _fullPath.extension().string();
	if (!_extension.compare(".obj") && Utils::FileSystem::ReadFile(_fullPath.string(), _fileData))
	{
		std::cout << "Il file .obj è stato letto" << std::endl;
		auto _gObj = new Entitys::GameObject();
		_gObj->CopyData(m_cube, sizeof(m_cube) / sizeof(m_cube[0]));
		if (_gObj->BuildVertex())
		{
			std::cout << "Compilazione .obj fatta!" << std::endl;
			m_gameObjects.push_back(_gObj);
		}
		else
		{
			std::cerr << "Errore nella compilazione .obj" << std::endl;
		}
	}
}

void Resources::GameObjectResources::Destroy()
{
	std::cout << "##### GameObjectResources Destroy #####" << std::endl;

	for (auto _gobj : m_gameObjects)
	{
		delete _gobj;
	}
}
