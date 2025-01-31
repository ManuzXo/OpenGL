#include "../STDInclude.hpp"

bool Graphics::Render::m_wireFrame = false;
void Graphics::Render::Draw()
{
	static auto _program = Resources::ShaderResources::GetProgram();
	static auto _projection = Camera::GetProjection();
	static auto _cameraView = Camera::GetCameraView();
	static auto* _gameObjects = &Resources::GameObjectResources::m_gameObjects;
	static auto _mvpLocation = glGetUniformLocation(_program, "u_mvp");
	if (m_wireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (Resources::Batching::m_useBatch)
	{
		glm::mat4 _calcMVP = (*_projection) * (*_cameraView) * glm::mat4(1.0f);
		glUniformMatrix4fv(_mvpLocation, 1, GL_FALSE, glm::value_ptr(_calcMVP));
		static auto _batch = Resources::Batching::GetVertexBatch();
		_batch->Bind();
		_batch->UnBind();
	}
	else
	{
		for (auto _gObj : *_gameObjects)
		{
			auto _transform = _gObj->GetTransform();
			glm::mat4 _calcMVP = (*_projection) * (*_cameraView) * _transform->GetModelMatrix();
			glUniformMatrix4fv(_mvpLocation, 1, GL_FALSE, glm::value_ptr(_calcMVP));
			auto _vertexData = _gObj->m_vertexData;
			_vertexData->Bind();
			_vertexData->UnBind();
		}
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


