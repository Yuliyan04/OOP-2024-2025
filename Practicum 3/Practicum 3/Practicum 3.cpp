#include <iostream>
#include <fstream>

namespace CONSTANTS
{
    const size_t NAME_LEN = 50;
    const size_t JEDI_MAX_COUNT = 100;
    const double e = 0.000000000000001;
    const size_t COLORS_COUNT = 5;
    const size_t TYPES_COUNT = 3;
}

enum class Color
{
    RED, 
    YELLOW, 
    GREEN, 
    BLUE, 
    PURPLE
};

enum class Type
{
    SINGLEBLADED, 
    DOUBLE_BLADED, 
    CROSSGUARD
};

struct LightSaber
{
    Type type;
    Color color;
};

struct Jedi
{
    char name[CONSTANTS::NAME_LEN + 1];
    unsigned age;
    unsigned power;
    LightSaber lightSaber;
};

struct JediCollection
{
    Jedi jedies[CONSTANTS::JEDI_MAX_COUNT];
    unsigned count = 0;
};


Jedi createJedi(const char* name, unsigned age, unsigned power, const LightSaber& lightSaber)
{
    if (!name)
    {
        return {};
    }

    Jedi res;
    strcpy(res.name, name);
    res.age = age;
    res.power = power;
    res.lightSaber = lightSaber;

    return res;
}

Jedi createJedi(const char* name, unsigned age, unsigned power, Color color, Type type)
{
    if (!name)
    {
        return {};
    }

    Jedi res;
    strcpy(res.name, name);
    res.age = age;
    res.power = power;

    LightSaber saber;
    saber.color = color;
    saber.type = type;

    res.lightSaber = saber;

    return res;
}

void addJedi(JediCollection& collection, const Jedi& jedi)
{
    if (collection.count >= CONSTANTS::JEDI_MAX_COUNT)
    {
        return;
    }

    collection.jedies[collection.count] = jedi;
    collection.count++;
}

