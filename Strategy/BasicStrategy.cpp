#include <iostream>
#include <vector>
using namespace std;

// Abstract class for the strategy
class SortStrategy
{
public:
    virtual ~SortStrategy() {}
    virtual void sort(vector<int> &data) = 0;
};

// Concrete strategy for quicksort
class QuickSort : public SortStrategy
{
public:
    void sort(vector<int> &data) override
    {
        // implementation of quicksort algorithm
        cout << "Sorting using QuickSort algorithm." << endl;
    }
};

// Concrete strategy for mergesort
class MergeSort : public SortStrategy
{
public:
    void sort(vector<int> &data) override
    {
        // implementation of mergesort algorithm
        cout << "Sorting using MergeSort algorithm." << endl;
    }
};

// Context class that uses the strategy
class Sorter
{
public:
    Sorter(SortStrategy *strategy) : m_strategy(strategy) {}

    void setStrategy(SortStrategy *strategy)
    {
        m_strategy = strategy;
    }

    void sort(vector<int> &data)
    {
        m_strategy->sort(data);
    }

private:
    SortStrategy *m_strategy;
};

// Example usage
int main()
{
    vector<int> data = {3, 1, 4, 2, 5};
    Sorter sorter(new QuickSort()); // create context with quicksort strategy
    sorter.sort(data);

    sorter.setStrategy(new MergeSort()); // switch to mergesort strategy
    sorter.sort(data);

    return 0;
}