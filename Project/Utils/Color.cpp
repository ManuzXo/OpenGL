#include "Color.h"

Utils::Color::Color(float _r, float _g, float _b, float _a)
{
	this->r = _r;
	this->g = _g;
	this->b = _b;
	this->a = _a;
}

void Utils::Color::SetRGBA(float _r, float _g, float _b, float _a)
{
	this->r = _r;
	this->g = _g;
	this->b = _b;
	this->a = _a;
}

void Utils::Color::SetRGBA(Color _color)
{
	auto _rgba = _color.GetRGBA();
	this->r = _rgba[0];
	this->g = _rgba[1];
	this->b = _rgba[2];
	this->a = _rgba[3];
}

float* Utils::Color::GetRGBA()
{
	float _rgba[4] = { this->r, this->g, this->b, this->a };
	return _rgba;
}
