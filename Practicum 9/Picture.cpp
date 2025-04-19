#include "Picture.h"


void Picture::copyFrom(const Picture& other)
{
	length = other.length;
	width = other.width;

	pic = new Pixel * [width];
	for (size_t i = 0; i < width; i++)
	{
		pic[i] = new Pixel[length];
		for (size_t j = 0; j < length; j++)
		{
			pic[i][j] = other.pic[i][j];
		}
	}
}

void Picture::moveFrom(Picture&& other)
{
	length = std::move(other.length);
	width = std::move(other.width);

	pic = other.pic;
	other.pic = nullptr;
}

void Picture::free()
{
	for (size_t i = 0; i < width; i++)
	{
		delete[] pic[i];
	}
	delete[] pic;
}


Picture::Picture() : pic(nullptr), width(0), length(0) {}

Picture::Picture(const Picture& other)
{
	copyFrom(other);
}

Picture::Picture(Picture&& other) noexcept
{
	moveFrom(std::move(other));
}

Picture& Picture::operator=(const Picture& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Picture& Picture::operator=(Picture&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Picture::~Picture()
{
	free();
}


void Picture::Grayscale()
{
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			uint8_t gray = 0.299 * pic[i][j].getR() + 0.587 * pic[i][j].getG() + 0.114 * pic[i][j].getB();
			pic[i][j].setR(gray);
			pic[i][j].setG(gray);
			pic[i][j].setB(gray);
		}
	}
}

void Picture::Monochrome()
{
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			uint8_t gray = 0.299 * pic[i][j].getR() + 0.587 * pic[i][j].getG() + 0.114 * pic[i][j].getB();
			if (gray < 128)
			{
				pic[i][j].setR(0);
				pic[i][j].setG(0);
				pic[i][j].setB(0);
			}
			else
			{
				pic[i][j].setR(255);
				pic[i][j].setG(255);
				pic[i][j].setB(255);
			}
		}
	}
}

void Picture::Negative()
{
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			pic[i][j].setR(255 - pic[i][j].getR());
			pic[i][j].setG(255 - pic[i][j].getG());
			pic[i][j].setB(255 - pic[i][j].getB());
		}
	}
}


bool Picture::isGrayscale() const
{
	if (!isGrayscale() || !isMonochrome())
	{
		throw std::logic_error("Can't use grayscale on grayscaled or monochromed picture");
	}
	for (size_t i = 0; i < width; i++) 
	{
		for (size_t j = 0; j < length; j++)
		{
			if (!(pic[i][j].getR() == pic[i][j].getG() && pic[i][j].getG() == pic[i][j].getB()))
			{
				return false;
			}
		}
	}
	return true;
}

bool Picture::isMonochrome() const
{
	for (size_t i = 0; i < width; i++) 
	{
		for (size_t j = 0; j < length; j++)
		{
			if (!((pic[i][j].getR() == 0 && pic[i][j].getG() == 0 && pic[i][j].getB() == 0) ||
				(pic[i][j].getR() == 255 && pic[i][j].getG() == 255 && pic[i][j].getB() == 255))) 
			{
				return false;
			}
		}
	}
	return true;
}

void Picture::print() const
{
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			pic[i][j].print();
		}
		std::cout << std::endl;
	}
}


size_t Picture::getWidth() const
{
	return width;
}

size_t Picture::getLength() const
{
	return length;
}

Pixel& Picture::getPixel(size_t i, size_t j) const
{
	return pic[i][j];
}