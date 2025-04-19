#pragma once
#include "Pixel.h"


class Picture
{
	Pixel** pic;
	size_t width;
	size_t length;

public:
	
	Picture();
	Picture(const Picture& other);
	Picture(Picture&& other) noexcept;
	Picture& operator=(const Picture& other);
	Picture& operator=(Picture&& other) noexcept;
	~Picture();

	void Grayscale();
	void Monochrome();
	void Negative();

	bool isMonochrome() const;
	bool isGrayscale() const;

	void print() const;
	size_t getWidth() const;
	size_t getLength() const;
	Pixel& getPixel(size_t i, size_t j) const;

private:

	void copyFrom(const Picture& other);
	void moveFrom(Picture&& other);
	void free();
};

