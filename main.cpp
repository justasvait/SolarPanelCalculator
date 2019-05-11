/*  SOLAR PANEL APPLICATION
    The application is created for ACS223 Computer Systems and Applications assignment
    (ACS223-002), The University of Sheffield.

    Description: The program estimates power consumption of the house by getting information from the user.
                 Upon user's choice on the season, the program calculates solar power needed. Dependent on user's preferences
                 on solar panel size, it calculates the number of solar panels required to cover the house with enough power.

    Author Reg. No.: 150148030
    Date: 31/10/2016 - 14/11/2016
*/
#include "Appliances.h"     // header files
#include "SolarPanel.h"     //
#include "Building.h"       //

#include <iostream>         // In-built libraries
#include <string>           //
#include <iomanip>          //
#include <fstream>          //
using namespace std;

#define ITEMS_IN_LIST 38    // Number of defined common appliances in the text file

// Functions
void cleanCin ();
void sortArray ( int anArray[], int length );
void sortArray ( float anArray[], int length );
void removeDuplicates ( int anArray[], int &length );
void removeDuplicates( float anArray[], int &length );

bool inputFromFile ( Appliances appliance[] );
bool inputSeason ();
void inputAppliances ( Appliances appliance[], Building abuilding[], int &numberOfAppliances );
float estimateTotalPower( bool summer, Building abuilding[], int counter );
void threeScenarios ( bool summer, float totalEstimatedPower, SolarPanel aSolarPanel[] );


