#pragma once
namespace Graphics {
	class Window {
	public:
		static bool Init();
		static void MainLoop();
		static void Destroy();

	private:
		static void MoveCamera();
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		/// <summary>
		/// https://www.glfw.org/docs/3.3/group__input.html#ga5bd751b27b90f865d2ea613533f0453c
		/// </summary>
		/// <param name="window"></param>
		/// <param name="key"></param>
		/// <param name="scancode"></param>
		/// <param name="action"></param>
		/// <param name="mods"></param>
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ErrorCallBack(int error_code, const char* description);
		static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		static GLFWwindow* m_window;
		static GLFWmonitor* m_monitor;
		static float m_fps;
		static int m_widthMonitor, m_heightMonitor;
		static double m_deltaTime;
	};
}