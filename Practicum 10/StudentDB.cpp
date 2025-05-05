#include "StudentDB.h"


void StudentDB::copyFrom(const StudentDB& other)
{
	capacity = other.capacity;
	size = other.size;
	students = new Student * [capacity] {nullptr};
	for (size_t i = 0; i < capacity; i++)
	{
		students[i] = other.students[i];
	}
}

void StudentDB::moveFrom(StudentDB&& other)
{
	capacity = other.capacity;
	size = other.size;

	students = other.students;
	other.students = nullptr;
}

void StudentDB::free()
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete students[i];
	}
	delete[] students;
}

void StudentDB::resize()
{
	size_t oldCap = capacity;
	capacity *= 2;

	Student** newStudents = new Student * [capacity] {nullptr};
	for (size_t i = 0; i < oldCap; i++)
	{
		newStudents[i] = students[i];
		students[i] = nullptr;
	}

	free();
	students = newStudents;
}


StudentDB::StudentDB() : students(nullptr), size(0), capacity(0) {}

StudentDB::StudentDB(const StudentDB& other)
{
	copyFrom(other);
}

StudentDB::StudentDB(StudentDB&& other) noexcept
{
	moveFrom(std::move(other));
}

StudentDB& StudentDB::operator=(const StudentDB& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

StudentDB& StudentDB::operator=(StudentDB&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

StudentDB::~StudentDB()
{
	free();
}

StudentDB::StudentDB(size_t n)
{
	students = new Student * [n] {nullptr};
	capacity = n;
	size = 0;
}


void StudentDB::add(const Student& toAdd)
{
	unsigned toAddFN = toAdd.getFN();
	size_t idx = capacity - 1;

	if (size == capacity)
	{
		resize();
		idx = size;
	}
	else
	{
		for (size_t i = 0; i < capacity; i++)
		{
			if (students[i]->getFN() == toAddFN)
			{
				throw std::invalid_argument("Student already in data base");
			}

			if (!students[i] && i < idx)
			{
				idx = i;
			}
		}
	}

	Student* toAddPtr = new Student(toAdd);
	students[idx] = toAddPtr;
	size++;
}

void StudentDB::remove(unsigned fn)
{
	int foundIDX = find(fn);

	if (foundIDX == -1)
	{
		throw std::invalid_argument("There is no student with such faculty number");
	}

	delete students[foundIDX];
	students[foundIDX] = nullptr;
	size--;
}

int StudentDB::find(unsigned fn) const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (students[i] && students[i]->getFN() == fn)
		{
			return i;
		}
	}
	return -1;
}

void StudentDB::display() const
{
	std::cout << "Students:" << std::endl;
	for (size_t i = 0; i < capacity; i++)
	{
		if (students[i])
		{
			students[i]->print();
			std::cout << std::endl;
		}
	}
}