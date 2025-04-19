#pragma once
#include "Picture.h"


enum class Filter
{
	some,
	filters
};


class Gallery
{
	Picture** pics;
	size_t size;
	size_t capacity;

public:

	Gallery();
	Gallery(const Gallery& other);
	Gallery(Gallery&& other) noexcept;
	Gallery& operator=(const Gallery& other);
	Gallery& operator=(Gallery&& other) noexcept;
	~Gallery();

	void addPicture(const Picture& toAdd);
	void removePicture(size_t idx);
	void applyFilterForPicture(Filter filter, size_t idx);
	void applyFilter(Filter filter);

	const Picture* operator[](size_t idx) const;
	Picture* operator[](size_t idx);

	void print() const;

private:

	void copyFrom(const Gallery& other);
	void moveFrom(Gallery&& other);
	void free();
	void resize();
};

