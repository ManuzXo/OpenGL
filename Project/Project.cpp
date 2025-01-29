#include "STDInclude.hpp"
int main()
{
	try {
		Components::SceneManager::Init();
	}
	catch (std::exception ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	Components::SceneManager::Destroy();
}
