#pragma once
#include <filesystem>
#include "Entity/Shader.h"
namespace Resources {
	class ShaderResources
	{
	public:
		static bool Init();
		static void Destroy();
	private:
		static void FileShaderManager(const std::filesystem::directory_entry& _entry);
		static bool CreateShaderProgram();
		static bool IsProgramCreated();
		static bool LinkProgram();
		static Entitys::Shader* CompileShader(const char* _data, GLenum _type);
		static std::vector<Entitys::Shader*> m_shaders;
		static GLuint m_shaderProgram;

	};
}