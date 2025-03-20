#include <iostream>
#include <fstream>


//Task 1

void task1(const char* filename1, const char* filename2)
{
    std::ifstream ifs(filename1);
    if (!ifs.is_open())
    {
        std::cout << "Error opening the file for reading...";
        return;
    }

    int n1, n2;
    ifs >> n1 >> n2;

    ifs.close();

    int sum = n1 + n2;
    int product = n1 * n2;

    std::ofstream ofs(filename2);
    if (!ofs.is_open())
    {
        std::cout << "Error opening the file for writing...";
        return;
    }

    ofs << sum << " " << product;
    ofs.close();
}


//Task 2

void task2(const char* filename)
{
    std::ifstream ifs(filename);

    if (!ifs.is_open())
    {
        std::cout << "Error opening the file for reading...";
        return;
    }

    std::ofstream even("even.txt");
    std::ofstream odd("odd.txt");

    int num;
    while (ifs >> num)
    {
        if (num % 2 == 0)
        {
            even << num << " ";
        }
        else
        {
            odd << num << " ";
        }
    }

    ifs.close();
    even.close();
    odd.close();
}


//Task 3

constexpr size_t MAX_VECTOR_COUNT = 50;

struct Vector
{
    int x, y, z;
};

struct VectorSpace
{
    Vector vectors[MAX_VECTOR_COUNT];
    int count = 0;
};


Vector makeVector()
{
    Vector curr;
    std::cin >> curr.x >> curr.y >> curr.z;

    return curr;
}

void addToVectorSpace(const Vector& vector, VectorSpace& space)
{
    if (space.count >= MAX_VECTOR_COUNT)
    {
        std::cout << "Vector space is full, can't add a new one..." << std::endl;
        return;
    }

    space.vectors[space.count] = vector;
    space.count++;
}

void serializeVector(const char* filename, const Vector& vector)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return;
    }

    file.write((const char*)&vector, sizeof(vector));
    file.close();
}

void serializeTXT(std::ofstream& ofs, const Vector& vector)
{
    ofs << "<" << vector.x << ", " << vector.y << ", " << vector.z << ">" << std::endl;
}

Vector deserializeTXT(std::ifstream& ifs)
{
    Vector res;

    ifs.ignore();
    ifs >> res.x;
    ifs.ignore();
    ifs >> res.y;
    ifs.ignore();
    ifs >> res.z;

    return res;
}

void serializeSpaceTXT(const char* filename, const VectorSpace& space)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "File can't be open" << std::endl;
        return;
    }

    ofs << space.count << std::endl;

    for (int i = 0; i < space.count; i++)
    {
        serializeTXT(ofs, space.vectors[i]);
    }

    ofs.close();
}



Vector deserializeVector(const char* filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return {};
    }

    Vector res;
    file.read((char*)&res, sizeof(res));
    file.close();

    return res;
}

VectorSpace deserializeSpaceTXT(const char* filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cout << "File can't be open" << std::endl;
        return {};
    }

    VectorSpace res;
    ifs >> res.count;

    for (int i = 0; i < res.count; i++)
    {
        Vector curr = deserializeTXT(ifs);
        res.vectors[i] = curr;
    }

    return res;
}

void serializeVectorSpace(const VectorSpace& space, const char* filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return;
    }

    file.write((const char*)&space.count, sizeof(space.count));
    file.write((const char*)&space.vectors, MAX_VECTOR_COUNT * sizeof(space.vectors[0]));
    file.close();
}

VectorSpace deserializeVectorSpace(const char* filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "file can't be open..." << std::endl;
        return {};
    }

    VectorSpace res;

    file.read((char*)&res.count, sizeof(res.count));
    file.ignore();
    file.read((char*)&res.vectors, MAX_VECTOR_COUNT * sizeof(Vector));
    file.close();

    return res;
}


//Task 4

constexpr int DEVICE_NAME_SIZE = 32;
constexpr int DELIVERER_SIZE = 32;
constexpr int MAX_DEVICES_COUNT = 100;
constexpr int OWNER_NAME_SIZE = 32;
constexpr double e = 0.0000000001;

enum class DeviceType
{
    TV,
    SMARTPHONE,
    LAPTOP,
    PC,
    CAMERA
};

struct Device
{
    char name[DEVICE_NAME_SIZE];
    int available;
    double price;
    DeviceType type;
    char deliverer[DELIVERER_SIZE];
};


struct Warehouse
{
    Device devices[MAX_DEVICES_COUNT];
    int count = 0;
    char owner[OWNER_NAME_SIZE];
};


Device createDevice(const char* name, int available, double price, DeviceType type, const char* deliverer)
{
    Device res;
    std::strcpy(res.name, name);
    res.available = available;
    res.price = price;
    res.type = type;
    std::strcpy(res.deliverer, deliverer);

    return res;
}

