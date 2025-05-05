#include "Component.h"


void Component::copyFrom(const Component& other)
{
	tag = new char[strlen(other.tag) + 1];
	strcpy(tag, other.tag);
}

void Component::moveFrom(Component&& other)
{
	tag = other.tag;
	tag = nullptr;
}

void Component::free()
{
	delete[] tag;
	tag = nullptr;
}


Component::Component() : tag(nullptr) {}

Component::Component(const Component& other)
{
	copyFrom(other);
}

Component::Component(Component&& other) noexcept
{
	moveFrom(std::move(other));
}

Component& Component::operator=(const Component& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Component& Component::operator=(Component&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Component::~Component()
{
	free();
}


Component::Component(const char* tag)
{
	if (!tag)
	{
		throw std::invalid_argument("Tag can't be nullptr");
	}

	this->tag = new char[strlen(tag) + 1];
	strcpy(this->tag, tag);
}