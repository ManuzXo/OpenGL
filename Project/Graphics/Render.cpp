#include "../STDInclude.hpp"

GLFWwindow* Graphics::Render::m_window = NULL;
GLFWmonitor* Graphics::Render::m_monitor = NULL;
float Graphics::Render::m_fps = 60.0;


float vertices[] = {
	// Posizioni dei vertici (x, y, z)
	 0.0f,  0.5f, 0.0f, // Vertice superiore
	-0.5f, -0.5f, 0.0f, // Vertice sinistro
	 0.5f, -0.5f, 0.0f  // Vertice destro
};
GLuint VAO, VBO;



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
					glfwMakeContextCurrent(m_window);
					std::cout << "Creazione del contesto!" << std::endl;
					glfwSetKeyCallback(m_window, KeyCallback);
					std::cout << "Creazione del callback per gli input!" << std::endl;


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
	// Creare VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Creare VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Specificare l'attributo dei vertici (layout(location = 0) in vec3 aPos)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Scollega il VAO per evitare modifiche accidentali
	glBindVertexArray(0);



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
		
		// Bind del VAO e disegna i vertici
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Disegna 3 vertici come un triangolo
		glBindVertexArray(0);

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

	// Cancella i VAO e VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Graphics::Render::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key: " << key << " ScanCode: " << scancode << " Action: " << action << " Mods: " << mods << std::endl;
}

