#pragma once
namespace Resources::Entitys{
	class Shader {
	public:
		Shader(GLint _id, GLenum _type) : m_shaderId(_id), m_type(_type){}
		void Compiled(bool _compiled);
		GLint GetShaderID();
		GLenum GetType();
		bool IsCompiled();
	private:
		GLuint m_shaderId;
		GLenum m_type;
		bool m_compiled;
	};
}