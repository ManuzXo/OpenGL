#pragma once
namespace Resources::Entitys::GL {
	class Program {
	public:
		Program();
		~Program();
		bool IsCreated();
		void AttachShader(GLuint _shaderID);
		bool Link();
		GLuint Id();
	private:	
		GLuint m_program;
	};
}