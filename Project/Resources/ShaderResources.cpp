#include "../STDInclude.hpp"

std::vector<Resources::Entitys::Shader*> Resources::ShaderResources::m_shaders;
GLuint Resources::ShaderResources::m_program;
bool Resources::ShaderResources::Init()
{
	std::cout << "##### ShaderResources Init #####" << std::endl;

	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::string _fullPath;
		if (Utils::FileSystem::SubPathFinder("shaders", _fullPath))
		{
			if (CreateProgram())
			{
				for (const auto& _entry : fs::directory_iterator(_fullPath))
				{
					if (fs::is_regular_file(_entry))
					{
						FileShaderManager(_entry);
					}
				}
			}
			return LinkProgram();
		}
	}
	else
	{
		std::cerr << "Glew Init errore di iniziliazzione" << std::endl;
	}
	return false;
}

void Resources::ShaderResources::Destroy()
{
	std::cout << "##### ShaderResources Destroy #####" << std::endl;

	//DELETE SHADER AS FRAG & VERT
	for (auto _shader : m_shaders)
	{
		if (_shader->IsCompiled())
		{
			auto _id = _shader->GetShaderID();
			if (IsProgramCreated())
				glDetachShader(m_program, _id);

			glDeleteShader(_shader->GetShaderID());
		}
		delete _shader;
	}
	m_shaders.clear();

	//DELETE PROGRAM SHADER
	if (IsProgramCreated())
	{
		glDeleteProgram(m_program);
	}
}

GLuint Resources::ShaderResources::GetProgram()
{
	return m_program;
}

void Resources::ShaderResources::FileShaderManager(const std::filesystem::directory_entry& _file)
{
	std::string _fileData;
	auto _fullPath = _file.path();
	auto _extension = _fullPath.extension().string();

	unsigned int _shaderType = 0;
	if (_extension.compare(".vert") == 0)
		_shaderType = GL_VERTEX_SHADER;
	else if (_extension.compare(".frag") == 0)
		_shaderType = GL_FRAGMENT_SHADER;

	if (Utils::FileSystem::ReadFile(_fullPath.string(), _fileData))
	{
		auto _shaderEntity = CompileShader(_fileData.c_str(), _shaderType);
		if (_shaderEntity->IsCompiled())
		{
			//ATTACH THE SHADER TO THE PROGRAM
			glAttachShader(m_program, _shaderEntity->GetShaderID());
		}
	}
}

bool Resources::ShaderResources::CreateProgram()
{
	m_program = glCreateProgram();
	if (m_program == 0)
	{
		std::cerr << "Errore nel creare lo shaderProgram" << std::endl;
		return false;
	}
	return true;
}

bool Resources::ShaderResources::IsProgramCreated()
{
	return m_program != 0;
}

bool Resources::ShaderResources::LinkProgram()
{
	glLinkProgram(m_program);
	GLint _programLinked;
	glGetProgramiv(m_program, GL_LINK_STATUS, &_programLinked);
	if (!_programLinked) {
		char infoLog[1024];
		glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
		std::cerr << "Errore nel collegamento del programma shader: " << infoLog << std::endl;
		return false;
	}
	std::cout << "Collegamento del programma shader completato con successo." << std::endl;
	return true;
}

Resources::Entitys::Shader* Resources::ShaderResources::CompileShader(const char* _data, GLenum _type)
{
	GLuint _shaderID = glCreateShader(_type);
	glShaderSource(_shaderID, 1, &_data, nullptr);
	glCompileShader(_shaderID);
	GLint _compileStatus;
	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &_compileStatus);

	auto _shaderEntity = new Entitys::Shader(_shaderID, _type);

	if (!_compileStatus) {
		char _infoLog[1024];
		glGetShaderInfoLog(_shaderID, 1024, nullptr, _infoLog);
		std::cerr << "Errore nella compilazione dello shader: " << _infoLog << std::endl;

		_shaderEntity->Compiled(false);
	}
	else
		_shaderEntity->Compiled(true);

	m_shaders.push_back(_shaderEntity);
	return _shaderEntity;
}
