#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;

// Base class Strategy
// Class ini nantinya akan diturunkan ke beberapa class turunan
// Dimana tiap class turunan akan mengimplementasikan algoritma yang berbeda
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual string doAlgorithm(string_view data) const = 0;
};

class Context
{
private:
    unique_ptr<Strategy> strategy_;

public:
    explicit Context(unique_ptr<Strategy> &&strategy = {}) : strategy_(move(strategy)) {}

    // Method ini berfungsi untuk mengubah class yang ingin digunakan
    void set_strategy(unique_ptr<Strategy> &&strategy)
    {
        strategy_ = move(strategy);
    }

    // Method ini berfungsi untuk menjalankan
    // Algoritma yang ada di dalam class Strategy
    void doSomeBusinessLogic() const
    {
        if (strategy_)
        {
            cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            string result = strategy_->doAlgorithm("aecbd");
            cout << result << "\n";
        }
        else
        {
            cout << "Context: Strategy isn't set\n";
        }
    }
};

// Concrete class Strategy
// Class ini berisi Algoritma dari ConcreteStrategyA
class ConcreteStrategyA : public Strategy
{
public:
    string doAlgorithm(string_view data) const override
    {
        string result(data);
        sort(begin(result), end(result));

        return result;
    }
};

// Concrete class Strategy
// Class ini berisi Algoritma dari ConcreteStrategyB

class ConcreteStrategyB : public Strategy
{
    string doAlgorithm(string_view data) const override
    {
        string result(data);
        sort(begin(result), end(result), greater<>());

        return result;
    }
};

// Function ini berfungsi sebagai pengganti main()
// Dalam artian, semua code akan dijalankan di dalam function ini
// Lalu, function ini akan dipanggil dalam main()

void clientCode()
{
    Context context(make_unique<ConcreteStrategyA>());

    cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();

    cout << "\n";
    cout << "Client: Strategy is set to reverse sorting.\n";
    context.set_strategy(make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}

int main()
{
    clientCode();

    return 0;
}