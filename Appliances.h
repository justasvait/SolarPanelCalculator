#ifndef APPLIANCES_H_INCLUDED
#define APPLIANCES_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


class Appliances
{
private:
    string name;
    float watts;
    int index;
public:
    // Constructors
    Appliances();
    Appliances( int no, string appliance_name, float wattage );
    // Functions
    void setAppliance( int no, string appliance_name, float wattage );

    int getIndex();
    string getName();
    float getWatts();
    void listAppliance();
};


#endif // APPLIANCES_H_INCLUDED
