#include "../STDInclude.hpp"
void Components::SceneManager::Init()
{
	std::cout << "##### SceneManager Init #####" << std::endl;

	if (Graphics::Render::Init())
	{
		if (Resources::ShaderResources::Init() && Resources::GameObjectResources::Init())
		{
			Graphics::Render::MainLoop();
		}
	}
}

void Components::SceneManager::Destroy()
{
	std::cout << "##### SceneManager Destroy #####" << std::endl;
	Resources::ShaderResources::Destroy();
	Resources::GameObjectResources::Destroy();
	Graphics::Render::Destroy();
}

