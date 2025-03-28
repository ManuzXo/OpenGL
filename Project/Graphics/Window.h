#pragma once
namespace Graphics {
	class Window {
	public:
		static bool Init();
		static void MainLoop();
		static void Destroy();
		static void SetPlayState(bool _value);

	private:
		static void MoveCamera();
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

		/// https://www.glfw.org/docs/3.3/group__input.html#ga5bd751b27b90f865d2ea613533f0453c
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ErrorCallBack(int error_code, const char* description);
		static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		static void FocusCallback(GLFWwindow* window, int focused);
		static GLFWwindow* m_window;
		static GLFWmonitor* m_monitor;
		static float m_fps;
		static int m_widthMonitor, m_heightMonitor;
		static double m_deltaTime;
		static bool m_windowFocus;
		static bool m_isPlaying;
	};
}