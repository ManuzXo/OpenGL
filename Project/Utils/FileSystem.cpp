
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "FileSystem.h"


bool Utils::FileSystem::SubPathFinder(std::string _filePath, std::string & _fullPathDest)
{
	//perchè quando si debugga in VS, il current path non 
	// è dove sta il bin/ ma proprio dove stanno i file source
#if _DEBUG
	_filePath = "Assets/" + _filePath;
#endif

	std::string _executable_path = fs::current_path().string();
	_fullPathDest = _executable_path + "/" + _filePath;
	if (!fs::exists(_fullPathDest) || !fs::is_directory(_fullPathDest)) {
		std::cerr << "La cartella " << _filePath << " non esiste o non è una directory valida." << std::endl;
		return false;
	}
	else
	{
		std::cout << "La cartella " << _filePath << " esiste" << std::endl;
		return true;
	}
}

bool Utils::FileSystem::ReadFile(std::string _filePath, std::string & _dataDst)
{
	std::ifstream _fileStream(_filePath);
	if (!_fileStream.is_open()) {
		std::cerr << "Impossibile aprire il file: " << _filePath << std::endl;
		return false;
	}
	std::stringstream _stream;
	_stream << _fileStream.rdbuf();
	_dataDst = _stream.str().c_str();
	return true;
}
