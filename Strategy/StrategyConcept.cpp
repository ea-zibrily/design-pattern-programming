#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

/**
 * The Strategy interface declares operations common to all supported versions
 * of some algorithm.
 *
 * The Context uses this interface to call the algorithm defined by Concrete
 * Strategies.
 */
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual string doAlgorithm(string_view data) const = 0;
};

/**
 * The Context defines the interface of interest to clients.
 */

class Context
{
    /**
     * @var Strategy The Context maintains a reference to one of the Strategy
     * objects. The Context does not know the concrete class of a strategy. It
     * should work with all strategies via the Strategy interface.
     */
private:
    unique_ptr<Strategy> strategy_;
    /**
     * Usually, the Context accepts a strategy through the constructor, but also
     * provides a setter to change it at runtime.
     */
public:
    explicit Context(unique_ptr<Strategy> &&strategy = {}) : strategy_(move(strategy))
    {
    }
    /**
     * Usually, the Context allows replacing a Strategy object at runtime.
     */
    void set_strategy(unique_ptr<Strategy> &&strategy)
    {
        strategy_ = move(strategy);
    }
    /**
     * The Context delegates some work to the Strategy object instead of
     * implementing +multiple versions of the algorithm on its own.
     */
    void doSomeBusinessLogic() const
    {
        if (strategy_) {
            cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            string result = strategy_->doAlgorithm("aecbd");
            cout << result << "\n";
        } else {
            cout << "Context: Strategy isn't set\n";
        }
    }
};

/**
 * Concrete Strategies implement the algorithm while following the base Strategy
 * interface. The interface makes them interchangeable in the Context.
 */
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
class ConcreteStrategyB : public Strategy
{
    string doAlgorithm(string_view data) const override
    {
        string result(data);
        sort(begin(result), end(result), greater<>());

        return result;
    }
};
/**
 * The client code picks a concrete strategy and passes it to the context. The
 * client should be aware of the differences between strategies in order to make
 * the right choice.
 */

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