#pragma once
namespace Graphics {
	class Camera {
	public:
		static void Setup();
		static void SetAspectRatio(int _width, int _height);
		static void SetFov(float _fov);
		static float GetFov();
		static glm::mat4* GetProjection();
	private:
		static float m_aspectRatio;
		static float m_fov;
		static glm::mat4 m_projection;
	};
}