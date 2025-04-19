#include "Book.h"

void Book::copyFrom(const Book& other)
{
	name = new char[strlen(other.name) + 1];
	author = new char[strlen(other.author) + 1];
	strcpy(name, other.name);
	strcpy(author, other.author);
	ID = other.ID;
	price = other.price;
	pubYear = other.pubYear;
}

void Book::free()
{
	delete[] name, author;
	author = name = nullptr;
	ID = 0;
	price = 0;
	pubYear = 0;
}


Book::Book() :author(nullptr), name(nullptr), price(0), pubYear(0), ID(0) {}

Book::Book(const Book& other)
{
	copyFrom(other);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Book::~Book()
{
	free();
}


void Book::setName(const char* newName)
{
	if (!newName)
	{
		return;
	}
	delete[] name;
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void Book::setAuthor(const char* newAuthor)
{
	if (!newAuthor)
	{
		return;
	}
	delete[] author;
	author = new char[strlen(newAuthor) + 1];
	strcpy(author, newAuthor);
}

void Book::setYear(unsigned newYear)
{
	if (newYear >= 0 && newYear <= 2025)
	{
		pubYear = newYear;
	}
}

void Book::setPrice(double newPrice)
{
	if (newPrice > 0)
	{
		price = newPrice;
	}
}

void Book::setID(unsigned newID)
{
	ID = newID;
}


const char* Book::getAuthor() const
{
	return author;
}

const char* Book::getName() const
{
	return name;
}

unsigned Book::getPubYear() const
{
	return pubYear;
}

unsigned Book::gedPrice() const
{
	return price;
}

unsigned Book::getID() const
{
	return ID;
}


Book::Book(const char* author, const char* name, unsigned pubYear, unsigned ID, double price) : Book()
{
	setAuthor(author);
	setName(name);
	setPrice(price);
	setID(ID);
	setYear(pubYear);
}


void Book::writeToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&ID, sizeof(ID));

	unsigned authorLen = strlen(author);
	ofs.write((const char*)&authorLen, sizeof(authorLen));
	ofs.write((const char*)author, authorLen * sizeof(char));

	unsigned nameLen = strlen(name);
	ofs.write((const char*)&nameLen, sizeof(nameLen));
	ofs.write((const char*)name, sizeof(char) * nameLen);

	ofs.write((const char*)&pubYear, sizeof(pubYear));

	ofs.write((const char*)&price, sizeof(price));
}

void Book::readFromBinaryFile(std::ifstream& ifs)
{
	unsigned authorLen;
	ifs.read((char*)&authorLen, sizeof(authorLen));
	author = new char[authorLen + 1];
	author[authorLen] = '\0';
	ifs.read(author, sizeof(char) * authorLen);

	unsigned nameLen;
	ifs.read((char*)&nameLen, sizeof(nameLen));
	name = new char[nameLen + 1];
	name[nameLen] = '\0';
	ifs.read(name, sizeof(char) * nameLen);

	ifs.read((char*)&price, sizeof(price));
	ifs.read((char*)&pubYear, sizeof(pubYear));
	ifs.read((char*)&ID, sizeof(ID));
}