Warehouse createWarehouse(const char* owner, int devicesCount, std::istream& ifs)
{
    Warehouse res;
    res.count = devicesCount;
    std::strcpy(res.owner, owner);

    for (int i = 0; i < devicesCount; i++)
    {
        char name[DEVICE_NAME_SIZE];
        int available;
        double price;
        int type;
        char deliverer[DELIVERER_SIZE];

        ifs >> name >> deliverer >> available >> price >> type;
        Device curr = createDevice(name, available, price, (DeviceType)type, deliverer);

        res.devices[i] = curr;
    }
    return res;
}

void addDevice(Warehouse& warehouse, const Device& device)
{
    if (warehouse.count >= MAX_DEVICES_COUNT)
    {
        std::cout << "The warehouse is full can't add a new device..." << std::endl;
        return;
    }

    warehouse.devices[warehouse.count] = device;
    warehouse.count++;
}

void serializeWarehouse(const Warehouse& warehouse, const char* filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return;
    }

    file.write((const char*)&warehouse, sizeof(warehouse));
    file.close();
}

Warehouse deserializeWarehouse(const char* filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return {};
    }

    Warehouse res;

    file.read((char*)&res, sizeof(res));
    file.close();

    return res;
}

void saveDeviceToFile(std::ostream& ofs, const Device& device)
{
    ofs << device.name << std::endl;
    ofs << (int)device.type << std::endl;
    ofs << device.price << std::endl;
    ofs << device.available << std::endl;
    ofs << device.deliverer << std::endl;
    ofs << std::endl;
}

void saveSameTypeDevices(const char* filename, const Warehouse& warehouse, DeviceType type)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return;
    }

    for (int i = 0; i < warehouse.count; i++)
    {
        if (warehouse.devices[i].type == type)
        {
            saveDeviceToFile(ofs, warehouse.devices[i]);
        }
    }

    ofs.close();
}

void printWarehouse(const Warehouse& warehouse)
{
    std::cout << warehouse.owner << std::endl;
    std::cout << warehouse.count << std::endl;

    for (int i = 0; i < warehouse.count; i++)
    {
        saveDeviceToFile(std::cout, warehouse.devices[i]);
    }
}

void sortByPrice(Warehouse& warehouse)
{
    for (size_t i = 0; i < warehouse.count; i++)
    {
        size_t minElInd = i;
        for (size_t j = i + 1; j < warehouse.count; j++)
        {
            if (warehouse.devices[minElInd].price - warehouse.devices[j].price > e)
            {
                minElInd = j;
            }
        }

        if (i != minElInd)
        {
            std::swap(warehouse.devices[i], warehouse.devices[minElInd]);
        }
    }
}

void sortByAvailability(Warehouse& warehouse)
{
    for (size_t i = 0; i < warehouse.count; i++)
    {
        size_t minElInd = i;
        for (size_t j = i + 1; j < warehouse.count; j++)
        {
            if (warehouse.devices[j].available < warehouse.devices[minElInd].available)
            {
                minElInd = j;
            }
        }

        if (i != minElInd)
        {
            std::swap(warehouse.devices[i], warehouse.devices[minElInd]);
        }
    }
}

void cheapestMostExpensive(const Warehouse& warehouse)
{
    Device devices[2];
    double cheapest = 10000000.0;
    double mostExpensive = 0.0;

    for (int i = 0; i < warehouse.count; i++)
    {
        if (warehouse.devices[i].price - mostExpensive > e)
        {
            mostExpensive = warehouse.devices[i].price;
            devices[1] = warehouse.devices[i];
        }

        if (cheapest - warehouse.devices[i].price > e)
        {
            cheapest = warehouse.devices[i].price;
            devices[0] = warehouse.devices[i];
        }
    }

    saveDeviceToFile(std::cout, devices[0]);
    saveDeviceToFile(std::cout, devices[1]);
}


//Task 5 - Colors

struct Color
{
    int R;
    int G;
    int B;
};


int getSymbolsCount(std::ifstream& ifs, char ch)
{
    size_t currPos = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    int count = 0;

    while (true)
    {
        if (ifs.eof())
            break;

        if (ifs.get() == ch)
            count++;
    }

    ifs.clear();
    ifs.seekg(currPos);
    return count;
}

Color* readColors(const char* filename, size_t& colorsCount)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return nullptr;
    }

    colorsCount = getSymbolsCount(ifs, '|') + 1;
    
    Color* colors = new Color[colorsCount];
    int colorInd = 0;
    int mask = 255;
    int num;

    while (ifs >> num)
    {
        Color curr;
        curr.B = mask & num;
        curr.G = (8 >> num) & mask;
        curr.R = (16 >> num) & mask;

        colors[colorInd] = curr;
        colorInd++;
    }
    return colors;
}

