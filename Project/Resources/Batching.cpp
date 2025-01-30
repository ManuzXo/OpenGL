#include "../STDInclude.hpp"

bool Resources::Batching::m_useBatch = false;
Resources::Entitys::GL::VertexBuffer* Resources::Batching::m_vertexBatch;

void Resources::Batching::Init(std::vector<Resources::Entitys::GameObject*>& _gameObjects)
{
	m_vertexBatch = new Resources::Entitys::GL::VertexBuffer();
	int _vertexSize = 0;
	
	for (auto _gObj : _gameObjects)
	{
		auto _gObjVertex = _gObj->m_vertexData;
		auto _indices = _gObjVertex->GetIndeces();
		for (int i = 0; i < _gObjVertex->GetIndicesSize(); i++) {
			m_vertexBatch->AddIndex(_indices[i] + _vertexSize);
		}
		_vertexSize += _gObjVertex->GetVertexSize();
		m_vertexBatch->InsertData(_gObjVertex->GetVertexRef());
	}

	if (m_vertexBatch->BuildVertex())
	{
		std::cout << "VertexBatch Compilato" << std::endl;
	}
	else
	{
		std::cerr << "Errore nalla compilazione VertexBatch" << std::endl;
	}
}

void Resources::Batching::ClearBatch()
{
	delete m_vertexBatch;
}

Resources::Entitys::GL::VertexBuffer* Resources::Batching::GetVertexBatch()
{
	return m_vertexBatch;
}



