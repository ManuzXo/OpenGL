#pragma once

namespace Resources {
	class Batching {
	public:
		static void Init(std::vector<Resources::Entitys::GameObject*>& _gameObjects);
		static void ClearBatch();
		static Entitys::GL::VertexBuffer* GetVertexBatch();
		static bool m_useBatch;
	private:
		static Entitys::GL::VertexBuffer *m_vertexBatch;
	};
}