void freeColors(const Color*& colors)
{
    delete[] colors;
}

void writeColors(const char* filename, const Color*& colors, size_t colorsCount)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
    }

    for (size_t i = 0; i < colorsCount; i++)
    {
        int curr = colors[i].R * 256 * 256 + colors[i].G * 256 + colors[i].B;
        ofs << curr << "|";
    }
}

void writeColors(const char* filename, const Color*& colors, size_t colorsCount)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
    }

    for (size_t i = 0; i < colorsCount; i++)
    {
        if (colors[i].R > 250)
        {
            int curr = colors[i].R * 256 * 256 + colors[i].G * 256 + colors[i].B;
            ofs << curr << "|";
        }
    }
}

//Task 5 - realtions

constexpr size_t MAX_PAIRS = 25;

struct Pair
{
    int a;
    int b;
};

struct Relation
{
    Pair relation[MAX_PAIRS];
    int pairsCount = 0;
};


void writePairToFile(std::ofstream& ofs, const Pair& pair)
{
    ofs << "<" << pair.a << "," << pair.b << ">" << " ";
}

void writeRelationToFile(const Relation& rel, const char* filename)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "File can't be open..." << std::endl;
        return;
    }

    ofs << rel.pairsCount << std::endl;
    for (int i = 0; i < rel.pairsCount; i++)
    {
        writePairToFile(ofs, rel.relation[i]);
        ofs << std::endl;
    }
}

Pair readPairFromFile(std::ifstream& ifs)
{
    Pair p;
    ifs.ignore();
    ifs >> p.a;
    ifs.ignore();
    ifs >> p.b;
    ifs.ignore();
    ifs.ignore();

    return p;
}

Relation readRelationFromFile(const char* filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cout << "File can't be open" << std::endl;
        return {};
    }

    Relation rel;
    ifs >> rel.pairsCount;

    for (int i = 0; i < rel.pairsCount; i++)
    {
        rel.relation[i] = readPairFromFile(ifs);
    }

    return rel;
}

void addPairToRel(Relation& rel, const Pair& toAdd)
{
    if (rel.pairsCount >= MAX_PAIRS)
    {
        std::cout << "The relation is full, can't add more pairs..." << std::endl;
        return;
    }

    rel.relation[rel.pairsCount] = toAdd;
    rel.pairsCount++;
}

bool findPair(const Pair& toFind, const Relation& rel, int& pos)
{
    for (size_t i = 0; i < rel.pairsCount; i++)
    {
        if (rel.relation[i].a == toFind.a && rel.relation[i].b == toFind.b)
        {
            pos = i;
            return true;
        }
    }
    return false;
}

void sortRelation(Relation& rel)
{
    for (int i = 0; i < rel.pairsCount; i++)
    {
        int minElInd = i;

        for (size_t j = i + 1; j < rel.pairsCount; j++)
        {
            if (rel.relation[j].a < rel.relation[i].a)
            {
                minElInd = j;
            }
            else if (rel.relation[j].a == rel.relation[i].a)
            {
                if (rel.relation[i].b < rel.relation[j].b)
                {
                    minElInd = j;
                }
            }
        }
        if (minElInd != i)
        {
            std::swap(rel.relation[minElInd], rel.relation[i]);
        }
    }
}

void reflexive(const char* filename, const Relation& rel)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "...";
        return;
    }

    for (size_t i = 0; i < rel.pairsCount; i++)
    {
        if (rel.relation[i].a == rel.relation[i].b)
        {
            writePairToFile(ofs, rel.relation[i]);
        }
    }
}

void symetric(const char* filename, const Relation& rel)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "...";
        return;
    }

    for (size_t i = 0; i < rel.pairsCount; i++)
    {
        Pair opposite = { rel.relation[i].b, rel.relation[i].a };
        int pos = -1;
        if (findPair(opposite, rel, pos))
        {
            writePairToFile(ofs, rel.relation[i]);
        }
    }
}

void transitive(const char* filename, const Relation& rel)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "...";
        return;
    }

    bool* isInRel = new bool[rel.pairsCount] {false};

    for (size_t i = 0; i < rel.pairsCount; i++)
    {
        for (size_t j = i + 1; j < rel.pairsCount; j++)
        {
            Pair p = { rel.relation[i].a, rel.relation[j].b };
            int pos = -1;
            if (findPair(p, rel, pos))
            {
                isInRel[i] = true;
                isInRel[j] = true;
                isInRel[pos] = true;
            }
        }
    }

    for (size_t i = 0; i < rel.pairsCount; i++)
    {
        if (isInRel[i])
        {
            writePairToFile(ofs, rel.relation[i]);
        }
    }

    delete[] isInRel;
}

int main()
{
    std::cout << "Hello World!\n";
}
