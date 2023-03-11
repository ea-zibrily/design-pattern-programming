#include <iostream>
using namespace std;

#pragma region Mobile Legends Division

class MobileLegendsDivision
{
public:
    virtual void createTeam() = 0;
};

class EvosLegends : public MobileLegendsDivision
{
public:
    void createTeam() override
    {
        cout << "Evos Legends" << endl;
    }
};

class EvosIcon : public MobileLegendsDivision
{
public:
    void createTeam() override
    {
        cout << "Evos Icon" << endl;
    }
};

#pragma endregion

#pragma region Free Fire Division

class FreeFireDivision
{
    public:
    virtual void createTeam() = 0;
};

class EvosDivine : public FreeFireDivision
{
public:
    void createTeam() override
    {
        cout << "Evos Divine" << endl;
    }
};

class EvosCapital : public FreeFireDivision
{
public:
    void createTeam() override
    {
        cout << "Evos Capital" << endl;
    }
};

#pragma endregion

#pragma region Evos Esports

class AbstractEvosEsports
{
public:
    virtual MobileLegendsDivision *createMobileLegendsDivision() = 0;
    virtual FreeFireDivision *createFreeFireDivision() = 0;
};

class DivisionOne : public AbstractEvosEsports
{
public:
    MobileLegendsDivision *createMobileLegendsDivision() override
    {
        return new EvosLegends();
    }

    FreeFireDivision *createFreeFireDivision() override
    {
        return new EvosDivine();
    }
};

class DivisionTwo : public AbstractEvosEsports
{
    public:
    MobileLegendsDivision *createMobileLegendsDivision() override
    {
        return new EvosIcon();
    }

    FreeFireDivision *createFreeFireDivision() override
    {
        return new EvosCapital();
    }
};

#pragma endregion

int main()
{
    //first division
    AbstractEvosEsports *evosEsportsOne = new DivisionOne();
    MobileLegendsDivision *mobileLegendsDivision = evosEsportsOne->createMobileLegendsDivision();
    FreeFireDivision *freeFireDivision = evosEsportsOne->createFreeFireDivision();
    mobileLegendsDivision->createTeam();
    freeFireDivision->createTeam();

    return 0;
}
