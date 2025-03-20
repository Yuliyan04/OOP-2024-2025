#include <iostream>
#include <fstream>


const size_t MAX_NAME_SIZE = 32;
const size_t MIN_AGE = 18;
const size_t MAX_AGE = 90;
const size_t MIN_SALARY = 2500;
const size_t MAX_SALARY = 5000;
const size_t MAX_PROGRAMMERS = 50;
const size_t MAX_COLS = 100;
const size_t MAX_ROWS = 100;

enum class ProgrammingLanguage
{
    Cpp = 1,
    Python = 2,
    Java = 4,
    Csharp = 8,
    Javascript = 16
};

const char* LanguageToString(ProgrammingLanguage lang)
{
    switch (lang)
    {
    case ProgrammingLanguage::Cpp : return "Cpp";
    case ProgrammingLanguage::Python: return "Python";
    case ProgrammingLanguage::Java: return "Java";
    case ProgrammingLanguage::Csharp: return "Csharp";
    case ProgrammingLanguage::Javascript: return "Javascript";
    }
}

void printLanguages(char langs)
{
    for (int i = 0; i <= 4; i++)
    {
        int mask = 1;
        mask = mask << i;
        if ((mask & langs) != 0)
        {
            std::cout << LanguageToString((ProgrammingLanguage)mask) << " ";
        }
    }
}

class Programmer
{
    char name[MAX_NAME_SIZE + 1];
    int age;
    int salary;
    char languages;

    bool validate(int toSet, int upperBound, int lowerBound)
    {
        if (toSet >= lowerBound && toSet <= upperBound)
        {
            return true;
        }
        return false;
    }

    void setName(const char* name)
    {
        if (!name)
        {
            return;
        }

        int nameLen = strlen(name);
        if (nameLen > 0 && nameLen <= MAX_NAME_SIZE)
        {
            strcpy(this->name, name);
        }

        return;
    }

    void setAge(int age)
    {
        if (validate(age, MAX_AGE, MIN_AGE))
        {
            this->age = age;
        }
        return;
    }

    void setMask(char mask)
    {
        if (mask > 0 && mask < 32)
        {
            languages = mask;
        }
        return;
    }

public:

    Programmer() : age(0), salary(0), languages(1) 
    {
        strcpy(name, " ");
    }

    Programmer(const char* name, int age, int salary, char languagesMask) : Programmer()
    {
        setName(name);
        setAge(age);
        setSalary(salary);
        setMask(languagesMask);
    }

    void setSalary(int salary)
    {
        if (validate(salary, MAX_SALARY, MIN_SALARY))
        {
            this->salary = salary;
        }
        return;
    }

    void addLanguages(ProgrammingLanguage lang)
    {
        this->languages |= (int)lang;
    }

    bool canWork(ProgrammingLanguage lang) const
    {
        int mask = (int)lang;
        mask = mask & this->languages;

        return mask != 0;
    }

    void printProgrammer() const
    {
        std::cout << name << " " << age << " " << salary << " ";
        printLanguages(this->languages);
    }

    char getLanguage() const
    {
        return languages;
    }

    int getSalary() const
    {
        return salary;
    }

    unsigned getAge() const
    {
        return age;
    }

    void changeSalary(unsigned (*formula)(unsigned))
    {
        salary = formula(salary);
    }
};


class SoftwareCompany
{
    Programmer programmers[MAX_PROGRAMMERS];
    unsigned count;

public:
    SoftwareCompany() :count(0) {};

    void addProgrammer(const Programmer& p)
    {
        if (count >= MAX_PROGRAMMERS)
        {
            return;
        }

        programmers[count] = p;
        count++;
    }

    unsigned getProgrammersCount() const
    {
        return count;
    }

    void printProgrammers() const
    {
        for (size_t i = 0; i < count; i++)
        {
            programmers[i].printProgrammer();
        }
    }

    void printProgramistLan(ProgrammingLanguage lang) const
    {
        for (size_t i = 0; i < count; i++)
        {
            if (((int)lang & programmers[i].getLanguage()) != 0)
            {
                programmers[i].printProgrammer();
            }
        }
    }

    double averageSalary() const
    {
        double res = 0;
        for (size_t i = 0; i < count; i++)
        {
            res += programmers[i].getSalary();
        }
        res /= count;
        return res;
    }

    double averageAge() const
    {
        double res = 0;
        for (size_t i = 0; i < count; i++)
        {
            res += programmers[i].getAge();
        }
        res /= count;
        return res;
    }
};


//Task 3
class MatrixFile
{
    int matrix[MAX_ROWS][MAX_COLS];
    unsigned rowsCount;
    unsigned colsCount;
    char* filename;

public:

