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
	static glm::mat4 model = glm::mat4(1.0f);  // Matrice identità

	static auto * _gameObjects = &Resources::GameObjectResources::m_gameObjects;
	static auto _program = Resources::ShaderResources::GetProgram();

	// Ottieni le posizioni degli uniformi "model", "view" e "projection"
	static auto _modelLocation = glGetUniformLocation(_program, "model");
	static auto _viewLocation = glGetUniformLocation(_program, "view");
	static auto _projectionLocation = glGetUniformLocation(_program, "projection");

	// Passa le matrici al vertex shader
	glUniformMatrix4fv(_modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, glm::value_ptr(*_cameraView));
	glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, glm::value_ptr(*_projection));

	for (auto _gObj : *_gameObjects)
	{
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


