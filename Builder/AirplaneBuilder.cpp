#include <iostream>
#include <string>
using namespace std;

// Product
class Airplane
{
public:
    Airplane(string customer, string type)
    {
        this->customer = customer;
        this->type = type;
    }

    Airplane SetWingspan(float wingspan)
    {
        this->wingspan = wingspan;
        return *this;
    }

    Airplane SetPowerplant(string powerplant)
    {
        this->powerplant = powerplant;
        return *this;
    }

    Airplane SetAvionics(string avionics)
    {
        this->avionics = avionics;
        return *this;
    }

    Airplane SetNumberSeats(int crewSeats, int passengerSeats)
    {
        this->crewSeats = crewSeats;
        this->passengerSeats = passengerSeats;
        return *this;
    }

    string GetCustomer()
    {
        return customer;
    }

    string GetType()
    {
        return type;
    }

    void AirplaneStatistic()
    {
        cout << "Customer: " << customer << endl;
        cout << "Airplane Type: " << type << endl;
        cout << "This Airplane is Ready to Deliver!" << endl;
        cout << endl;
    }

private:
    string type;
    float wingspan;
    string powerplant;
    int crewSeats;
    int passengerSeats;
    string avionics;
    string customer;
};

// Abstract Builder
class AirplaneBuilder
{
public:
    virtual ~AirplaneBuilder(){};

    Airplane *GetAirplane()
    {
        return airplane;
    }

    void CreateAirplane()
    {
        airplane = new Airplane(customer, type);
    }

    virtual void BuildWings() = 0;
    virtual void BuildPowerplant() = 0;
    virtual void BuildAvionics() = 0;
    virtual void BuildSeats() = 0;

protected:
    Airplane *airplane;
    string customer;
    string type;
};

// Concrete Builder
class CropDuster : public AirplaneBuilder
{
public:
    CropDuster(string customer)
    {
        this->customer = customer;
        this->type = "Crop Duster v3.4";
    }

    void BuildWings() override
    {
        airplane->SetWingspan(9.0);
    }

    void BuildPowerplant() override
    {
        airplane->SetPowerplant("Single Piston");
    }

    void BuildAvionics() override {}

    void BuildSeats() override
    {
        airplane->SetNumberSeats(1, 1);
    }
};

class FighterJet : public AirplaneBuilder
{
public:
    FighterJet(string customer)
    {
        this->customer = customer;
        this->type = "F-35 Lightning II";
    }

    void BuildWings() override
    {
        airplane->SetWingspan(35.0);
    }

    void BuildPowerplant() override
    {
        airplane->SetPowerplant("Dual Thrust Vectoring");
    }

    void BuildAvionics() override
    {
        airplane->SetAvionics("Military");
    }

    void BuildSeats() override
    {
        airplane->SetNumberSeats(1, 0);
    }
};

class Glider : public AirplaneBuilder
{
public:
    Glider(string customer)
    {
        this->customer = customer;
        this->type = "Glider v9.0";
    }

    void BuildWings() override
    {
        airplane->SetWingspan(57.1f);
    }

    void BuildPowerplant() override {}

    void BuildAvionics() override {}

    void BuildSeats() override
    {
        airplane->SetNumberSeats(1, 0);
    }
};

class Airliner : public AirplaneBuilder
{
public:
    Airliner(string customer)
    {
        this->customer = customer;
        this->type = "787 Dreamliner";
    }

    void BuildWings() override
    {
        airplane->SetWingspan(197);
    }

    void BuildPowerplant() override
    {
        airplane->SetPowerplant("Dual Turbofan");
    }

    void BuildAvionics() override
    {
        airplane->SetAvionics("Commercial");
    }

    void BuildSeats() override
    {
        airplane->SetNumberSeats(8, 289);
    }
};

// Director
class AirplaneDirector
{
public:
    void setAirplaneBuilder(AirplaneBuilder *builder)
    {
        airplaneBuilder = builder;
    }

    Airplane *getAirplane()
    {
        return airplaneBuilder->GetAirplane();
    }

    void constructAirplane()
    {
        airplaneBuilder->CreateAirplane();
        airplaneBuilder->BuildWings();
        airplaneBuilder->BuildPowerplant();
        airplaneBuilder->BuildAvionics();
        airplaneBuilder->BuildSeats();
    }

private:
    AirplaneBuilder *airplaneBuilder;
};

int main()
{
    AirplaneDirector director;
    AirplaneBuilder *cropDuster = new CropDuster("Farmer Joe");
    AirplaneBuilder *fighterJet = new FighterJet("The Navy");
    AirplaneBuilder *glider = new Glider("Tim Rice");
    AirplaneBuilder *airliner = new Airliner("United Airlines");

    // Build a crop duster
    director.setAirplaneBuilder(cropDuster);
    director.constructAirplane();
    Airplane *airplaneCropDuster = director.getAirplane();
    airplaneCropDuster->AirplaneStatistic();

    // Build a fighter jet
    director.setAirplaneBuilder(fighterJet);
    director.constructAirplane();
    Airplane *airplaneFighterJet = director.getAirplane();
    airplaneFighterJet->AirplaneStatistic();

    // Build a glider
    director.setAirplaneBuilder(glider);
    director.constructAirplane();
    Airplane *airplaneGlider = director.getAirplane();
    airplaneGlider->AirplaneStatistic();    

    // Build an airliner
    director.setAirplaneBuilder(airliner);
    director.constructAirplane();
    Airplane *airplaneAirliner = director.getAirplane();
    airplaneAirliner->AirplaneStatistic();

    return 0;
}