    MatrixFile() : rowsCount(0), colsCount(0), filename(nullptr)
    {
        for (size_t i = 0; i < MAX_ROWS; i++)
        {
            for (size_t j = 0; j < MAX_COLS; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    MatrixFile(const char* filename) : MatrixFile()
    {
        if (!filename)
        {
            return;
        }

        std::ifstream file(filename);
        if (!file.is_open())
        {
            return;
        }

        this->filename = new char[strlen(filename) + 1];
        strcpy(this->filename, filename);

        file >> rowsCount >> colsCount;
        for (size_t i = 0; i < rowsCount; i++)
        {
            for (size_t j = 0; j < colsCount; j++)
            {
                file >> matrix[i][j];
            }
        }

        file.close();
    }

    void printMatric() const
    {
        for (size_t i = 0; i < rowsCount; i++)
        {
            for (size_t j = 0; j < colsCount; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    ~MatrixFile()
    {
        delete[] filename;
    }

    void transponate()
    {
        for (size_t i = 0; i < rowsCount; i++)
        {
            for (size_t j = i + 1; j < colsCount    ; j++)
            {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    void multiplyBy(int num)
    {
        for (size_t i = 0; i < rowsCount; i++)
        {
            for (size_t j = 0; j < colsCount; j++)
            {
                matrix[i][j] *= num;
            }
        }
    }

    void change(int val, int x, int y)
    {
        if (x >= 0 && x < rowsCount && y >= 0 && y < colsCount)
        {
            matrix[x][y] = val;
        }
    }

    void saveToFile() const
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            return;
        }

        file << std::endl;

        for (size_t i = 0; i < rowsCount; i++)
        {
            for (size_t j = 0; j < colsCount; j++)
            {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }

        file.close();
    }
};



//Task 4

const size_t BRAND_NAME = 100;
const size_t MODEL_NAME = 100;
const double down = 0.001;
const size_t CARS = 1000;
const double e = 0.0000000001;

enum class EngineType
{
    GASOLINE,
    DIESEL,
    ELECTRICITY,
    UNKNOWN
};

const char* typeToStr(EngineType type)
{
    switch (type)
    {
    case EngineType::GASOLINE:return "Gasoline";
    case EngineType::DIESEL:return "Diesel";
    case EngineType::ELECTRICITY:return "Electricity";
    case EngineType::UNKNOWN:return "Unknown";
    }
}


class Car
{
    char brand[BRAND_NAME];
    char model[MODEL_NAME];
    EngineType engineType;
    bool isUsed;
    unsigned mileage;
    double price;

    bool validateString(const char* str, unsigned upperBound)
    {
        if (!str)
        {
            return false;
        }

        unsigned len = strlen(str);

        if (len > 0 && len <= upperBound)
        {
            return true;
        }

        return false;
    }

    void setModel(const char* model)
    {
        if (validateString(model, MODEL_NAME))
        {
            strcpy(this->model, model);
        }
        return;
    }

    void setBrand(const char* brand)
    {
        if (validateString(brand, BRAND_NAME))
        {
            strcpy(this->brand, brand);
        }
        return;
    }
    
public:

    Car() : engineType(EngineType::UNKNOWN), mileage(0), price(0), isUsed(false) {};
    Car(const char* model, const char* brand, EngineType type, unsigned price) : Car()
    {
        setBrand(brand);
        setModel(model);
        engineType = type;
        this->price = price;
    }

    void printCar() const
    {
        std::cout << brand << " " << model << " " << price << " " << mileage;
        if (isUsed)
        {
            std::cout << "Used" << " ";
        }
        else
        {
            std::cout << "New" << " ";
        }
        
        std::cout << typeToStr(engineType) << std::endl;
    }

    void drive(unsigned kilometers)
    {
        mileage += kilometers;
        isUsed = true;
        price -= (price * down);
    }

    EngineType getType() const
    {
        return engineType;
    }

    const char* getModel() const
    {
        return model;
    }

    double getPrice() const
    {
        return price;
    }

    const char* getBrand() const
    {
        return brand;
    }
};


class CarDealership
{
    Car cars[CARS];
    unsigned count;

public:

    CarDealership() :count(0) {};
    CarDealership(const Car* cars, size_t size) : CarDealership()
    {
        if (!cars)
        {
            return;
        }

        this->count = size;
        for (size_t i = 0; i < size; i++)
        {
            this->cars[i] = cars[i];
        }
    }

    CarDealership(const Car* cars, size_t size, EngineType type) : CarDealership()
    {
        if (!cars)
        {
            return;
        }

        for (size_t i = 0; i < size; i++)
        {
            if (cars[i].getType() == type)
            {
                this->cars[count] = cars[i];
                count++;
            }
        }
    }

    CarDealership(const Car* cars, size_t size, const char* model) : CarDealership()
    {
        if (!cars || !model)
        {
            return;
        }

        for (size_t i = 0; i < size; i++)
        {
            if (strcmp(cars[i].getModel(), model) == 0)
            {
                this->cars[count] = cars[i];
                count++;
            }
        }
    }

    unsigned getCarsCount() const
    {
        return count;
    }

    void addCar(const Car& other)
    {
        if (count >= CARS)
        {
            return;
        }

        cars[count] = other;
        count++;
    }

    void removeCar(const char* model, const char* brand)
    {
        if (!model || !brand)
        {
            return;
        }

        int ind = count;
        for (size_t i = 0; i < count; i++)
        {
            if (strcmp(brand, cars[i].getBrand()) == 0 && strcmp(model, cars[i].getModel()) == 0)
            {
                ind = i;
                break;
            }
        }

        if (ind == count)
        {
            return;
        }

        for (size_t i = ind; i < count - 1; i++)
        {
            cars[i] = cars[i + 1];
        }
        count--;
    }

    void testDrive()
    {
        for (size_t i = 0; i < count; i++)
        {
            cars[i].drive(1);
        }
    }

    void printCarByModel(const char* model)
    {
        if (!model)
        {
            return;
        }

        for (size_t i = 0; i < count; i++)
        {
            if (strcmp(cars[i].getModel(), model) == 0)
            {
                cars[i].printCar();
            }
        }
    }

    Car getMostExpensive() const
    {
        double max = 0;
        Car car;

        for (size_t i = 0; i < count; i++)
        {
            if (cars[i].getPrice() - max > e)
            {
                max = cars[i].getPrice();
                car = cars[i];
            }
        }

        return car;
    }

    double getAverage(const Car& car)
    {
        double avgCnt = 0;
        double res = 0;

        for (size_t i = 0; i < count; i++)
        {
            if (strcmp(cars[i].getBrand(), car.getBrand()) == 0)
            {
                avgCnt++;
                res += cars[i].getPrice();
            }
        }

        avgCnt > 0 ? res / avgCnt : 0;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
