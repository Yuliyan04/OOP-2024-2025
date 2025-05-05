#pragma once
#include <iostream>

class Component
{
protected:

	char* tag;

public:

	Component();
	Component(const Component& other);
	Component(Component&& other) noexcept;
	Component& operator=(const Component& other);
	Component& operator=(Component&& other) noexcept;
	virtual ~Component();

	Component(const char* tag);

	virtual double price() const = 0;
	virtual void output(std::ostream& os) const = 0;

	virtual Component* clone() const = 0;

private:

	void copyFrom(const Component& other);
	void moveFrom(Component&& other);
	void free();
};

