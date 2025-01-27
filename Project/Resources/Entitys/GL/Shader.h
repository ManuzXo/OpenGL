#pragma once
namespace Resources::Entitys::GL{
	class Shader {
	public:
		Shader(GLint _id, GLenum _type);
		~Shader();
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