#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Building
{
private:
    int index;
    string appliance;
    float wattage;
    float usage;
public:
    // Constructors
    Building();
    Building( int i, string name, float inWattage, float usage );

    // Functions
    void setAppliance( int i, string name, float watts, float inUsage );

    int getIndex();
    string getAppliance();
    float getWattage();
    float getUsage();
};



#endif // BUILDING_H_INCLUDED
