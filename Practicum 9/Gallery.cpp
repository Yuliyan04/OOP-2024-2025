#include "Gallery.h"


void Gallery::copyFrom(const Gallery& other)
{
	capacity = other.capacity;
	size = other.size;

	pics = new Picture * [capacity] {nullptr};
	for (size_t i = 0; i < size; i++)
	{
		pics[i] = new Picture(*other.pics[i]);
	}
}

void Gallery::moveFrom(Gallery&& other)
{
	capacity = other.capacity;
	size = other.size;

	pics = other.pics;
	other.pics = nullptr;
}

void Gallery::free()
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete pics[i];
	}
	delete[] pics;
}

void Gallery::resize()
{
	capacity *= 2;
	Picture** newPics = new Picture * [capacity] {nullptr};
	for (size_t i = 0; i < size; i++)
	{
		newPics[i] = pics[i];
		pics[i] = nullptr;
	}

	free();
	pics = newPics;
}


Gallery::Gallery() : pics(nullptr), size(0), capacity(0) {}

Gallery::Gallery(const Gallery& other)
{
	copyFrom(other);
}

Gallery::Gallery(Gallery&& other)
{
	moveFrom(std::move(other));
}

Gallery& Gallery::operator=(const Gallery& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Gallery& Gallery::operator=(Gallery&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Gallery::~Gallery()
{
	free();
}


void Gallery::addPicture(const Picture& toAdd)
{
	if (size == capacity) resize();

	size_t idx = size;
	for (size_t i = 0; i < size; i++)
	{
		if (!pics[i])
		{
			idx = i;
			break;
		}
	}

	Picture* picPtr = new Picture(toAdd);
	pics[idx] = picPtr;

	if (idx == size) size++;
}

void Gallery::removePicture(size_t idx)
{
	pics[idx]->~Picture();
	pics[idx] = nullptr;

	if (idx == size - 1) size--;
}

void Gallery::applyFilterForPicture(Filter filter, size_t idx)
{
	Picture* pic = pics[idx];
	for (size_t i = 0; i < pic->getWidth(); i++)
	{
		for (size_t j = 0; j < pic->getLength(); j++)
		{
			pic->getPixel(i, j).setR(pic->getPixel(i, j).getR() & (uint8_t)filter);
			pic->getPixel(i, j).setG(pic->getPixel(i, j).getG() & (uint8_t)filter);
			pic->getPixel(i, j).setB(pic->getPixel(i, j).getB() & (uint8_t)filter);
		}
	}
}

void Gallery::applyFilter(Filter filter)
{
	for (size_t i = 0; i < size; i++)
	{
		if (pics[i]) applyFilterForPicture(filter, i);
	}
}


const Picture* Gallery::operator[](size_t idx) const
{
	return pics[idx];
}

Picture* Gallery::operator[](size_t idx)
{
	return pics[idx];
}


void Gallery::print() const
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "Picture: " << i + 1 << std::endl;
		if (pics[i])
		{
			pics[i]->print();
		}
		std::cout << std::endl;
	}
}