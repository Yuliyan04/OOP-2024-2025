#include <iostream>


//Task 1
struct Point
{
    int x;
    int y;
};

struct Triangle
{
    int id;
    Point A;
    Point B;
    Point C;

    double S;
};

void insertionSort(Triangle* triangles, int N)
{
    for (int i = 1; i < N; i++)
    {
        Triangle toIns = triangles[i];
        int j = i - 1;

        while (j >= 0 && triangles[j].S > toIns.S)
        {
            triangles[j + 1] = triangles[j];
            j--;
        }
        triangles[j + 1] = toIns;
    }
}

int main()
{
    int N;
    std::cin >> N;
    Triangle* triangles = new Triangle[N];

    for (int i = 0; i < N; i++)
    {
        Point A, B, C;
        std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
        triangles[i].A = A;
        triangles[i].B = B;
        triangles[i].C = C;
        triangles[i].id = i + 1;
        triangles[i].S = std::abs(A.x * B.y + B.x * C.y + C.x * A.y - (A.y * B.x + B.y * C.x + C.y * A.x));
    }

    insertionSort(triangles, N);

    for (int i = 0; i < N; i++)
    {
        triangles[i].S /= 2.0;
        std::cout << i + 1 << " " << triangles[i].id << triangles[i].S << std::endl;
    }

    delete[] triangles;
    return 0;
}



//Task 2

struct Complex
{
    int Re;
    int Im;

    Complex operator+(const Complex& other) const
    {
        Complex res;
        res.Re = Re + other.Re;
        res.Im = Im + other.Im;
        return res;
    }

    Complex operator-(const Complex& other) const
    {
        Complex res;
        res.Re = Re - other.Re;
        res.Im = Im - other.Im;
        return res;
    }

    Complex operator*(const Complex& other) const
    {
        Complex result;
        result.Re = Re * other.Re - Im * other.Im;  
        result.Im = Re * other.Im + Im * other.Re;
        return result;
    }

    Complex operator/(const Complex& other) const
    {
        Complex result;
        int denominator = other.Re * other.Re + other.Im * other.Im; 

        if (denominator == 0)
        {
            std::cout << "Error: Division by zero!" << std::endl;
            return Complex{ 0, 0 };
        }

        result.Re = (Re * other.Re + Im * other.Im) / denominator;  
        result.Im = (Im * other.Re - Re * other.Im) / denominator;
        return result;
    }

    bool isReal()
    {
        return Im == 0;
    }
};



constexpr size_t TITLE_SIZE = 64;
constexpr size_t AUTHOR_SIZE = 32;
constexpr size_t LIBRARY_NAME = 32;
constexpr size_t BOOKS_COUNT = 10;


enum class Status
{
    Available,
    Borrowed,
    Reserved,
    Unknown
};

struct Book
{
    char title[TITLE_SIZE];
    char author[AUTHOR_SIZE];
    int publicationYear;
    Status status = Status::Unknown;
};

struct Library
{
    char name[LIBRARY_NAME];
    Book books[BOOKS_COUNT];
    int booksCount = 0;
};

void printStatus(Status state)
{
    switch (state)
    {
        case Status::Available:std::cout << "Available " << std::endl; break;
        case Status::Borrowed:std::cout << "Borrowed " << std::endl; break;
        case Status::Reserved:std::cout << "Reserved " << std::endl; break;
        case Status::Unknown:std::cout << "Unknown status... " << std::endl; break;
    }
}

void addBook(Library& lib, const char* title, const char* author, int pubYear)
{
    if (std::strlen(title) > TITLE_SIZE || std::strlen(author) > AUTHOR_SIZE)
    {
        std::cout << "Too large title or author name..." << std::endl;
        return;
    }

    if (lib.booksCount >= BOOKS_COUNT)
    {
        std::cout << "Can't add a new book. The library is full. ";
        return;
    }

    Book newBook;
    std::strcpy(newBook.title, title);
    std::strcpy(newBook.author, author);
    newBook.publicationYear = pubYear;
    newBook.status = Status::Available;

    lib.books[lib.booksCount] = newBook;
    lib.booksCount++;
}

void borrowBook(Book& book)
{
    if (book.status == Status::Borrowed)
    {
        return;
    }
    book.status = Status::Borrowed;
}

void reserveBook(Book& book)
{
    if (book.status == Status::Reserved)
    {
        return;
    }
    book.status = Status::Reserved;
}

void printLibrary(const Library& lib)
{
    std::cout << "Books in " << lib.name << ": " << std::endl;

    for (int i = 0; i < lib.booksCount; i++)
    {
        std::cout << "Title: " << lib.books[i].title << std::endl;
        std::cout << "Author: " << lib.books[i].author << std::endl;
        std::cout << "Publication year: " << lib.books[i].publicationYear << std::endl;
        std::cout << "Book status: ";
        printStatus(lib.books[i].status);

        std::cout << std::endl << std::endl;
    }
}
