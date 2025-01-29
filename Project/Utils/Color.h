#pragma once
namespace Utils {
	class Color {
	public:
		Color();
		Color(float _r, float _g, float _b, float _a);
		void SetRGBA(Color  _color);
		float* GetRGBA();
		bool operator==(const Color& other) const;
		float r, g, b, a;
	};
}