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
#include <tuple>
#include <unordered_map>

#include "GLFW/glfw3.h"

//IMGUI
#include "Graphics/ImGui/imgui.h"
#include "Graphics/ImGui/imgui_impl_glfw.h"
#include "Graphics/ImGui/imgui_impl_opengl3.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Utils/Color.h"
#include "Utils/Structs.h"
#include "Utils/FileSystem.h"


//RESOURCES
#include "Resources/Entitys/GL/VertexBuffer.h"

#include "Resources/Models/MTL.h"

#include "Resources/Entitys/GL/Shader.h"
#include "Resources/Entitys/GL/Program.h"

#include "Resources/Entitys/GameObject.h"

#include "Resources/Models/BaseModel.h"
#include "Resources/Models/OBJ.h"

#include "Resources/Batching.h"
#include "Resources/GameObjectResources.h"

#include "Resources/ShaderResources.h"

//GRAPHICS

#include "Graphics/Camera.h"
#include "Graphics/Render.h"
#include "Graphics/ImGui/Manager.h"
#include "Graphics/Window.h"

#include "Components/SceneManager.h"