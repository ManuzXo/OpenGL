#include <iostream>
#include <filesystem>
#include "GLEW/glew.h"
#include "ShaderResources.h"
#include "../Utils/FileSystem.h"
bool Resources::ShaderResources::Init()
{
	std::cout << "##### ShaderResources Init #####" << std::endl;

	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		std::string _fullPath;
		if (Utils::FileSystem::SubPathFinder("shaders", _fullPath))
		{
			for (const auto& _entry : fs::directory_iterator(_fullPath))
			{
				if (fs::is_regular_file(_entry))
				{
					WorkFile(_entry);
				}
			}
			return true;
		}
	}
	else
	{
		std::cerr << "Glew Init errore di iniziliazzione" << std::endl;
	}
	return false;
}

void Resources::ShaderResources::WorkFile(const std::filesystem::directory_entry& _file)
{
	std::string _fileData;
	auto _fullPath = _file.path();
	auto _extension = _fullPath.extension().string();

	unsigned int _shaderType = 0;
	if (_extension.compare(".vert"))
		_shaderType = GL_VERTEX_SHADER;
	else if (_extension.compare(".frag"))
		_shaderType = GL_FRAGMENT_SHADER;

	if (Utils::FileSystem::ReadFile(_fullPath.string(), _fileData))
	{
		CompileShader(_fileData.c_str(), _shaderType);
	}
}

void Resources::ShaderResources::CompileShader(const char* _data, GLenum _type)
{
	GLuint _shaderID = glCreateShader(_type);
	glShaderSource(_shaderID, 1, &_data, nullptr);
	glCompileShader(_shaderID);
	GLint _compileStatus;
	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &_compileStatus);
	if (!_compileStatus) {
		char _infoLog[512];
		glGetShaderInfoLog(_shaderID, 512, nullptr, _infoLog);
		std::cerr << "Errore nella compilazione dello shader: " << _infoLog << std::endl;
	}
}
