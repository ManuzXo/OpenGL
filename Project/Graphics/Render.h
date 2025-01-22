#pragma once
namespace Graphics {
	class Render{
	public:
		static bool Init();
		static void MainLoop();
		static void Destroy();
	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static GLFWwindow* m_window;
		static GLFWmonitor* m_monitor;
		static float m_fps;
	};
}