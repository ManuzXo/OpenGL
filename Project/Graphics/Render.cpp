#include "../STDInclude.hpp"

GLFWwindow* Graphics::Render::m_window = NULL;
GLFWmonitor* Graphics::Render::m_monitor = NULL;
float Graphics::Render::m_fps = 60.0;
int Graphics::Render::m_widthMonitor;
int Graphics::Render::m_heightMonitor;
double Graphics::Render::m_deltaTime;

bool Graphics::Render::Init()
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

					std::cout << "Versione OpenGL: " << glGetString(GL_VERSION) << std::endl;

					glEnable(GL_DEPTH_TEST);

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

void Graphics::Render::MainLoop()
{
	auto _projection = Camera::GetProjection();
	auto _cameraView = Camera::GetCameraView();

	const double _frameDuration = 1.0 / m_fps; // Durata di un frame a 60 FPS
	double _lastFrameTime = glfwGetTime();

	// Inizializza gli angoli di rotazione
	float angleX = 0.0f; // Angolo di rotazione attorno all'asse X (su e giù)
	float angleY = 0.0f; // Angolo di rotazione attorno all'asse Y (sinistra e destra)

	while (!glfwWindowShouldClose(m_window)) {
		double _currentFrameTime = glfwGetTime();
		m_deltaTime = _currentFrameTime - _lastFrameTime;
		if (m_deltaTime < _frameDuration) {
			glfwWaitEventsTimeout(_frameDuration - m_deltaTime);
			continue;
		}

		_lastFrameTime = _currentFrameTime;

		MoveCamera();


		// Incrementiamo gli angoli di rotazione
		angleX += 0.5f;  // Angolo di rotazione attorno all'asse X
		angleY += 1.0f;  // Angolo di rotazione attorno all'asse Y

		// Creiamo le matrici di rotazione per X e Y
		glm::mat4 model = glm::mat4(1.0f);  // Matrice identità

		// Rotazione attorno all'asse X (su e giù)
		model = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));

		// Rotazione attorno all'asse Y (sinistra e destra)
		model = glm::rotate(model, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));


		// Rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use Program
		glUseProgram(Resources::ShaderResources::GetProgram());

		// Ottieni le posizioni degli uniformi "model", "view" e "projection"
		GLuint modelLoc = glGetUniformLocation(Resources::ShaderResources::GetProgram(), "model");
		GLuint viewLoc = glGetUniformLocation(Resources::ShaderResources::GetProgram(), "view");
		GLuint projLoc = glGetUniformLocation(Resources::ShaderResources::GetProgram(), "projection");

		// Passa le matrici al vertex shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*_cameraView));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(*_projection));

		for (auto _gObj : Resources::GameObjectResources::m_gameObjects)
		{
			glBindVertexArray(_gObj->GetVertexArray());
			glDrawArrays(GL_TRIANGLES, 0, _gObj->GetVertexSize());
		}

		// Swap dei buffer
		glfwSwapBuffers(m_window);

		// Gestione degli eventi
		glfwPollEvents();
	}
}


void Graphics::Render::Destroy()
{
	std::cout << "##### Render Destroy #####" << std::endl;

	if (m_window != NULL)
		glfwDestroyWindow(m_window);
	if (m_monitor != NULL)
		free(m_monitor);
	//SE NON COMMENTATO ALLA CHIUSURA DELL'APP FA "Gamma ramp size must be 256"
	//glfwTerminate();
}

void Graphics::Render::MoveCamera()
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

void Graphics::Render::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Graphics::Render::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
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

void Graphics::Render::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_ESCAPE)
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
	}
	else
	{
		if (key == GLFW_KEY_1)
			Camera::SetFov(Camera::GetFov() + 1.0f);

		else if (key == GLFW_KEY_2)
			Camera::SetFov(Camera::GetFov() - 1.0f);
	}
	std::cout << "Key: " << key << " ScanCode: " << scancode << " Action: " << action << " Mods: " << mods << std::endl;
}

void Graphics::Render::ErrorCallBack(int error_code, const char* description)
{
	std::cerr << "GLFW Codice di errore: " << error_code << " Descrizione: " << description << std::endl;
}

void Graphics::Render::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	m_widthMonitor = width;
	m_heightMonitor = height;
	// Imposta il viewport in base alle nuove dimensioni della finestra
	glViewport(0, 0, width, height);
	Camera::SetAspectRatio(width, height);
}

