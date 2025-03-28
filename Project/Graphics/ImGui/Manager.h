#pragma once
namespace Graphics::DearImGui {
	class Manager {
	public:
		static bool Init(GLFWwindow * _window, const char* _glslVersion);
		static void NewFrame();
		static void SetupUtils();
		static void SetupInfoText();
		static void Draw();
		static void Destroy();
		static bool IsHover();
	private:
	};
}