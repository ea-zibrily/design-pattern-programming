#include <iostream>
#include <vector>

using namespace std;

class Memento
{
public:
    Memento(vector<int> state)
    {
        this->state = state;
    }

    vector<int> getState()
    {
        return state;
    }

private:
    vector<int> state;
};

class Originator
{
public:
    void setState(vector<int> state)
    {
        this->state = state;
    }

    vector<int> getState()
    {
        return state;
    }

    Memento *saveStateToMemento()
    {
        return new Memento(state);
    }

    void getStateFromMemento(Memento *memento)
    {
        state = memento->getState();
    }

private:
    vector<int> state;
};

class Caretaker
{
public:
    void addMemento(Memento *memento)
    {
        mementos.push_back(memento);
    }

    Memento *getMemento(int index)
    {
        return mementos[index];
    }

private:
    vector<Memento *> mementos;
};

int main()
{
    Originator originator;
    Caretaker caretaker;

    // set initial state
    vector<int> state1 = {1, 2, 3};
    originator.setState(state1);
    caretaker.addMemento(originator.saveStateToMemento());

    // make changes
    vector<int> state2 = {4, 5, 6};
    originator.setState(state2);
    caretaker.addMemento(originator.saveStateToMemento());

    // make more changes
    vector<int> state3 = {7, 8, 9};
    originator.setState(state3);

    // restore to previous state
    originator.getStateFromMemento(caretaker.getMemento(0));
    cout << "Current state: ";
    for (int i = 0; i < originator.getState().size(); i++)
    {
        cout << originator.getState()[i] << " ";
    }
    cout << endl;

    return 0;
}