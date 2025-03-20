#include <iostream>


class Vector
{
    int* array;
    size_t size;
    size_t capacity;

public:
    //Vector() = default;
    Vector()
    {
        array = nullptr;
        size = 0;
        capacity = 0;
    }

    Vector(const Vector& other)
    {
        delete[] this->array;

        this->array = new int[other.size];
        for (int i = 0; i < other.size; i++)
        {
            this->array[i] = other.array[i];
        }
        this->size = other.size;
        this->capacity = other.capacity;
    }

    Vector& operator=(const Vector& other) //always
    {
        if (this == &other)
        {
            return *this; //always
        }

        delete[] this->array;

        this->array = new int[other.size];
        for (size_t i = 0; i < other.size; i++)
        {
            this->array[i] = other.array[i];
        }
        this->size = other.size;
        this->capacity = other.capacity;

        return *this; //always
    }

    ~Vector()
    {
        delete[] this->array;
    }
 
    //Not important, custom
    Vector(int size)
    {
        array = new int[size];
        this->size = 0;
        this->capacity = size;
    }

    //custom
    Vector(int size, int num)
    {
        this->array = new int[size];
        this->capacity = size;
        this->size = size;

        for (size_t i = 0; i < size; i++)
        {
            this->array[i] = num;
        }
    }

    void resize(int N)
    {
        if (N <= capacity)
        {
            return;
        }
        
        int* newArray = new int[N];
        this->size = 0;
        this->capacity = N;

        for (size_t i = 0; i < capacity; i++)
        {
            newArray[i] = this->array[i];
            this->size++;
            
        }

        delete[] this->array;
        this-> array = newArray;
    }

    void clear()
    {
        for (size_t i = 0; i < this->capacity; i++)
        {
            this->array[i] = 0;
        }
        this->size = 0;
    }

    int at(size_t x) const
    {
        if (x >= size)
        {
            return -1;
        }

        for (size_t i = 0; i < capacity; i++)
        {
            if (i == x)
            {
                return array[x];
            }
        }
    }

    void pushBack(int el)
    {
        if (size == capacity)
        {
            //moje da se izvika resize vmesto tova
            int* newArray = new int[capacity + 1];
            this->capacity++;

            for (size_t i = 0; i < capacity; i++) 
            {
                newArray[i] = array[i];
            }

            delete[] this->array;
            this->array = newArray;
        }

        this->array[size] = el;
        this->size++;
    }

    bool empty() const
    {
        return size == 0;
    }

    int size() const
    {
        return this->size;
    }
};


int main()
{
    Vector arr[3];
    Vector v1 = {}; //copy constructor
    Vector v2;
    v2 = v1; //operator=
    v1 = v2;
}

