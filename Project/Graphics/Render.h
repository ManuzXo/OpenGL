#pragma once
namespace Graphics {
	class Render{
	public:
		static void Draw();
		static void Clear();
		static void BindProgram();
		static bool m_isPoly;
	};
}