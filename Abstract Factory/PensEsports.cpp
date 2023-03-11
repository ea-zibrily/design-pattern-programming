#include <iostream>
#include <string.h>
using namespace std;

#pragma region Mobile Legends

// Abstract Product 1
class MobileLegends
{
private:
    string teamName;
    int totalTeamMember;
    string teamCaptain;

public:
    string GetName()
    {
        return teamName;
    }
    void SetName(string enterName)
    {
        teamName = enterName;
    }

    int GetMember()
    {
        return totalTeamMember;
    }
    void SetMember(int enterMemberCount)
    {
        totalTeamMember = enterMemberCount;
    }

    string GetCaptain()
    {
        return teamCaptain;
    }
    void SetCaptain(string enterCaptainNickname)
    {
        teamCaptain = enterCaptainNickname;
    }

    virtual void displayTeam() = 0;
};

// Concrete Product
class Legion : public MobileLegends
{
private:
public:
    void displayTeam() override
    {
        cout << "Team Name: " << GetName() << endl;
        cout << "Team Total Member: " << GetMember() << endl;
        cout << "Team Captain: " << GetCaptain() << endl;

        cout << endl;
        cout << "This team is Verified." << endl;
        cout << endl;
    }
};

class Reborn : public MobileLegends
{
private:
public:
    void displayTeam() override
    {
        cout << "Team Name: " << GetName() << endl;
        cout << "Team Total Member: " << GetMember() << endl;
        cout << "Team Captain: " << GetCaptain() << endl;

        cout << endl;
        cout << "This team is Verified." << endl;
        cout << endl;
    }
};

#pragma endregion

#pragma region Pens Esports

// Abstract Factory
class PensEsports
{
public:
    virtual MobileLegends *createTeam() = 0;
};

// Concrete Factory
class FirstTeam : public PensEsports
{
private:
    
public:
    MobileLegends *createTeam() override
    {
        return new Reborn();
    }
};

class SecondaryTeam : public PensEsports
{
private:
    
public:
    MobileLegends *createTeam() override
    {
        return new Legion();
    }
};

#pragma endregion

int main()
{
    PensEsports *pensEsports = new FirstTeam();
    MobileLegends *mobileLegends = pensEsports->createTeam();
    mobileLegends->SetName("Reborn");
    mobileLegends->SetMember(5);
    mobileLegends->SetCaptain("MIRZ");
    mobileLegends->displayTeam();

    return 0;
}