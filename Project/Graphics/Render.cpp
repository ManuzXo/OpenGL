#include "../STDInclude.hpp"

GLFWwindow* Graphics::Render::m_window = NULL;
GLFWmonitor* Graphics::Render::m_monitor = NULL;
float Graphics::Render::m_fps = 60.0;

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
	glfwTerminate();
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

