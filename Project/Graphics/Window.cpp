#include "../STDInclude.hpp"

GLFWwindow* Graphics::Window::m_window = NULL;
GLFWmonitor* Graphics::Window::m_monitor = NULL;
float Graphics::Window::m_fps = 60.0;
int Graphics::Window::m_widthMonitor;
int Graphics::Window::m_heightMonitor;
double Graphics::Window::m_deltaTime;
bool Graphics::Window::m_focus = true;
bool Graphics::Window::Init()
{
	std::cout << "##### Render Init #####" << std::endl;
	if (glfwInit() == GLFW_TRUE)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_monitor = glfwGetPrimaryMonitor();
		if (m_monitor != NULL)
		{

			const GLFWvidmode* _mode = glfwGetVideoMode(m_monitor);
			if (_mode != NULL)
			{

				glfwWindowHint(GLFW_RED_BITS, _mode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, _mode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, _mode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, _mode->refreshRate);

				m_widthMonitor = _mode->width;
				m_heightMonitor = _mode->height;

				m_window = glfwCreateWindow(m_widthMonitor, m_heightMonitor, "Project Test", NULL, NULL);
				if (m_window != NULL)
				{
					std::cout << "Creazione finestra fatto con successo!" << std::endl;

					std::cout << "Creazione del contesto!" << std::endl;
					glfwMakeContextCurrent(m_window);

					std::cout << "Creazione del callback per gli input!" << std::endl;
					glfwSetKeyCallback(m_window, KeyCallback);

					std::cout << "Creazione del callback per gli errore!" << std::endl;
					glfwSetErrorCallback(ErrorCallBack);

					std::cout << "Creazione del callback per il frame buffer size window!" << std::endl;
					glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

					std::cout << "Creazione del callback per il mouse" << std::endl;
					glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
					glfwSetCursorPosCallback(m_window, CursorPositionCallback);

					std::cout << "Creazione del callback per il focus window" << std::endl;
					glfwSetWindowFocusCallback(m_window, FocusCallback);

					std::cout << "ImGui Init" << std::endl;
					DearImGui::Manager::Init(m_window, "#version 330 core");

					std::cout << "Versione OpenGL: " << glGetString(GL_VERSION) << std::endl;

					glEnable(GL_DEPTH_TEST);
					//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

					Camera::SetAspectRatio(_mode->width, _mode->height);

					return true;
				}
				else
				{
					std::cerr << "Errore nella creazione della finestra Windows!" << std::endl;
					return false;
				}
				delete _mode;
			}
			else
			{
				std::cerr << "Errore nel prendere le informazioni riguardo al monitor!" << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "Impossibile trovare il monitor primario!" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Errore nell'inizializzatore glfw!" << std::endl;
		return false;
	}
}

void Graphics::Window::MainLoop()
{
	const double _frameDuration = 1.0 / m_fps; // Durata di un frame a 60 FPS
	double _lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(m_window)) {

		//SE NON IN FOCUS NON RENDERIZZARE

		double _currentFrameTime = glfwGetTime();
		m_deltaTime = _currentFrameTime - _lastFrameTime;
		if (m_deltaTime < _frameDuration) {
			glfwWaitEventsTimeout(_frameDuration - m_deltaTime);
			continue;
		}

		// Gestione degli eventi
		glfwPollEvents();

		if (!m_focus)
			continue;

		_lastFrameTime = _currentFrameTime;

		MoveCamera();

		Render::Draw();
		DearImGui::Manager::Draw();

		// Swap dei buffer
		glfwSwapBuffers(m_window);
	}
}

void Graphics::Window::Destroy()
{
	std::cout << "##### Render Destroy #####" << std::endl;

	if (m_window != NULL)
		glfwDestroyWindow(m_window);
	if (m_monitor != NULL)
		free(m_monitor);
	//SE NON COMMENTATO ALLA CHIUSURA DELL'APP FA "Gamma ramp size must be 256"
	//glfwTerminate();
}

void Graphics::Window::MoveCamera()
{
	// Movimenti della telecamera
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
		Camera::MoveForward(m_deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
		Camera::MoveBackward(m_deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
		Camera::MoveRight(m_deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
		Camera::MoveLeft(m_deltaTime);
	}
}

void Graphics::Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Graphics::Window::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	static float _lastXPos = m_widthMonitor / 2;
	static float _lastYPos = m_heightMonitor / 2;
	static bool _firstMouse = true;

	if (_firstMouse) // Evita un salto improvviso al primo frame
	{
		_lastXPos = xpos;
		_lastYPos = ypos;
		_firstMouse = false;
	}

	float xOffset = xpos - _lastXPos;
	float yOffset = _lastYPos - ypos; // Invertito, perché il movimento verso l'alto diminuisce y
	_lastXPos = xpos;
	_lastYPos = ypos;
	Graphics::Camera::ProcessMouseOffset(xOffset, yOffset);
}

void Graphics::Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		auto _cursorMode = glfwGetInputMode(window, GLFW_CURSOR);
		if (_cursorMode == GLFW_CURSOR_NORMAL)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		else if (_cursorMode == GLFW_CURSOR_DISABLED)
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		Camera::SetCameraSpeed(Camera::GetCameraDefaultSpeed() * 2);
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
	{
		Camera::ResetCameraSpeed();
	}
	else if (key == GLFW_KEY_1)
		Camera::SetFov(Camera::GetFov() + 1.0f);
	else if (key == GLFW_KEY_2)
		Camera::SetFov(Camera::GetFov() - 1.0f);
	std::cout << "Key: " << key << " ScanCode: " << scancode << " Action: " << action << " Mods: " << mods << std::endl;
}

void Graphics::Window::ErrorCallBack(int error_code, const char* description)
{
	std::cerr << "GLFW Codice di errore: " << error_code << " Descrizione: " << description << std::endl;
}

void Graphics::Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	m_widthMonitor = width;
	m_heightMonitor = height;
	// Imposta il viewport in base alle nuove dimensioni della finestra
	glViewport(0, 0, width, height);
	Camera::SetAspectRatio(width, height);
}

void Graphics::Window::FocusCallback(GLFWwindow* window, int focused)
{
	m_focus = (bool)focused;
}
