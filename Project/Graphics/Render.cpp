#include "../STDInclude.hpp"

void Graphics::Render::Draw()
{
	auto _projection = Camera::GetProjection();
	auto _cameraView = Camera::GetCameraView();
	glm::mat4 model = glm::mat4(1.0f);  // Matrice identità
	// Rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use Program
	glUseProgram(Resources::ShaderResources::GetProgram());

	// Ottieni le posizioni degli uniformi "model", "view" e "projection"
	GLuint modelLoc = glGetUniformLocation(Resources::ShaderResources::GetProgram(), "model");
	GLuint viewLoc = glGetUniformLocation(Resources::ShaderResources::GetProgram(), "view");
	GLuint projLoc = glGetUniformLocation(Resources::ShaderResources::GetProgram(), "projection");

	// Passa le matrici al vertex shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*_cameraView));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(*_projection));

	for (auto _gObj : Resources::GameObjectResources::m_gameObjects)
	{
		glBindVertexArray(_gObj->GetVertexArray());
		glDrawArrays(GL_TRIANGLES, 0, _gObj->GetVertexSize());
	}
}
