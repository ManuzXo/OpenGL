#pragma once
namespace Utils {
	class Color {
	public:
		Color(float _r, float _g, float _b, float _a);
		void SetRGBA(float _r, float _g, float _b, float _a);
		void SetRGBA(Color  _color);
		float* GetRGBA();
	private:
		float r, g, b, a;
	};
}