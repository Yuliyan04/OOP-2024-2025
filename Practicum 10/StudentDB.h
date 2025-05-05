#pragma once
#include "Student.h"


class StudentDB
{
protected:

	Student** students;
	size_t size;
	size_t capacity;

public:

	StudentDB();
	StudentDB(const StudentDB& other);
	StudentDB(StudentDB&& other) noexcept;
	StudentDB& operator=(const StudentDB& other);
	StudentDB& operator=(StudentDB&& other) noexcept;
	~StudentDB();

	StudentDB(size_t n);

	void add(const Student& toAdd);
	void remove(unsigned fn);
	int find(unsigned fn) const;
	void display() const;

private:

	void copyFrom(const StudentDB& other);
	void moveFrom(StudentDB&& other);
	void free();
	void resize();
};