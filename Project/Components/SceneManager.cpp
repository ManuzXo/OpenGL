#include "../STDInclude.hpp"
void Components::SceneManager::Init()
{
	std::cout << "##### SceneManager Init #####" << std::endl;

	if (Graphics::Window::Init())
	{
		if (Resources::ShaderResources::Init() && Resources::GameObjectResources::Init())
		{
			if (Resources::Batching::m_useBatch)
				Resources::Batching::Init(Resources::GameObjectResources::m_gameObjects);
			else
				Resources::GameObjectResources::CompileObjects();

			Graphics::Window::MainLoop();
		}
	}
}

void Components::SceneManager::Destroy()
{
	std::cout << "##### SceneManager Destroy #####" << std::endl;
	Resources::ShaderResources::Destroy();
	Resources::GameObjectResources::Destroy();
	Graphics::Window::Destroy();
}

