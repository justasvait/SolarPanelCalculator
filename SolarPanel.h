#ifndef SOLARPANEL_H_INCLUDED
#define SOLARPANEL_H_INCLUDED

class SolarPanel
{
private:
    float totalEnergy;
    float totalArea;
    float solarPanelWattage;
    int numberOfPanels;

public:
    // Constructors
    SolarPanel();
    SolarPanel( float inEnergy, float inArea, float inSPWattage, int inNoOfPanels );

    // Functions
    void setSolarPanel( float inEnergy, float inArea, float inSPWattage, int inNoOfPanels );
    float getTotalEnergy();
    float getTotalArea();
    float getSolarPanelWattage();
    int getNumberOfPanels();
};


#endif // SOLARPANEL_H_INCLUDED
