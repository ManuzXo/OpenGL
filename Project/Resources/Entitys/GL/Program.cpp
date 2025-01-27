#include "../../../STDInclude.hpp"

Resources::Entitys::GL::Program::Program()
{
	m_program = glCreateProgram();
}

Resources::Entitys::GL::Program::~Program()
{
	glDeleteProgram(m_program);
}

bool Resources::Entitys::GL::Program::IsCreated()
{
	return m_program != 0;
}

void Resources::Entitys::GL::Program::AttachShader(GLuint _shaderID)
{
	glAttachShader(m_program, _shaderID);
}

bool Resources::Entitys::GL::Program::Link()
{
	glLinkProgram(m_program);
	glValidateProgram(m_program);

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

GLuint Resources::Entitys::GL::Program::Id()
{
	return m_program;
}
