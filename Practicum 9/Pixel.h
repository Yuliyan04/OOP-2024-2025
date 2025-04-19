#pragma once
#include <iostream>

class Pixel
{
	uint8_t R;
	uint8_t G;
	uint8_t B;

public:

	uint8_t getR() const;
	uint8_t getG() const;
	uint8_t getB() const;
	
	void setR(uint8_t R);
	void setG(uint8_t G);
	void setB(uint8_t B);

	void print() const;
};

