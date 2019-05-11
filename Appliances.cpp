#include "Appliances.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Constructor 1
Appliances::Appliances()
{
    index = 0;
    name = ' ';
    watts = 0;
}
// Constructor 2 (parameterised)
Appliances::Appliances( int no, string appliance_name, float wattsage )
{
    index = no;
    name = appliance_name;
    watts = wattsage;
}

// Functions
void Appliances::setAppliance( int no, string appliance_name, float wattsage )
{
    index = no;
    name = appliance_name;
    watts = wattsage;
}

int Appliances::getIndex()
{
    return Appliances::index;
}
string Appliances::getName()
{
    return Appliances::name;
}
float Appliances::getWatts()
{
    return Appliances::watts;
}
void Appliances::listAppliance()
{
    cout << setw(2) << Appliances::index << setw(25) << Appliances::name << setw(8) << watts << endl;
}
