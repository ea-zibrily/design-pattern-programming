#include <iostream>
#include <string>
using namespace std;

class Person;

class Command
{
private:
    Person *person;
    void (Person::*method)();
    
public:
    Command(Person *obj = 0, void (Person::*mth)() = 0)
    {
        this->person = obj;
        this->method = mth;
    }

    void execute()
    {
        // Invoke the method on the Object
        (person->*method)(); 
    }
};

class Person
{
private:
    string personName;
    Command cmd;

public:
    Person(string name, Command cmd) : cmd(cmd)
    {
        this->personName = name;
    }

    void talk()
    {
        cout << personName << " is talking" << endl;
        cmd.execute();
    }

    void passOn()
    {
        cout << personName << " is passing on" << endl;
        cmd.execute();
    }

    void gossip()
    {
        cout << personName << " is gossiping" << endl;
        cmd.execute();
    }

    void listen()
    {
        cout << personName << " is listening" << endl;
        cmd.execute();
    }
};

int main()
{
    cout << "Person Command Pattern Example" << endl;
    cout << endl;

    // Set base command
    Person wilma("Wilma", Command());

    // Use base command to set other commands
    Person betty("Betty", Command(&wilma, &Person::listen));
    Person barney("Barney", Command(&betty, &Person::gossip));
    Person fred("Fred", Command(&barney, &Person::passOn));

    // Execute Fred Object Commands
    fred.talk();

    return 0;
}