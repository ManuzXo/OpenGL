#include "../../STDInclude.hpp"

void Resources::Entitys::Shader::Compiled(bool _compiled)
{
	m_compiled = _compiled;
}

GLint Resources::Entitys::Shader::GetShaderID()
{
	return m_shaderId;
}

GLenum Resources::Entitys::Shader::GetType()
{
	return m_type;
}

bool Resources::Entitys::Shader::IsCompiled()
{
	return m_compiled;
}
