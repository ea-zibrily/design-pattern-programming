#include <iostream>
#include <string>

using namespace std;

// Product
class Pizza {
public:

    // Pizza setDough(const string dough) {
    //     m_dough = dough;
    //     return *this;
    // }

    Pizza setSauce(const string sauce) {
        m_sauce = sauce;
        return *this;
    }

    Pizza setTopping(const string topping) {
        m_topping = topping;
        return *this;
    }

    void open() const {
        cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and " << m_topping << " topping. Mmm." << endl;
    }

    void setDough(const string dough) {
        m_dough = dough;
    }

    // void setSauce(const string& sauce) {
    //     m_sauce = sauce;
    // }

    // void setTopping(const string& topping) {
    //     m_topping = topping;
    // }

    // void open() const {
    //     cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and " << m_topping << " topping. Mmm." << endl;
    // }

private:
    string m_dough;
    string m_sauce;
    string m_topping;
};


// Builder
class PizzaBuilder {
public:
    virtual ~PizzaBuilder() {};

    Pizza* getPizza() {
        return m_pizza;
    }

    void createNewPizza() {
        m_pizza = new Pizza;
    }

    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;

protected:
    Pizza* m_pizza;
};

// ConcreteBuilder
class HawaiianPizzaBuilder : public PizzaBuilder {
public:
    virtual ~HawaiianPizzaBuilder() {};
    
    virtual void buildDough() {
        m_pizza->setDough("cross");
    }

    virtual void buildSauce() {
        m_pizza->setSauce("mild");
    }

    virtual void buildTopping() 
    {
        m_pizza->setTopping("ham and pineapple");
    }
};

// ConcreteBuilder
class SpicyPizzaBuilder : public PizzaBuilder {
public:
    virtual ~SpicyPizzaBuilder() {};

    virtual void buildDough() {
        m_pizza->setDough("pan baked");
    }

    virtual void buildSauce() {
        m_pizza->setSauce("hot");
    }

    virtual void buildTopping() {
        m_pizza->setTopping("pepperoni and salami");
    }
};

// Director
class Cook {
public:
    void setPizzaBuilder(PizzaBuilder* pizzaBuilder) {
        m_pizzaBuilder = pizzaBuilder;
    }

    Pizza* getPizza() {
        return m_pizzaBuilder->getPizza();
    }

    void constructPizza() {
        m_pizzaBuilder->createNewPizza();
        m_pizzaBuilder->buildDough();
        m_pizzaBuilder->buildSauce();
        m_pizzaBuilder->buildTopping();
    }

private:
    PizzaBuilder* m_pizzaBuilder;
};

int main() 
{
    Cook cook;
    PizzaBuilder* hawaiianPizzaBuilder = new HawaiianPizzaBuilder;
    PizzaBuilder* spicyPizzaBuilder = new SpicyPizzaBuilder;

    // Build and cook a Hawaiian pizza
    cook.setPizzaBuilder(hawaiianPizzaBuilder);
    cook.constructPizza();
    Pizza* hawaiianPizza = cook.getPizza();
    hawaiianPizza->open();

    // Build and cook a spicy pizza
    cook.setPizzaBuilder(spicyPizzaBuilder);
    cook.constructPizza();
    Pizza* spicyPizza = cook.getPizza();
    spicyPizza->open();

    // Clean up
    delete hawaiianPizzaBuilder;
    delete spicyPizzaBuilder;
    delete hawaiianPizza;
    delete spicyPizza;

    return 0;
}
