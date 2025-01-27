#pragma once
namespace Utils {
	class Color {
	public:
		Color();
		Color(float _r, float _g, float _b, float _a);
		void SetRGBA(Color  _color);
		float* GetRGBA();
		float r, g, b, a;
	};
}