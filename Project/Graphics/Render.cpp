#include "../STDInclude.hpp"

bool Graphics::Render::m_isPoly = false;
void Graphics::Render::Draw()
{
	if (m_isPoly)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	static auto _projection = Camera::GetProjection();
	static auto _cameraView = Camera::GetCameraView();

	static auto * _gameObjects = &Resources::GameObjectResources::m_gameObjects;
	static auto _program = Resources::ShaderResources::GetProgram();

	static auto _mvpLocation = glGetUniformLocation(_program, "u_mvp");

	for (auto _gObj : *_gameObjects)
	{
		glm::mat4 _calcMVP = (*_projection) * (*_cameraView) * _gObj->GetModelMatrix();
		glUniformMatrix4fv(_mvpLocation, 1, GL_FALSE, glm::value_ptr(_calcMVP));
		glBindVertexArray(_gObj->GetVertexArray());
		glDrawArrays(GL_TRIANGLES, 0, _gObj->GetVertexSize());
	}
}

void Graphics::Render::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::Render::BindProgram()
{
	//Use Program
	glUseProgram(Resources::ShaderResources::GetProgram());
}


