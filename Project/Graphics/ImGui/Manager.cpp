#include "../../STDInclude.hpp"

bool Graphics::DearImGui::Manager::Init(GLFWwindow* _window, const char* _glslVersion)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init(_glslVersion);
	return true;
}
void Graphics::DearImGui::Manager::NewFrame()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void Graphics::DearImGui::Manager::SetupUtils()
{
	ImGui::Begin("Utils");

	if (ImGui::Button("Play")) {
		Window::SetPlayState(true);
	}
	ImGui::Checkbox("Polygon Mode", &Render::m_wireFrame);
	static auto* _gameObjects = &Resources::GameObjectResources::m_gameObjects;

	if (ImGui::Checkbox("Batch", &Resources::Batching::m_useBatch))
	{
		if (Resources::Batching::m_useBatch)
		{
			//PULISCO I SINGOLI OGGETTI 
			Resources::GameObjectResources::ClearGameObjects();
			//RINIZIALIZZO SENZA COMPILARLI ESSENDO CHE USEBATCH è A TRUE
			Resources::GameObjectResources::Init();
			//INIZIALIZZO BATCH
			Resources::Batching::Init(*_gameObjects);
		}
		else
		{
			//PULISCO BATCH
			Resources::Batching::ClearBatch();
			//PULISCO GLI OGGETTI
			Resources::GameObjectResources::ClearGameObjects();

			//RINIZILIZZO OGNI SINGOLO OGGETTO COMPILANDOLO
			Resources::GameObjectResources::Init();
			Resources::GameObjectResources::CompileObjects();
		}
	}

	ImGui::Separator();
	ImGui::Text("Game Objects");
	ImGui::Separator();

	for (auto _gObj : *_gameObjects)
	{
		ImGui::Text("Name: %s", _gObj->GetName().c_str());

		if (_gObj->m_vertexData) {
			ImGui::Text("Vertices: %d", _gObj->m_vertexData->GetVertexSize());
			ImGui::Text("Indices: %d", _gObj->m_vertexData->GetIndicesSize());
		}
		else {
			ImGui::Text("No vertex data");
		}
		auto _pos = _gObj->GetPosition();
		ImGui::SliderFloat3("Position", &_pos.x, -10.0f, 10.0f);
		ImGui::Separator(); // Separatore per leggibilità
	}
	ImGui::End();
}
void Graphics::DearImGui::Manager::SetupInfoText()
{
	ImGui::Begin("Info");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}
void Graphics::DearImGui::Manager::Draw()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void Graphics::DearImGui::Manager::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool Graphics::DearImGui::Manager::IsHover()
{
	// Ottieni la posizione e le dimensioni della finestra corrente
	ImVec2 _windowPos = ImGui::GetWindowPos();    // Posizione della finestra (angolo in alto a sinistra)
	ImVec2 _windowSize = ImGui::GetWindowSize();  // Dimensioni della finestra
	// Calcola il rettangolo che rappresenta la finestra
	ImVec2 _rectMin = _windowPos;                                     // Angolo superiore sinistro
	ImVec2 _rectMax = ImVec2(_windowPos.x + _windowSize.x,            // Angolo inferiore destro
		_windowPos.y + _windowSize.y);

	return ImGui::IsMouseHoveringRect(_rectMin, _rectMax);
}
