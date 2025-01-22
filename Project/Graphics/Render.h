#pragma once
namespace Graphics {
	class Render{
	public:
		static bool Init();
		static void MainLoop();
		static void Destroy();
	private:
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
		static GLFWwindow* m_window;
		static GLFWmonitor* m_monitor;
		static float m_fps;
	};
}