#pragma once
namespace Resources::Models {
	class MTL
	{
	public:
		MTL();
		~MTL();
		bool Load(const std::string& _filePath);
		const std::map<std::string, Utils::Color>& GetMaterialsColor();
	private:
		std::map<std::string, Utils::Color> m_materialsColor;
	};
}