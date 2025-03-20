#include <iostream>


//Task 1

constexpr double e = 0.0000000001;

struct Complex
{
    double re;
    double im;
};

Complex init(double re, double im)
{
    Complex num;
    num.re = re;
    num.im = im;

    return num;
}

void printComplex(const Complex& num)
{
    std::cout << num.re;

    if (std::abs(num.im) < e)
    {
        return;
    }
    else if (num.im > 0)
    {
        std::cout << " + " << num.im << "i" << std::endl;
    }
    else
    {
        std::cout << "-" << num.im << "i" << std::endl;
    }
}

Complex conjugate(const Complex& num)
{
    Complex conjugated;
    conjugated.re = num.re;
    conjugated.im = -num.im;
    return conjugated;
}

Complex add(const Complex& lhs, const Complex& rhs)
{
    Complex res;
    res.re = lhs.re + rhs.re;
    res.im = lhs.im + rhs.im;
    return res;
}

Complex subsrtract(const Complex& lhs, const Complex& rhs)
{
    Complex res;
    res.re = lhs.re - rhs.re;
    res.im = lhs.im - rhs.im;
    return res;
}
//multiply and divide....do not know the formulas



//Task 2


constexpr size_t NAME_LEN = 32;
constexpr size_t COURSE_STUDENTS = 50;

enum class Major
{
    SE,
    IS,
    CS,
    I,
    PM,
    M,
    MI,
    DA,
    Unknown
};


void majorPrint(Major m)
{
    switch (m)
    {
        case Major::M:std::cout << "Mathematics " << std::endl; break;
        case Major::MI:std::cout << "Mathematics and informatics " << std::endl; break;
        case Major::DA:std::cout << "Data analysis " << std::endl; break;
        case Major::I:std::cout << "Informatics " << std::endl; break;
        case Major::IS:std::cout << "Information systems " << std::endl; break;
        case Major::CS:std::cout << "Computer science " << std::endl; break;
        case Major::SE:std::cout << "Software egineering " << std::endl; break;
        case Major::Unknown:std::cout << "Unknown " << std::endl; break;
    }
}

struct Student
{
    char name[NAME_LEN];
    int fn;
    double averageGrade;
    Major major = Major::Unknown;
};

struct Course
{
    Student students[COURSE_STUDENTS];
    int studentsCount = 0;
};


Student initStudent(const char* name, int fn, Major m)
{
    Student s;
    std::strcpy(s.name, name);
    s.fn = fn;
    s.major = m;

    return s;
}

void printStudent(const Student& s)
{
    std::cout << s.name << std::endl;
    majorPrint(s.major);
    std::cout << s.fn << std::endl;
    std::cout << s.averageGrade << std::endl;
    std::cout << std::endl << std::endl;
}

void printCourse(const Course& course)
{
    if (course.studentsCount == 0)
    {
        std::cout << "The course is empty..." << std::endl;
        return;
    }

    for (int i = 0; i < course.studentsCount; i++)
    {
        printStudent(course.students[i]);
    }
}

void addToCourse(const Student& s, Course& course)
{
    if (course.studentsCount >= COURSE_STUDENTS)
    {
        std::cout << "The cours is full, can't add anymore students..." << std::endl;
        return;
    }

    course.students[course.studentsCount] = s;
    course.studentsCount++;
}

void removeStudent(Course& course, int fn)
{
    int ind = 0;
    while (ind < course.studentsCount)
    {
        if (course.students[ind].fn == fn)
        {
            break;
        }
        ind++;
    }

    if (ind == course.studentsCount)
    {
        std::cout << "There isn't student with fn in this course..." << std::endl;
        return;
    }

    for (int i = ind; i < course.studentsCount - 1; i++)
    {
        course.students[i] = course.students[i + 1];
    }
    course.studentsCount--;
}

void sortByGrade(Course& course)
{
    for (int i = 0; i < course.studentsCount; i++)
    {
        int minElInd = i;
        for (int j = i + 1; j < course.studentsCount; j++)
        {
            if (course.students[j].averageGrade < course.students[minElInd].averageGrade) 
            {
                minElInd = j;
            }
            else if (course.students[j].averageGrade == course.students[minElInd].averageGrade)
            {
                if (std::strcmp(course.students[j].name, course.students[minElInd].name) < 0)
                {
                    minElInd = j;
                }
            }
        }

        if (i != minElInd)
        {
            std::swap(course.students[i], course.students[minElInd]);
        }
    }
}

void filterStudents(const Course& course, bool(*predicate)(const Student&))
{
    if (course.studentsCount == 0)
    {
        return;
    }

    for (int i = 0; i < course.studentsCount; i++)
    {
        if (predicate(course.students[i]))
        {
            printStudent(course.students[i]);
        }
    }
}


//Task 3

constexpr size_t CLIENT_NAME_SIZE = 31;
constexpr size_t DRINKS_COUNT = 8;

enum class Drink
{
    Whiskey,
    Vodka,
    CocaCola,
    Fanta,
    Water,
    Wine,
    Rom,
    Juice
};

void printDrink(Drink drink)
{
    switch (drink)
    {
        case Drink::Whiskey: std::cout << "Whiskey " << std::endl; break;
        case Drink::Vodka: std::cout << "Vodka " << std::endl; break;
        case Drink::CocaCola: std::cout << "Coca-Cola " << std::endl; break;
        case Drink::Fanta: std::cout << "Fanta " << std::endl; break;
        case Drink::Water: std::cout << "Water " << std::endl; break;
        case Drink::Wine: std::cout << "Wine " << std::endl; break;
        case Drink::Rom: std::cout << "Rom " << std::endl; break;
        case Drink::Juice: std::cout << "Juice " << std::endl; break;
    }
}

