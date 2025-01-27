#pragma once
namespace Resources {
	class ShaderResources
	{
	public:
		static bool Init();
		static void Destroy();
		static GLuint GetProgram();
	private:
		static void FileShaderManager(const std::filesystem::directory_entry& _entry);
		static Entitys::GL::Shader* CompileShader(const char* _data, GLenum _type);
		static std::vector < Entitys::GL::Program*> m_programs;
		static std::vector<Entitys::GL::Shader*> m_shaders;
	};
}