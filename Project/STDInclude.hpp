#pragma once
#include "GLEW/glew.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils/Color.h"
#include "Utils/Structs.h"
#include "Utils/FileSystem.h"

#include "Resources/Models/MTL.h"

#include "Resources/Models/BaseModel.h"
#include "Resources/Models/OBJ.h"

#include "Resources/Entitys/GL/Shader.h"
#include "Resources/Entitys/GL/Program.h"

#include "Resources/Entitys/GameObject.h"
#include "Resources/GameObjectResources.h"

#include "Resources/ShaderResources.h"

#include "Graphics/Camera.h"
#include "Graphics/Render.h"
#include "Graphics/Window.h"

#include "Components/SceneManager.h"