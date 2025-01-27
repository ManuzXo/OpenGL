#include "../../../STDInclude.hpp"

Resources::Entitys::GL::Shader::Shader(GLint _id, GLenum _type)
{
	m_shaderId = _id;
	m_type = _type;
}

Resources::Entitys::GL::Shader::~Shader()
{
	if (IsCompiled())
		glDeleteShader(m_shaderId);
}

void Resources::Entitys::GL::Shader::Compiled(bool _compiled)
{
	m_compiled = _compiled;
}

GLint Resources::Entitys::GL::Shader::GetShaderID()
{
	return m_shaderId;
}

GLenum Resources::Entitys::GL::Shader::GetType()
{
	return m_type;
}

bool Resources::Entitys::GL::Shader::IsCompiled()
{
	return m_compiled;
}
