#include <iostream>
#include <string>
using namespace std;

class Singleton
{
private:
    int data;
    static Singleton *instance;

    // Constructor dan destructor private agar tidak dapat diakses
    Singleton() {}
    ~Singleton() {}

public:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    static Singleton &Instance()
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        else
        {
            return *instance;
        }
    }

    int getData()
    {
        return data;
    }

    void setData(int newData)
    {
        data = newData;
    }
};

Singleton *Singleton::instance = nullptr;

int main()
{
    Singleton *s = s->&Instance();
    s->setData(100);
    cout << s->getData() << endl;

    return 0;
}
