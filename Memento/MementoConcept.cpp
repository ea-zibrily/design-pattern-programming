#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

/**
 * The Memento interface provides a way to retrieve the memento's metadata, such
 * as creation date or name. However, it doesn't expose the Originator's state.
 */

// Class memento sebagai interface class yang berfungsi untuk sebagai
// badan utama dari pattern Memento

class Memento
{
public:
    virtual ~Memento() {}
    virtual string GetName() const = 0;
    virtual string date() const = 0;
    virtual string state() const = 0;
};

/**
 * The Concrete Memento contains the infrastructure for storing the Originator's
 * state.
 */
class ConcreteMemento : public Memento
{
private:
    string state_;
    string date_;

public:
    ConcreteMemento(string state) : state_(state)
    {
        this->state_ = state;
        time_t now = time(0);
        this->date_ = ctime(&now);
    }
    /**
     * The Originator uses this method when restoring its state.
     */
    string state() const override
    {
        return this->state_;
    }
    /**
     * The rest of the methods are used by the Caretaker to display metadata.
     */
    string GetName() const override
    {
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }
    string date() const override
    {
        return this->date_;
    }
};

/**
 * The Originator holds some important state that may change over time. It also
 * defines a method for saving the state inside a memento and another method for
 * restoring the state from it.
 */

// Class Originator berfungsi pengendali dari Memento, dimana user dapat
// memberikan input/data yang akan disimpan dalam Memento

class Originator
{
private:
    string state_;

    string GenerateRandomString(int length = 10)
    {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        string random_string;
        for (int i = 0; i < length; i++)
        {
            random_string += alphanum[rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(string state) : state_(state)
    {
        cout << "Originator: My initial state is: " << this->state_ << "\n";
    }
    /**
     * The Originator's business logic may affect its internal state. Therefore,
     * the client should backup the state before launching methods of the business
     * logic via the save() method.
     */
    void DoSomething()
    {
        cout << "Originator: I'm doing something important.\n";
        this->state_ = this->GenerateRandomString(30);
        cout << "Originator: and my state has changed to: " << this->state_ << "\n";
    }

    /**
     * Saves the current state inside a memento.
     */
    Memento *Save()
    {
        return new ConcreteMemento(this->state_);
    }
    /**
     * Restores the Originator's state from a memento object.
     */
    void Restore(Memento *memento)
    {
        this->state_ = memento->state();
        cout << "Originator: My state has changed to: " << this->state_ << "\n";
    }
};

/**
 * The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
 * doesn't have access to the originator's state, stored inside the memento. It
 * works with all mementos via the base Memento interface.
 */

// Class Caretaker berfungsi untuk menyimpan "State" dari semua perubahan Memento yang
// user berikan pada class Originator
// Dalam class ini lah, user dapat mengembalikan state dari Memento yang telah disimpan

class Caretaker
{
private:
    vector<Memento *> mementos_;
    Originator *originator_;

public:
    Caretaker(Originator *originator) : originator_(originator)
    {
    }

    ~Caretaker()
    {
        for (auto m : mementos_)
            delete m;
    }

    void Backup()
    {
        cout << "\nCaretaker: Saving Originator's state...\n";
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo()
    {
        if (!this->mementos_.size())
        {
            return;
        }
        Memento *memento = this->mementos_.back();
        this->mementos_.pop_back();
        cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
        try
        {
            this->originator_->Restore(memento);
        }
        catch (...)
        {
            this->Undo();
        }
    }
    void ShowHistory() const
    {
        cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento *memento : this->mementos_)
        {
            cout << memento->GetName() << "\n";
        }
    }
};

void ClientCode()
{
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    cout << "\n";
    caretaker->ShowHistory();
    cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->Undo();
    cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    ClientCode();
    return 0;
}