// Main
int main()
{
    // Initialisation
    int i;  // indexes
    bool summer;    // variable to store user's choice for seasons
                    // (true- summer; false- winter)
    bool error;     // used to break program in case of an error
    int numberOfAppliances = 0;     // variable to store number of appliances in the house
    float totalEstimatedPower = 0;  // variable to store estimated power consumption for the house

    Appliances appliance[ITEMS_IN_LIST];    // definition of classes
    Building abuilding[ITEMS_IN_LIST];      //
    SolarPanel aSolarPanel[3];              //

    // Start of the program
    error = inputFromFile( appliance );     // Function to import data from a text file to the array of classes.
    if ( !error )
    {
        summer = inputSeason();                 // Function to get a boolean variable of user's choice for season.
        inputAppliances( appliance, abuilding, numberOfAppliances );    // Function to get appliances from the list and their usage.

        // Print the data of the house described by user
        cout << "No.                    Name   watts   Usage" << endl;
        for ( i=0; i<numberOfAppliances; i++ )
        {
            cout << setw(2) << abuilding[i].getIndex() << setw(25) << abuilding[i].getAppliance() << setw(8) <<
                    abuilding[i].getWattage() << setw(8) << setprecision(4) << abuilding[i].getUsage() << endl;
        }

        // Calculate estimate power requirements
        totalEstimatedPower = estimateTotalPower( summer, abuilding, numberOfAppliances );
        cout << "Total estimated power consumption in the building is: " << fixed << setprecision(4) << totalEstimatedPower << "W" << endl <<
                string(54,' ') << totalEstimatedPower/1000 << "kW" << endl <<
                string(54,' ') << totalEstimatedPower/10000000 << "MW" << endl;
        cout.unsetf(ios_base::floatfield);                          // resets cout format to default

        // Three scenarios of user's choice
        threeScenarios ( summer, totalEstimatedPower, aSolarPanel );

        cout << string(3,'\n') << string(65,'-') << endl;
        cout << string(22,'\\') << " SOLAR POWER SYSTEM " << string(23, '/') << endl;
        cout << string(65,'-') << endl;
        cout << "Wattage(Watts) | Number of panels | Area of panels(square metres)" << endl;
        for ( i=0; i<3; i++ )
        {
            cout << fixed << setw(8) << setprecision(0) << aSolarPanel[i].getSolarPanelWattage() << "       |" <<
                    setw(10) << aSolarPanel[i].getNumberOfPanels() << "        |" <<
                    setw(18) << setprecision(4) << aSolarPanel[i].getTotalArea() << endl;
        }
        cout << string(65,'-') << string(13,'\n');
    }
    else
        cout << "\nTHE FILE IS NOT FOUND. THE PROGRAM IS TERMINATED!" << endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Functions:

void cleanCin ()
{
    // CLEAN CIN //
    ///////////////
    // A function which cleans any remaining inputs from keyboard.
    //      -Used to protect from buffer input.

    cin.clear();
    cin.ignore(256,'\n');
}
void sortArray ( int anArray[], int length )
{
    // SORT ARRAY //
    ////////////////
    // Function to sort integer array.
    //      -Need 2 inputs: array and its length.

    int i, j;
    int temp;
    for ( i=0; i<length-1; i++ )
    {
        for ( j=i+1; j<length; j++ )
        {
            if ( anArray[i] > anArray[j] )
            {
                temp = anArray[i];
                anArray[i] = anArray[j];
                anArray[j] = temp;
            }
        }
    }
}
void sortArray ( float anArray[], int length )
{
    // SORT ARRAY //
    ////////////////
    // Function to sort float array.
    //      -Need 2 inputs: array and its length.

    int i, j;
    float temp;
    for ( i=0; i<length-1; i++ )
    {
        for ( j=i+1; j<length; j++ )
        {
            if ( anArray[i] > anArray[j] )
            {
                temp = anArray[i];
                anArray[i] = anArray[j];
                anArray[j] = temp;
            }
        }
    }
}
void removeDuplicates ( int anArray[], int &length )
{
    // REMOVE DUPLICATES //
    ///////////////////////
    // Function to remove duplicate integers to get a new list with unique values.
    //      -Need 2 inputs: array and its length.
    //      -Function updates the length.

    sortArray( anArray, length );
    int i, j;
    for ( i=0; i<length-1; i++ )
    {
        if ( anArray[i] == anArray[i+1] )
        {
            for ( j=i+1; j<length-1; j++ )
            {
                anArray[j] = anArray[j+1];
            }
            length--;
            i--;
        }
    }
}
void removeDuplicates ( float anArray[], int &length )
{
    // REMOVE DUPLICATES //
    ///////////////////////
    // Function to remove duplicate floats to get a new list with unique values.
    //      -Need 2 inputs: array and its length.
    //      -Function updates the length.

    sortArray( anArray, length );
    int i, j;
    for ( i=0; i<length-1; i++ )
    {
        if ( anArray[i] == anArray[i+1] )
        {
            for ( j=i+1; j<length-1; j++ )
            {
                anArray[j] = anArray[j+1];
            }
            length--;
            i--;
        }
    }
}

bool inputFromFile ( Appliances appliance[] )
{
    // INPUTS //
    ////////////
    // Function to import data from a text file to the array of classes.
    //      The text file contains with index, name and wattage.
    //      The input is only accepted, if the file is opened and correctly read.

    string input_name;  // temporary variables to store data from file
    float input_watts;  //
    int index;          //

    bool error = false; // error variable, used to stop program in case of failure to open the file.

    ifstream InputFile;
    InputFile.open("AppliancePower.txt");

    if ( InputFile.is_open() )
    {
        while ( !InputFile.eof() )
        {
            InputFile >> index >> input_name >> input_watts;

            if ( !InputFile.fail() )
            {
                appliance[index - 1].setAppliance( index, input_name, input_watts );
            }
        }
    }
    else
    {
        cout << "Error! File \"AppliancePower.txt\" could not be found." << endl;
        error = true;
    }
    InputFile.close();
    return error;
}

bool inputSeason ()
{
    // INPUT SEASON //
    //////////////////
    // Function to get a boolean variable of user's choice for season.
    //      Boolean equal to 1 (true) - summer.
    //      Boolean equal to 0 (false) - winter.

    bool summer;
    string validate;

    cout << "Enter preferred season (1 - summer and 0 - winter): " << endl;

    cin >> validate;
    while ( validate != "1" && validate != "0" )
    {
        cout << "Error! Your choice was not recognised, please try again.\n" << endl;
        cleanCin();
        cin >> validate;
    }
    if ( validate == "1" )
        {
            cout << "Your chosen seasons is summer.\n\n" << endl;
            summer = true;
        }
    else
        {
            cout << "Your chosen seasons is winter.\n\n" << endl;
            summer = false;
        }
    cleanCin();
    return summer;
}

void inputAppliances ( Appliances appliance[], Building abuilding[], int &numberOfAppliances )
{
    // INPUT APPLIANCES //
    //////////////////////
    // Function to get appliances from the list and their usage.
    //      -User enters indexes of appliance to add the to house appliance list.
    //      -User is required to enter daily time (in hours) usage of appliances.
    //      -Information is stored in building class.

    int i;
    int user_picks[ITEMS_IN_LIST] = {0};
    float validate;
    float inUsage;

    cout << "Enter appliances, which are used in the house:\n" << endl;
    cout << endl << "NOTE:\tto select item, write the item index to the command prompt.";
    cout << "\n\tTo add more items, separate numbers by space or the enter key.\n\tWrite 0 to stop." << endl << endl;
    for ( i=0; i<ITEMS_IN_LIST; i++ )
    {
        cout << setw(2) << appliance[i].getIndex() << setw(25) << appliance[i].getName();
        i++;
        if ( i < ITEMS_IN_LIST )
            cout << setw(5) << "|" << setw(4) << appliance[i].getIndex() << setw(25) << appliance[i].getName() << endl;
        else
            cout << endl;
    }

    i = 0;
    do
    {
        if ( cin.fail() )
        {
            cleanCin();
            cout << "Error! Your choice was not recognised, please try again." << endl;
        }
        cin >> validate;

        if ( validate > 0 && validate <= ITEMS_IN_LIST && validate == int(validate) )
        {
            user_picks[i] = validate;
            cout << "Your choice '" << user_picks[i] << "' is accepted." << endl;
            i++;
        }
        else if ( validate != 0 )
            cout << "Error! Your choice was not recognised, please try again." << endl;
    }
    while ( validate != 0 || cin.fail() );

    // sort and remove duplicates in the list
    numberOfAppliances = i;
    removeDuplicates( user_picks, numberOfAppliances );

    // Adding the list to a building class
    cout << "Number of appliances: " << numberOfAppliances << endl;

    for ( i=0; i<numberOfAppliances; i++ )
    {
        cout << "Enter daily usage of \"" << appliance[ user_picks[i]-1 ].getName() << "\" appliance in hours:" << endl;

        cin >> inUsage;
        while ( cin.fail() || inUsage <= 0 || inUsage > 24 )
        {
            if ( cin.fail() )
            {
                cout << "Error! Your choice was not recognised, please try again." << endl;
            }
            else if ( inUsage <= 0 || inUsage > 24 )
            {
                cout << "Error! Your choice is out of range (0-24h, exclusive 0), please try again." << endl;
            }
            cleanCin();
            cin >> inUsage;
        }

    abuilding[i].setAppliance( i+1 /*index*/,
                              appliance[ user_picks[i]-1 ].getName() /*appliance name*/,
                              appliance[ user_picks[i]-1 ].getWatts() /*wattage*/,
                              inUsage /*usage*/ );
    }
}

float estimateTotalPower( bool summer, Building abuilding[], int counter )
{
    // ESTIMATE TOTAL POWER //
    //////////////////////////
    // Function to estimate solar power required for the building.
    //      -If user selected summer season, the total household power required is divided by 6,
    //       as solar panels get average of 6 hours of sunlight per day.
    //      -If user selected - winter, the solar power required is the same as household power
    //       required (i.e. 1h sunlight per day).

    float total = 0;
    int i;

    for ( i=0; i<counter; i++ )
    {
        total += abuilding[i].getUsage() * abuilding[i].getWattage();
    }
    if ( summer == 1 )
        total = total / 6;

    return total;
}

void threeScenarios ( bool summer, float totalEstimatedPower, SolarPanel aSolarPanel[] )
{
    // THREE SCENARIOS //
    /////////////////////
    // Function which asks user to enter 3 different variations of panel size, then it calculates
    // the number of panels of selected size is required to cover estimated power needs.
    //      -User is only allowed to select 3 choices from 6:
    //          -Available choices are 10, 40, 80, 100, 150, 250 (Watts).
    //          -Size of solar panels are 0.0938, 0.312, 0.5978, 0.6968, 0.9983, 1.65 (square metres) respectively.
    //      -The information is sent back and stored to solarPower class.

    int i, temp;
    int noOfPanels = 0;
    int wattage;
    float areaOfPanels = 0;
    float scenario[4];

    // User input
    cout << "Enter 3 solar panel options from the list:" << endl;
    cout << "1   10W \n2   40W \n3   80W \n4   100W \n5   150W \n6   250W" << endl;

    for ( i=0; i<3; i++ )
    {
        cin >> scenario[i];
        while ( cin.fail() || scenario[i] < 1 || scenario[i] > 6 || scenario[i] != int( scenario[i] ) )
        {
            cout << "Error! Your choice was not recognised, please try again." << endl;
            cleanCin();
            cin >> scenario[i];
        }
        temp = i + 1;
        removeDuplicates( scenario, temp );
        if ( temp == i + 1 )
            cout << "Your choice \"" << scenario[i] << "\" is accepted." << endl;
        else
        {
            i--;
            cout << "You already have chosen this size of panel, please try again." << endl;
        }
    }

    // Number of solar panels and area required
    for ( i=0; i<3; i++ )
    {
        switch ( int( scenario[i] ) )
        {
        case 1:
            wattage = 10;
            noOfPanels = totalEstimatedPower / wattage;     // number of panels of size 10W required
            areaOfPanels = noOfPanels * 0.0938;             // total area of panels required
            break;
        case 2:
            wattage = 40;
            noOfPanels = totalEstimatedPower / wattage;     // number of panels of size 40W required
            areaOfPanels = noOfPanels * 0.312;              // total area of panels required
            break;
        case 3:
            wattage = 80;
            noOfPanels = totalEstimatedPower / wattage;     // number of panels of size 80W required
            areaOfPanels = noOfPanels * 0.5978;             // total area of panels required
            break;
        case 4:
            wattage = 100;
            noOfPanels = totalEstimatedPower / wattage;     // number of panels of size 100W required
            areaOfPanels = noOfPanels * 0.6968;             // total area of panels required
            break;
        case 5:
            wattage = 150;
            noOfPanels = totalEstimatedPower / wattage;     // number of panels of size 150W required
            areaOfPanels = noOfPanels * 0.9983;             // total area of panels required
            break;
        case 6:
            wattage = 250;
            noOfPanels = totalEstimatedPower / wattage;     // number of panels of size 250W required
            areaOfPanels = noOfPanels * 1.65;               // total area of panels required
            break;
        default:
            wattage = 0;                                    //
            noOfPanels = 0;                                 // in case of a fault, set the values to 0.
            areaOfPanels = 0;                               //
        }

        // Store the data to a solar panel class
        aSolarPanel[i].setSolarPanel( totalEstimatedPower, areaOfPanels, wattage, noOfPanels );
    }
}
