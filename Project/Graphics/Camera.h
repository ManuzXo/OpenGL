#pragma once
namespace Graphics {
	class Camera {
	public:
		static void Setup();
		static void SetAspectRatio(int _width, int _height);
		static void SetFov(float _fov);
		static void MoveForward(float _deltaTime);
		static void MoveBackward(float _deltaTime);
		static void MoveLeft(float _deltaTime);
		static void MoveRight(float _deltaTime);
		static void ProcessMouseOffset(float _x, float _y);
		static float GetFov();
		static glm::mat4* GetProjection();
		static glm::mat4* GetCameraView();
	private:
		static glm::vec3 GetFrontDirection();
		static glm::vec3 GetRightDirection();
		static glm::mat4 m_projection, m_cameraView;
		static glm::vec3 m_cameraPosition, m_cameraTarget;
		static float m_aspectRatio;
		static float m_fov;
		static float m_yaw;
		static float m_pitch;
		static bool m_limitPitch;
		static float m_maxPitch, m_minPitch;

		static const float m_cameraSpeed;
		static const float m_cameraSensitivity;
	};
}