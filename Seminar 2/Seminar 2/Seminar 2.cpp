#include <iostream>
#include <fstream>


//Task 1

size_t fileSize(std::ifstream& ifs)
{
    size_t currPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(currPos);

    return size;
}


//Task 2

size_t symbolsCount(std::ifstream& file, char c)
{
    size_t currPos = file.tellg();
    file.seekg(0, std::ios::beg);

    int count = 0;
    while (true)
    {
        char curr = file.get();

        if (file.eof())
        {
            break;
        }

        if (curr == c)
        {
            count++;
        }
    }
    file.seekg(currPos);
    file.clear();

    return count;
}

size_t getRowsCount(const char* filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return 0;
    }

    size_t rows = symbolsCount(ifs, '\n');
    return rows;
}

size_t rowsCount(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return 0;
    }


}

//Task

constexpr size_t STUDENT_NAME_SIZE = 50;
constexpr size_t FACULTY_NUMBER_SIZE = 10;
constexpr size_t MAX_STUDENTS_COUTNT = 50;

struct Student
{
    char name[STUDENT_NAME_SIZE + 1];
    char fn[FACULTY_NUMBER_SIZE + 1];
    double grade;
};

struct StudentsTable
{
    Student students[MAX_STUDENTS_COUTNT];
    int count = 0;
};


StudentsTable readStudents(const char* filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cout << "File can't be open" << std::endl;
        return {};
    }

    StudentsTable table;

    char buff[1024];
    ifs.getline(buff, 1024);
    ifs.getline(buff, 1024);
}


//Task 4

namespace CONSTANTS
{
    constexpr size_t FN_SIZE = 10;
}

struct Student
{
    char* name;
    char fn[CONSTANTS::FN_SIZE];
    char* email;
};

Student* getStudents(const char* filename, size_t& studentsCount)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return nullptr;
    }

    file >> studentsCount;

    Student* students = new Student[studentsCount];
    size_t studentInd = 0;

    for (size_t i = 0; i < studentsCount; i++)
    {
        Student curr;

        size_t nameSize;
        file >> nameSize;
        curr.name = new char[nameSize + 1];
        file >> curr.name;

        file >> curr.fn;

        size_t emailSize;
        file >> emailSize;
        curr.email = new char[emailSize + 1];
        file >> curr.email;

        students[studentInd] = curr;
        studentInd++;
    }

    file.close();
    return students;
}

void saveStudents(const char* filename, const Student*& students, size_t studentsSize)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return;
    }

    ofs << studentsSize << std::endl;
    
    for (int i = 0; i < studentsSize; i++)
    {
        ofs << strlen(students[i].name) << " " << students[i].name << std::endl;
        delete[] students[i].name;

        ofs << students[i].fn << std::endl;

        ofs << strlen(students[i].email) << " " << students[i].email << std::endl;
        delete[] students[i].email;
    }

    delete[] students;
    ofs.close();
}


//TASK 5

Student readStudentBinary(std::fstream& file)
{
    Student curr;

    size_t nameSize;
    file.read((char*)&nameSize, sizeof(nameSize));
    curr.name = new char[nameSize + 1];
    curr.name[nameSize] = '\0';
    file.read(curr.name, nameSize * sizeof(char));

    file.read(curr.fn, CONSTANTS::FN_SIZE);

    size_t emailSize;
    file.read((char*)&emailSize, sizeof(emailSize));
    curr.email = new char[emailSize + 1];
    curr.email[emailSize] = '\0';
    file.read(curr.email, emailSize);

    return curr;
}

Student* readStudentsBinary(const char* filename, size_t& studentsCount)
{
    std::fstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return {};
    }

    file.read((char*)&studentsCount, sizeof(studentsCount));

    Student* students = new Student[studentsCount];

    for (size_t i = 0; i < studentsCount; i++)
    {
        students[i] = readStudentBinary(file);
    }

    return students;
}

void saveStudentBinary(std::fstream& file, const Student& student)
{
    size_t nameLen = strlen(student.name);
    file.write((const char*)&nameLen, sizeof(nameLen));
    file.write(student.name, nameLen * sizeof(char));

    file.write(student.fn, CONSTANTS::FN_SIZE);

    size_t emailSize = strlen(student.email);
    file.write((const char*)&emailSize, sizeof(emailSize));
    file.write(student.email, emailSize);
}

void saveStudentsBinary(const char* filename, const Student*& students, size_t studentsCount)
{
    std::fstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return;
    }

    file.write((const char*)&studentsCount, sizeof(studentsCount));

    for (size_t i = 0; i < studentsCount; i++)
    {
        saveStudentBinary(file, students[i]);
    }
}

void freeStudents(const Student*& students, size_t studentsCount)
{
    for (size_t i = 0; i < studentsCount; i++)
    {
        delete[] students[i].name;
        delete[] students[i].email;
    }

    delete[] students;
}

Student* removeStudent(const Student*& students, size_t& studentsCount, const char* fn)
{
    Student* res = new Student[studentsCount - 1];
    int ind = 0;
    bool studentFound = false;

    for (size_t i = 0; i < studentsCount; i++)
    {
        if (strcmp(students[i].fn, fn) == 0)
        {
            studentFound = true;
            continue;
        }
        else
        {
            res[ind] = students[i];
            ind++;
        }
    }

    if (!studentFound)  // If the student was not found
    {
        std::cout << "Student not found" << std::endl;
        delete[] res;
        return nullptr;
    }

    freeStudents(students, studentsCount);

    studentsCount--;
    return res;
}

Student* addStudent(const Student*& students, const Student& student, size_t& studentsCount)
{
    Student* res = new Student[studentsCount + 1];

    for (int i = 0; i < studentsCount; i++)
    {
        res[i] = students[i];
    }

    freeStudents(students, studentsCount);

    res[studentsCount] = student;
    studentsCount++;

    return res;
}

Student searchByFn(const Student*& students, size_t studentsSize, const char* fn)
{
    for (int i = 0; i < studentsSize; i++)
    {
        if (strcmp(students[i].fn, fn) == 0)
        {
            return students[i];
        }
    }

    std::cout << "There isn't any student with that faculty number..." << std::endl;
    return {};
}

void changeEmailByFN(Student*& students, size_t studentsSize, const char* fn, const char* email)
{
    for (int i = 0; i < studentsSize; i++)
    {
        if (strcmp(students[i].fn, fn) == 0)
        {
            delete[] students[i].email;
            students[i].email = new char[strlen(email) + 1];
            strcpy(students[i].email, email);
            return;
        }
    }

    std::cout << "There isn't any student with that faculty number..." << std::endl;
    return;
}

void changeNameByFN(Student*& students, size_t studentsSize, const char* fn, const char* name)
{
    for (int i = 0; i < studentsSize; i++)
    {
        if (strcmp(students[i].fn, fn) == 0)
        {
            delete[] students[i].name;
            students[i].name = new char[strlen(name) + 1];
            strcpy(students[i].name, name);
            return;
        }
    }

    std::cout << "There isn't any student with that faculty number..." << std::endl;
    return;
}


//Task 3

constexpr int lineSize = 1024;

int main()
{
    const char filename[] = "Seminar 2.cpp";
    std::ifstream ifs(filename);

    if (!ifs.is_open())
    {
        return 1;
    }

    while (!ifs.eof())
    {
        char buff[lineSize];
        ifs.getline(buff, lineSize);

        std::cout << buff << std::endl;
    }

    return 0;
}