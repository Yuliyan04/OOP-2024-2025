#include "Animal.h"


void Animal::copyFrom(const Animal& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	age = other.age;
	kind = other.kind;
}

void Animal::free()
{
	delete[] name;
	name = nullptr;
	age = 0;
	kind = Kind::unknown;
}


Animal::Animal() :name(nullptr), age(0), kind(Kind::unknown) {};

Animal::Animal(const Animal& other) : Animal()
{
	if (this != &other)
	{
		copyFrom(other);
	}
}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Animal::~Animal()
{
	free();
}

const char* Animal::getName() const
{
	return name;
}

Kind Animal::getKind() const
{
	return kind;
}

unsigned Animal::getAge() const
{
	return age;
}

void Animal::setName(const char* name)
{
	if (!name)
	{
		return;
	}

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Animal::setKind(Kind kind)
{
	if (kind != Kind::unknown)
	{
		this->kind = kind;
	}
}

void Animal::setAge(unsigned age)
{
	if (age >= 0 && age <= 200)
	{
		this->age = age;
	}
}

void Animal::saveAnimal(std::ostream& file) const
{
	file << name << " " << (int)kind << age << std::endl;
}