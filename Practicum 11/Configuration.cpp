#include "Configuration.h"


void Configuration::copyFrom(const Configuration& other)
{
	capacity = other.capacity;
	components = new Component * [capacity] {nullptr};
	size = other.size;
	for (size_t i = 0; i < size; i++)
	{
		components[i] = other.components[i]->clone();
	}
}

void Configuration::moveFrom(Configuration&& other)
{
	capacity = other.capacity;
	size = other.size;
	components = other.components;
	other.components = nullptr;
}

void Configuration::free()
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete components[i];
	}
	delete[] components;
}

void Configuration::resize(size_t newCap)
{
	Component** newComps = new Component * [newCap] {nullptr};
	for (size_t i = 0; i < size; i++)
	{
		newComps[i] = components[i];
		components[i] = nullptr;
	}
	
	free();
	capacity = newCap;
	components = newComps;
}


Configuration::Configuration() : components(nullptr), capacity(0), size(0) {}

Configuration::Configuration(const Configuration& other)
{
	copyFrom(other);
}

Configuration::Configuration(Configuration&& other) noexcept
{
	moveFrom(std::move(other));
}

Configuration& Configuration::operator=(const Configuration& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Configuration& Configuration::operator=(Configuration&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Configuration::~Configuration()
{
	free();
}


Configuration::Configuration(size_t n)
{
	components = new Component * [n] {nullptr};
	size = 0;
	capacity = n;
}


void Configuration::insert(Component* component)
{
	if (!component)
	{
		throw std::invalid_argument("Component can't be nullptr");
	}

	if (size == capacity)
	{
		resize(capacity * 2);
	}

	components[size] = component;
	component = nullptr;
	size++;
}

double Configuration::price() const
{
	double sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		sum += components[i]->price();
	}
	return sum;
}

size_t Configuration::getSize() const
{
	return size;
}


Component*& Configuration::operator[](size_t idx)
{
	return components[idx];
}

const Component*& Configuration::operator[](size_t idx) const
{
	return components[idx];
}

std::ostream& operator<<(std::ostream& os, const Configuration& config)
{
	for (size_t i = 0; i < config.getSize(); i++)
	{
		config[i]->output(os);
	}
	return os;
}