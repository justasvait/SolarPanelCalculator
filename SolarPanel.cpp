#include "SolarPanel.h"

using namespace std;

// Constructors
SolarPanel::SolarPanel()
{
    totalEnergy = 0;
    totalArea = 0;
    solarPanelWattage = 0;
    numberOfPanels = 0;
}
SolarPanel::SolarPanel( float inEnergy, float inArea, float inSPWattage, int inNoOfPanels )
{
    totalEnergy = inEnergy;
    totalArea = inArea;
    solarPanelWattage = inSPWattage;
    numberOfPanels = inNoOfPanels;
}

// Functions
    void SolarPanel::setSolarPanel( float inEnergy, float inArea, float inSPWattage, int inNoOfPanels )
    {
        totalEnergy = inEnergy;
        totalArea = inArea;
        solarPanelWattage = inSPWattage;
        numberOfPanels = inNoOfPanels;
    }
    float SolarPanel::getTotalEnergy()
    {
        return totalEnergy;
    }
    float SolarPanel::getTotalArea()
    {
        return totalArea;
    }
    float SolarPanel::getSolarPanelWattage()
    {
        return solarPanelWattage;
    }
    int SolarPanel::getNumberOfPanels()
    {
        return numberOfPanels;
    }
