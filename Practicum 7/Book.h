#pragma once
#include <iostream>
#include <fstream>


class Book
{
	unsigned ID;
	char* name;
	char* author;
	unsigned pubYear;
	double price;

public:

	Book();
	Book(const Book& other);
	Book& operator=(const Book& other);
	~Book();

	Book(const char* author, const char* name, unsigned pubYear, unsigned ID, double price);

	void setName(const char* newName);
	void setAuthor(const char* newAuthor);
	void setYear(unsigned newYear);
	void setPrice(double newPrice);
	void setID(unsigned newID);
	
	const char* getAuthor() const;
	const char* getName() const;
	unsigned getPubYear() const;
	unsigned gedPrice() const;
	unsigned getID() const;

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);

private:

	void copyFrom(const Book& other);
	void free();
};