struct Client
{
    char clientName[CLIENT_NAME_SIZE];
    unsigned char likedDrinks = 0;
};

bool doesClientLikeDrink(const Client& client, Drink d)
{
    int mask = 1;
    mask = mask << (int)d;

    return (client.likedDrinks & mask) != 0;
}

void makeClientLikeDrink(Client& client, Drink d)
{
    int mask = 1;
    mask = mask << (int)d;

    client.likedDrinks = client.likedDrinks | mask;
}

void makeClientNotLikeDrink(Client& client, Drink d)
{
    int mask = 1;
    mask = mask << (int)d;
    mask = ~mask;

    client.likedDrinks = client.likedDrinks & mask;
}

void printLikedDrinks(const Client& client)
{
    char mask = client.likedDrinks;
    int check = 1;

    for (int i = 0; i < DRINKS_COUNT; i++)
    {
        if ((mask & (check << i)) != 0)
        {
            printDrink((Drink)i);
        }
    }
}



//Task 4

constexpr size_t TITLE_SIZE = 50;
constexpr size_t QUESTIONS_COUNT = 30;

struct Question
{
    char title[TITLE_SIZE];
    char* A;
    char* B;
    char* C;
    char* D;
    char trueAnswer;
};

struct Test
{
    Question questions[QUESTIONS_COUNT];
};

Question initQ(const char* title, const char* A, const char* B, const char* C, const char* D, char trueAnswer)
{
    Question q;

    q.A = new char[std::strlen(A) + 1];
    q.B = new char[std::strlen(B) + 1];
    q.C = new char[std::strlen(C) + 1];
    q.D = new char[std::strlen(D) + 1];

    std::strcpy(q.title, title);
    std::strcpy(q.A, A);
    std::strcpy(q.B, B);
    std::strcpy(q.C, C);
    std::strcpy(q.D, D);

    q.trueAnswer = trueAnswer;
    return q;
}

void deleteQuestion(Question& q)
{
    delete[] q.A;
    delete[] q.B;
    delete[] q.C;
    delete[] q.D;
}

void printQuestion(const Question& q)
{
    std::cout << q.title << std::endl;
    std::cout << "A) " << q.A << std::endl;
    std::cout << "B) " << q.B << std::endl;
    std::cout << "C) " << q.C << std::endl;
    std::cout << "D) " << q.D << std::endl << std::endl;
}

void printTes(const Test& test)
{
    for (int i = 0; i < QUESTIONS_COUNT; i++)
    {
        printQuestion(test.questions[i]);
    }
}

bool isPickedQuestionTrue(const Test& test, int qNum, char picked)
{
    if(test.questions[qNum - 1].trueAnswer == picked)
    {
        return true;
    }
    return false;
}


//Task 5


constexpr int VERTEX_NAME_SIZE = 10;

struct Edge
{
    char v[VERTEX_NAME_SIZE];
    char u[VERTEX_NAME_SIZE];
};

struct OrderedGraph
{
    int edgesCount;
    int verticesCount;
    Edge* edges;
};


Edge initEdge(const char* v, const char* u)
{
    Edge e;
    std::strcpy(e.v, v);
    std::strcpy(e.u, u);

    return e;
}

OrderedGraph initGraph(int v, int e)
{
    OrderedGraph graph;
    graph.edgesCount = e;
    graph.verticesCount = v;
    graph.edges = new Edge[e];

    return graph;
}

void deleteGraph(OrderedGraph& graph)
{
    delete[] graph.edges;
    graph.verticesCount = 0;
    graph.edgesCount = 0;
}

void addEdge(OrderedGraph& graph, const char* v, const char* u)
{
    Edge* newEdges = new Edge[graph.edgesCount + 1];

    for (int i = 0; i < graph.edgesCount; i++)
    {
        newEdges[i] = graph.edges[i];
    }

    Edge newEdge = initEdge(v, u);
    newEdges[graph.edgesCount] = newEdge;

    delete[] graph.edges;

    graph.edges = newEdges;
    graph.edgesCount++;
}

void vertexDegrees(const OrderedGraph& graph, const char* vertex, int& entry, int& exit)
{
    for (int i = 0; i < graph.edgesCount; i++)
    {
        if (std::strcmp(graph.edges[i].u, vertex) == 0)
        {
            entry++;
        }

        if (std::strcmp(graph.edges[i].v, vertex) == 0)
        {
            exit++;
        }
    }
}

bool isFull(const OrderedGraph& graph)
{
    return ((graph.verticesCount * (graph.verticesCount - 1)) / 2) == graph.edgesCount;
}

void deleteEdge(OrderedGraph& graph, const Edge& edge)
{
    Edge* newEdges = new Edge[graph.edgesCount - 1];
    int newEdgesInd = 0;

    for (int i = 0; i < graph.edgesCount; i++)
    {
        if (std::strcmp(graph.edges[i].u, edge.u) == 0 && std::strcmp(graph.edges[i].v, edge.v) == 0)
        {
            continue;
        }
        newEdges[newEdgesInd] = graph.edges[i];
        newEdgesInd++;
    }

    delete[] graph.edges;

    graph.edges = newEdges;
    graph.edgesCount--;
}


int main()
{
    std::cout << "Hello World!\n";
}

