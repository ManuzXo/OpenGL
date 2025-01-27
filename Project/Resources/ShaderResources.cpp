#include "../STDInclude.hpp"

std::vector<Resources::Entitys::GL::Program*> Resources::ShaderResources::m_programs;
std::vector<Resources::Entitys::GL::Shader*> Resources::ShaderResources::m_shaders;
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
					FileShaderManager(_entry);
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

void Resources::ShaderResources::Destroy()
{
	std::cout << "##### ShaderResources Destroy #####" << std::endl;

	//DELETE SHADER AS FRAG & VERT
	for (auto _shader : m_shaders)
	{
		delete _shader;
	}
	m_shaders.clear();
	for (auto _program : m_programs)
	{
		delete _program;
	}
	m_programs.clear();
}

GLuint Resources::ShaderResources::GetProgram()
{
	return m_programs[0]->Id();
}


void Resources::ShaderResources::FileShaderManager(const std::filesystem::directory_entry& _file)
{
	auto _fullPath = _file.path();
	std::ifstream _stream(_fullPath);
	std::stringstream _ss[2];
	
	enum ShaderType_e {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType_e _shaderType = NONE;

	auto _program = new  Entitys::GL::Program();
	if (_program->IsCreated())
	{
		std::string _line;
		while (getline(_stream, _line))
		{
			if (_line.find("#shader") != std::string::npos)
			{
				if (_line.find("vertex") != std::string::npos)
				{
					_shaderType = VERTEX;
				}
				else if (_line.find("fragment") != std::string::npos)
				{
					_shaderType = FRAGMENT;
				}
			}
			else
			{
				_ss[_shaderType] << _line << "\n";
			}
		}
		auto _vertexEntity = CompileShader(_ss[ShaderType_e::VERTEX].str().c_str(), GL_VERTEX_SHADER);
		if (_vertexEntity->IsCompiled())
		{
			_program->AttachShader(_vertexEntity->GetShaderID());
		}

		auto _fragmentEntity = CompileShader(_ss[ShaderType_e::FRAGMENT].str().c_str(), GL_FRAGMENT_SHADER);
		if (_fragmentEntity->IsCompiled())
		{
			_program->AttachShader(_fragmentEntity->GetShaderID());
		}
	}
	if (_program->Link())
		m_programs.push_back(_program);
	else
		delete _program;

}

Resources::Entitys::GL::Shader* Resources::ShaderResources::CompileShader(const char* _data, GLenum _type)
{
	GLuint _shaderID = glCreateShader(_type);
	glShaderSource(_shaderID, 1, &_data, nullptr);
	glCompileShader(_shaderID);
	GLint _compileStatus;
	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &_compileStatus);

	auto _shaderEntity = new Entitys::GL::Shader(_shaderID, _type);

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
