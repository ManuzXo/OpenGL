#pragma once
#include <string>
namespace fs = std::filesystem;
namespace Utils {
	class FileSystem {
	public:
		static bool SubPathFinder(std::string _filePath, std::string& _fullPathDest);
		static bool ReadFile(std::string _filePath, std::string& _dataDst);
	};
}