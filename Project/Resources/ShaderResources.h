#include <filesystem>
#include <GLFW/glfw3.h>

namespace Resources {
	class ShaderResources
	{
	public:
		static bool Init();
	private:
		static void WorkFile(const std::filesystem::directory_entry& _entry);
		static void CompileShader(const char* _data, GLenum _type);
	};
}