int findJediIndex(const char* name, const JediCollection& collection)
{
    if (!name)
    {
        return -1;
    }

    for (size_t i = 0; i < collection.count; i++)
    {
        if (strcmp(collection.jedies[i].name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}

void removeJediByName(JediCollection& collection, const char* jediName)
{
    if (!jediName)
    {
        return;
    }

    int idx = findJediIndex(jediName, collection);

    if (idx < 0)
    {
        return;
    }

    for (int i = idx; i < collection.count - 1; i++)
    {
        collection.jedies[i] = collection.jedies[i + 1];
    }
}

void saveCollectionToBinaryFile(const char* filename, const JediCollection& collection)
{
    if (!filename)
    {
        return;
    }

    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open())
    {
        return;
    }

    file.write((const char*)&collection, sizeof(collection));
    file.close();
}

JediCollection readCollectionFromBinaryFile(const char* filename)
{
    if (!filename)
    {
        return {};
    }

    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        return {};
    }

    JediCollection collection;
    file.read((char*)&collection, sizeof(collection));
    
    file.close();
    return collection;
}

void saveLightSaberToTXT(const LightSaber& lightSaber, std::ostream& ofs)
{
    ofs << (int)lightSaber.color << ", " << (int)lightSaber.type;
}

void saveJediToTXT(const Jedi& jedi, std::ostream& ofs)
{
    ofs << jedi.name << ", " << jedi.age << ", " << jedi.power << ", ";
    saveLightSaberToTXT(jedi.lightSaber, ofs);
    ofs << std::endl;
}

void saveCollectionToTXT(const char* filename, const JediCollection& collection)
{
    if (!filename)
    {
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    file << collection.count << std::endl;

    for (size_t i = 0; i < collection.count; i++)
    {
        saveJediToTXT(collection.jedies[i], file);
    }

    file.close();
}

void printCollection(const JediCollection& collection)
{
    for (size_t i = 0; i < collection.count; i++)
    {
        saveJediToTXT(collection.jedies[i], std::cout);
    }
}


LightSaber readLightSaberFromFile(std::ifstream& ifs)
{
    LightSaber curr;
    int color;
    int type;

    ifs >> color;
    ifs.ignore();
    ifs >> type;

    curr.color = (Color)color;
    curr.type = (Type)type;

    return curr;
}

Jedi readJediFromTXT(std::ifstream& ifs)
{
    Jedi curr;

    ifs >> curr.name;
    ifs.ignore();
    ifs >> curr.age;
    ifs.ignore();
    ifs >> curr.power;

    curr.lightSaber = readLightSaberFromFile(ifs);

    return curr;
}

JediCollection readCollectionFromTXT(const char* filename)
{
    if (!filename)
    {
        return {};
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        return {};
    }

    JediCollection collection;
    file >> collection.count;

    for (size_t i = 0; i < collection.count; i++)
    {
        collection.jedies[i] = readJediFromTXT(file);
    }

    file.close();
    return collection;
}

void sortByAge(const JediCollection& collection)
{
    for (size_t i = 0; i < collection.count; i++)
    {
        size_t minElInd = i;
        for (size_t j = i + 1; j < collection.count; j++)
        {
            if (collection.jedies[j].age < collection.jedies[minElInd].age)
            {
                minElInd = j;
            }
        }

        if (minElInd != i)
        {
            std::swap(collection.jedies[minElInd], collection.jedies[i]);
        }
    }
}

void sortByPower(const JediCollection& collection)
{
    for (size_t i = 0; i < collection.count; i++)
    {
        size_t minElInd = i;
        for (size_t j = i + 1; j < collection.count; j++)
        {
            if ( CONSTANTS::e < collection.jedies[minElInd].power - collection.jedies[j].power)
            {
                minElInd = j;
            }
        }

        if (minElInd != i)
        {
            std::swap(collection.jedies[minElInd], collection.jedies[i]);
        }
    }
}

Color mostPopularSaberColor(const JediCollection& collection)
{
    int colors[CONSTANTS::COLORS_COUNT]{ 0 };

    for (size_t i = 0; i < collection.count; i++)
    {
        colors[(int)collection.jedies[i].lightSaber.color]++;
    }

    int max = 0;
    int value = 0;

    for (size_t i = 0; i < CONSTANTS::COLORS_COUNT; i++)
    {
        if (colors[i] > max)
        {
            max = colors[i];
            value = i;
        }
    }

    return (Color)value;
}

Type mostPopularSaberType(const JediCollection& collection)
{
    int types[CONSTANTS::TYPES_COUNT]{ 0 };

    for (size_t i = 0; i < collection.count; i++)
    {
        types[(int)collection.jedies[i].lightSaber.type]++;
    }

    int max = 0;
    int value = 0;

    for (size_t i = 0; i < CONSTANTS::TYPES_COUNT; i++)
    {
        if (types[i] > max)
        {
            max = types[i];
            value = i;
        }
    }

    return (Type)value;
}


//Task 2

const size_t OWNER_NAME_MAX_LEN = 24;
const size_t FEES_MAX_COUNT = 20;

enum class Brand
{
    Porche,
    Mustang,
    RangeRover,
    Nissan,
    Honda
};

const char* brandToStr(Brand b)
{
    switch (b)
    {
    case Brand::Honda : return "Honda";
    case Brand::Mustang: return "Mustang";
    case Brand::Nissan: return "Nissan";
    case Brand::Porche: return "Porche";
    case Brand::RangeRover: return "RangeRover";
    }
}


struct Car
{
    Brand brand;
    char ownerName[OWNER_NAME_MAX_LEN + 1];
    double averageSpeed;
    double fees[FEES_MAX_COUNT];
    unsigned feesCount = 0;
};


double feesSum(const Car& car)
{
    double sum = 0;
    for (size_t i = 0; i < car.feesCount; i++)
    {
        sum += car.fees[i];
    }
    return sum;
}

void addFee(Car& car, double fee)
{
    if (car.feesCount >= FEES_MAX_COUNT)
    {
        return;
    }

    car.fees[car.feesCount] = fee;
    car.feesCount++;
}

void printFees(const Car& car)
{
    for (size_t i = 0; i < car.feesCount; i++)
    {
        std::cout << car.fees[i] << ", ";
    }
}

void printCar(const Car& car)
{
    std::cout << brandToStr(car.brand) << std::endl;
    std::cout << car.averageSpeed << std::endl;
    std::cout << car.ownerName << std::endl;
    std::cout << car.feesCount << std::endl;
    printFees(car);
    std::cout << std::endl;
}

void writeToBinary(const char* filename, const Car& car)
{
    if (!filename)
    {
        return;
    }

    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open())
    {
        return;
    }

    file.write((const char*)&car, sizeof(car));
    file.close();
}

Car readFromBinary(const char* filename)
{
    if (!filename)
    {
        return {};
    }

    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        return {};
    }

    Car curr;

    file.read((char*)&curr, sizeof(curr));
    file.close();

    return curr;
}


