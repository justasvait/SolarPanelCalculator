#include "Building.h"
#include <string>
using namespace std;

// Constructors
Building::Building()
{
    index = 0;
    appliance = ' ';
    wattage = 0;
    usage = 0;
}
// Constructor with parameters
Building::Building( int inIndex, string inAppliance, float inWattage, float inUsage )
{
    index = inIndex;
    appliance = inAppliance;
    wattage = inWattage;
    usage = inUsage;
}

// Functions

void Building::setAppliance( int i, string name, float watts, float inUsage )
{
    index = i;
    appliance = name;
    wattage = watts;
    usage = inUsage;
}

int Building::getIndex()
{
    return index;
}
string Building::getAppliance()
{
    return appliance;
}
float Building::getWattage()
{
    return wattage;
}
float Building::getUsage()
{
    return usage;
}
