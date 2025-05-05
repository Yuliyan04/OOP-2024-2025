#pragma once
#include "Component.h"
#include "CPU.h"
#include "Memory.h"


class Configuration
{
	Component** components;
	size_t size;
	size_t capacity;

public:

	Configuration();
	Configuration(const Configuration& other);
	Configuration(Configuration&& other) noexcept;
	Configuration& operator=(const Configuration& other);
	Configuration& operator=(Configuration&& other) noexcept;
	~Configuration();

	Configuration(size_t n);

	void insert(Component* component);
	double price() const;
	size_t getSize() const;

	Component*& operator[](size_t idx);
	const Component*& operator[](size_t idx) const;

	friend std::ostream& operator<<(std::ostream& os, const Configuration& config);

private:

	void copyFrom(const Configuration& other);
	void moveFrom(Configuration&& other);
	void free();
	void resize(size_t newCap);
};