//Task 3

size_t fileSize(std::ifstream& file)
{
    size_t currPos = file.tellg();
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(currPos);

    return size;
}

int findKey(const char* filename)
{
    if (!filename)
    {
        return -1;
    }
    
    std::ifstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open())
    {
        return -1;
    }

    char key;
    file.read((char*)&key, sizeof(key));

    return (int)key;
}

unsigned* getNumsFromFile(const char* filename, size_t& numsCount)
{
    if (!filename)
    {
        return nullptr;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        return nullptr;
    }

    size_t filesize = fileSize(file);
    numsCount = filesize / sizeof(unsigned);

    unsigned* nums = new unsigned[numsCount];
    file.read((char*)nums, filesize);

    file.close();
    return nums;
}

int* decypher(const char* cypherFile, const char* keyFile)
{
    if (!keyFile || !cypherFile)
    {
        return nullptr;
    }

    size_t numsCount = 0;
    unsigned* cypher = getNumsFromFile(cypherFile, numsCount);
    int key = findKey(keyFile);

    int* decyphered = new int[numsCount];

    for (size_t i = 0; i < numsCount; i++)
    {
        decyphered[i] = cypher[i] + key;
    }

    delete[] cypher;
    return decyphered;
}


//Task 4

const size_t USER_DATA_SIZE = 504;
const size_t NODE_SIZE = 512;

struct Node
{
    uint64_t next;
    char userdata[USER_DATA_SIZE  + 1];
};


Node* readData(const char* filename, size_t& nodesCount)
{
    if (!filename)
    {
        return nullptr;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        return nullptr;
    }

    size_t filesize = fileSize(file);
    nodesCount = filesize / NODE_SIZE;
    Node* nodes = new Node[nodesCount];

    for (size_t i = 0; i < nodesCount; i++)
    {
        file.read((char*)&nodes[i], NODE_SIZE);
        nodes[i].userdata[USER_DATA_SIZE] = '\0';
    }

    file.close();
    return nodes;
}

void censore(Node& node)
{
    for (size_t i = 0; i < USER_DATA_SIZE; i++)
    {
        node.userdata[i] = '*';
    }
}

void writeCensoredData(const char* filename, const Node* data, size_t dataSize)
{
    if (!filename)
    {
        return;
    }

    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open())
    {
        return;
    }

    for (size_t i = 0; i < dataSize; i++)
    {
        file.write((const char*)&data[i], NODE_SIZE);
    }
    file.close();
}


void censoreDeletedNodes(const Node* nodes, size_t nodesCount, int start, const char* filename)
{
    if (!nodes || !filename)
    {
        return;
    }

    size_t dataNodesCount = 0;
    Node* data = readData(filename, dataNodesCount);

    if (dataNodesCount == 0) return;

    bool* mark = new bool[dataNodesCount] {false};

    mark[start] = true;

    for (size_t i = 0; i < nodesCount; i++)
    {
        if (nodes[i].next < dataNodesCount) 
        {
            mark[nodes[i].next] = true;
        }
    }

    for (size_t i = 0; i < dataNodesCount; i++)
    {
        if (!mark[i])
        {
            censore(data[i]);
        }
    }

    delete[] mark;
    writeCensoredData(filename, data, dataNodesCount);
    delete[] data;
}


int main()
{
    std::cout << "Hello World!\n";
}

