#pragma once
namespace Resources {

	class GameObjectResources {
	public:
		static bool Init();
		static void FileModelManager(const std::filesystem::directory_entry& _entry);
		static void CompileObjects();
		static void Destroy();
		static void ClearGameObjects();
		static std::vector<Entitys::GameObject*> m_gameObjects;
	};
}