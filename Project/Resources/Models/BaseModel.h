#pragma once
namespace Resources::Models {
	class BaseModel {
	public:
		virtual std::vector<Utils::vertexData_t> GetVertexData() 
		{
			return std::vector<Utils::vertexData_t>();
		};
	};
}