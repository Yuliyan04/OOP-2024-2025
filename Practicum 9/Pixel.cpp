#include "Pixel.h"


uint8_t Pixel::getR() const
{
	return R;
}

uint8_t Pixel::getG() const
{
	return G;
}

uint8_t Pixel::getB() const
{
	return B;
}


void Pixel::setR(uint8_t R)
{
	this->R = R;
}

void Pixel::setG(uint8_t R)
{
	this->G = G;
}

void Pixel::setB(uint8_t R)
{
	this->B = B;
}

void Pixel::print() const
{
	std::cout << "(" << R << "," << G << "," << B << ")";
}