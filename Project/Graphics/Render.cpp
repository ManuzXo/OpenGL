#include "../STDInclude.hpp"

GLFWwindow* Graphics::Render::m_window = NULL;
GLFWmonitor* Graphics::Render::m_monitor = NULL;
float Graphics::Render::m_fps = 60.0;

Utils::vertexData_t m_cube[] = {
	// Faccia frontale
	{{-0.5f, -0.5f, 0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{-0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{0.5f, 0.5f, 0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia posteriore
	{{-0.5f, -0.5f, -0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 2 (blu)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 3 (verde)

	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 3 (verde) (ripetuto)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 2 (blu) (ripetuto)
	{{0.5f, 0.5f, -0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia sinistra
	{{-0.5f, -0.5f, -0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{-0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{-0.5f, -0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{-0.5f, 0.5f, 0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia destra
	{{0.5f, -0.5f, 0.5f}, 1.0f, 0.0f, 0.0f},   // Vertice 1 (rosso)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},    // Vertice 3 (blu)

	{{0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},    // Vertice 3 (blu) (ripetuto)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{0.5f, 0.5f, -0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia superiore
	{{-0.5f, 0.5f, 0.5f}, 1.0f, 0.0f, 0.0f},   // Vertice 1 (rosso)
	{{0.5f, 0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},    // Vertice 2 (verde)
	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{0.5f, 0.5f, 0.5f}, 0.0f, 1.0f, 0.0f},    // Vertice 2 (verde) (ripetuto)
	{{0.5f, 0.5f, -0.5f}, 1.0f, 1.0f, 0.0f},   // Vertice 4 (giallo)

	// Faccia inferiore
	{{-0.5f, -0.5f, -0.5f}, 1.0f, 0.0f, 0.0f}, // Vertice 1 (rosso)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde)
	{{-0.5f, -0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu)

	{{-0.5f, -0.5f, 0.5f}, 0.0f, 0.0f, 1.0f},  // Vertice 3 (blu) (ripetuto)
	{{0.5f, -0.5f, -0.5f}, 0.0f, 1.0f, 0.0f},  // Vertice 2 (verde) (ripetuto)
	{{0.5f, -0.5f, 0.5f}, 1.0f, 1.0f, 0.0f}    // Vertice 4 (giallo)
};



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

				m_window = glfwCreateWindow(_mode->width, _mode->height, "Project Test", NULL, NULL);
				if (m_window != NULL)
				{
					std::cout << "Creazione finestra fatto con successo!" << std::endl;
					
					std::cout << "Creazione del contesto!" << std::endl;
					glfwMakeContextCurrent(m_window);
					
					std::cout << "Creazione del callback per gli input!" << std::endl;
					glfwSetKeyCallback(m_window, KeyCallback);

					std::cout << "Creazione del callback per gli errore!" << std::endl;
					glfwSetErrorCallback(ErrorCallBack);

					std::cout << "Versione OpenGL: " << glGetString(GL_VERSION) << std::endl;
					return true;
				}
				else
				{
					std::cerr << "Errore nella creazione della finestra Windows!" << std::endl;
					return false;
				}
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
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube), m_cube, GL_STATIC_DRAW);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Specifica gli attributi dei vertici
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);  // Posizione
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));  // Colore
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);  // Facoltativo: scollega il VBO
	glBindVertexArray(0);             // Facoltativo: scollega il VAO


	const double _frameDuration = 1.0 / m_fps; // Durata di un frame a 60 FPS
	double _lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(m_window)) {
		double _currentFrameTime = glfwGetTime();
		double _deltaTime = _currentFrameTime - _lastFrameTime;
		if (_deltaTime < _frameDuration) {
			glfwWaitEventsTimeout(_frameDuration - _deltaTime);
			continue;
		}

		_lastFrameTime = _currentFrameTime;

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		//Use Program
		glUseProgram(Resources::ShaderResources::GetProgram());

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

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

void Graphics::Render::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	std::cout << "Key: " << key << " ScanCode: " << scancode << " Action: " << action << " Mods: " << mods << std::endl;
}

void Graphics::Render::ErrorCallBack(int error_code, const char* description)
{
	std::cerr << "GLFW Codice di errore: " << error_code << " Descrizione: " << description << std::endl;
}

