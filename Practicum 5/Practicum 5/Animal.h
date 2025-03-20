#pragma once
#include <iostream>

enum class Kind
{
	mammal,
	reptile,
	fish,
	bird,
	amphibian,
	ivertebrates,
	insect,
	unknown
};

class Animal
{
	char* name;
	Kind kind;
	unsigned age;

public:

	Animal();
	Animal(const Animal& other);
	Animal& operator=(const Animal& other);
	~Animal();

	const char* getName() const;
	Kind getKind() const;
	unsigned getAge() const;

	void setName(const char* name);
	void setKind(Kind kind);
	void setAge(unsigned age);

	void saveAnimal(std::ostream& file) const;

private:

	void copyFrom(const Animal& other);
	void free();
};

