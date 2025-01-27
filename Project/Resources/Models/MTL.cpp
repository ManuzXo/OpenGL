#include "../../STDInclude.hpp"


Resources::Models::MTL::MTL()
{
}

Resources::Models::MTL::~MTL()
{
    m_materialsColor.clear();
}

bool Resources::Models::MTL::Load(const std::string& _filePath)
{
    std::ifstream _file(_filePath);
    if (!_file.is_open()) {
        std::cerr << "Impossibile aprire il file MTL: " << _filePath << std::endl;
        return false;
    }
    std::string _line;
    std::string _materialName;
    while (std::getline(_file, _line)) {
        std::istringstream _iss(_line);
        std::string _prefix;
        _iss >> _prefix;

        if (_prefix == "newmtl") {
            _iss >> _materialName;
            
        }
        else if (_prefix == "Kd") {
            Utils::Color _color;
            _iss >> _color.r >> _color.g >> _color.b;
            _color.a = 1.0f;
            m_materialsColor[_materialName] = _color;
        }
    }
    _file.close();
    return true;
}

const std::map<std::string, Utils::Color>& Resources::Models::MTL::GetMaterialsColor()
{
    return m_materialsColor;
}
