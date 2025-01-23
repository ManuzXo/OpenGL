#pragma once
namespace Resources::Entitys {
	class GameObject {
	public:
		void AddData(Utils::vertexData_t _data);
	private:
		std::vector<Utils::vertexData_t> m_vertexData;
	};
}