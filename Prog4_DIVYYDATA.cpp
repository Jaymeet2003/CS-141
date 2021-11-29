/* program_4.cpp
    Divvy Bike Data Analysis program.
    Author: Chris Fulton
    Date: 10/18/2021
    Class: CS 141, Fall 2021, UIC
    System: Visual Studio 2019 IDE Windows
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <cstring>    // For C string function strcpy
#include <algorithm>  // use of vector algorithms
#include <cmath>      // For trig functions used in finding distance between points
#include <iomanip>    // For setting precision of floating point number display
using namespace std;

// Struct corresponds to fields in csv data file supplied by Divvy.
// For instance the header row and the first row of data look like the following:
// ride_id,rideable_type,started_at,ended_at,start_station_name,end_station_name,start_lat,start_lng,end_lat,end_lng,member_casual
// E07475A697F1E70B,classic_bike,9/1/21 0:13,9/1/21 0:15,Clark St & Chicago Ave,Clark St & Elm St,41.89675,-87.63089,41.902973,-87.63128,member

struct DivvyRide {
    string ride_id;         // Unique value for each ride as a large hexadecimal number
    string rideable_type;   // classic_bike, electric_bike, or docked_bike
    string started_at;      // Starting date and time, e.g.   9/1/2021  12:13:00 AM
    string started_at_date; //    separated started_at field to extract date e.g. 9/1/2021
    string started_at_time; //    separated started_at field to extract time e.g. 12:13:00 AM
    string ended_at;        // Ending date and time, e.g.   9/1/2021  12:15:00 AM
    string ended_at_date;   //    separated ended_at field to extract date e.g. 9/1/2021
    string ended_at_time;   //    separated ended_at field to extract time e.g. 12:15:00 AM
    string start_station_name;   // Station name, e.g.  Clark St & Chicago Ave
    string end_station_name;     // Station name, e.g. Clark St & Elm St
    string start_lat;       // Starting latitude, e.g. 41.89675
    string start_lng;       // Starting longitude, e.g. -87.63089
    string end_lat;         // Ending latitude, e.g. 41.902973
    string end_lng;         // Ending longitude, e.g. -87.63128
    string member_casual;   // member or casual
};

//New struct created for extra credit
struct NearestDivvyRide {
    string location;
    long double startlat;
    long double startlng;
    double miles;
};


//---------------------------------------------------------------------------------
// Read the contents of CSV file into a vector
void readCVSFile( vector<DivvyRide>& dataStore)
{
    // DataStore vector should be empty before adding records
    dataStore.clear();

    string inputLine, rideableTypetempString, rideStartedTempString, rideEndedTempString,
           rideStartStationTempString, rideEndStationTempString,
           rideStartLatTempString, rideStartLongTempString,
           rideEndLatTempString, rideEndLongTempString,
           rideMemberTempString;
    char fileName[ 81];
    int csvSheetSelection;

    ifstream inStream;

    cout << "   Select datafile: \n"
         << "      1. Small subset of data with 14 rides to help create your program\n"
         << "      2. Week day vs weekend rides\n"
         << "      3. All September 2021 data (not tested in Zybooks)\n"
         << "   Your selection--> ";
    cin >> csvSheetSelection;

    switch (csvSheetSelection) {
        case 1:
            strcpy(fileName,"divvyridesampledata.csv");
            break;
        case 2:
            strcpy(fileName,"weekdayweekend.csv");
            break;
        case 3:
            strcpy(fileName,"all_divvy_rides_september.csv");
            break;
        default: cout << "Invalid value.  Exiting Program.";
            exit(-1);
            break;
    }

    inStream.open( fileName);
    assert(inStream.fail() == false);
    
    // Declare DivvyRide variable from DivvyRide struct
    DivvyRide aRide;

    // First read in the title line with field titles
    getline(inStream, inputLine);
    
    // Read in a whole line at a time and parse strings out of it for the various fields
    while( getline(inStream, inputLine)) {
        // Extract ride_id
        aRide.ride_id = inputLine.substr(0, inputLine.find(','));

        rideableTypetempString = inputLine.substr(inputLine.find(',') + 1);
        aRide.rideable_type = rideableTypetempString.substr(0, rideableTypetempString.find(','));

        //Temporary String to find started_at_time
        rideStartedTempString = rideableTypetempString.substr(rideableTypetempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value
        aRide.started_at = rideStartedTempString.substr(0, rideStartedTempString.find(','));
        aRide.started_at_date = aRide.started_at.substr(0, aRide.started_at.find(' ')); //Extract the date from started_at field
        aRide.started_at_time = aRide.started_at.substr((aRide.started_at.find(' ') + 1), aRide.started_at.find(','));

        //Temporary String to find ended_at_time
        rideEndedTempString = rideStartedTempString.substr(rideStartedTempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value
        aRide.ended_at = rideEndedTempString.substr(0, rideEndedTempString.find(','));
        aRide.ended_at_date = aRide.ended_at.substr(0, aRide.ended_at.find(' ')); //Extract the date from started_at field
        aRide.ended_at_time = aRide.ended_at.substr((aRide.ended_at.find(' ') + 1), aRide.ended_at.find(','));

        //Temporary String to find start_station_name
        rideStartStationTempString = rideEndedTempString.substr(rideEndedTempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value
        aRide.start_station_name = rideStartStationTempString.substr(0, rideStartStationTempString.find(','));

        //Temporary String to find end_station_name
        rideEndStationTempString = rideStartStationTempString.substr(rideStartStationTempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value
        aRide.end_station_name = rideEndStationTempString.substr(0, rideEndStationTempString.find(','));
        //cout << aRide.end_station_name << endl;

        //Temporary String to find start_lat
        rideStartLatTempString = rideEndStationTempString.substr(rideEndStationTempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value - We also convert into long data type
        aRide.start_lat = rideStartLatTempString.substr(0, rideStartLatTempString.find(','));

        //Temporary String to find start_lng
        rideStartLongTempString = rideStartLatTempString.substr(rideStartLatTempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value - We also convert into long data type
        aRide.start_lng = rideStartLongTempString.substr(0, rideStartLongTempString.find(','));

        //Temporary String to find end_lat
        rideEndLatTempString = rideStartLongTempString.substr(rideStartLongTempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value - We also convert into long data type
        aRide.end_lat = rideEndLatTempString.substr(0, rideEndLatTempString.find(','));

        //Temporary String to find end_lng
        rideEndLongTempString = rideEndLatTempString.substr(rideEndLatTempString.find(',') + 1);
        //Get the # of characters until the next comma deliminated value - We also convert into long data type
        aRide.end_lng = rideEndLongTempString.substr(0, rideEndLongTempString.find(','));

        //Temporary String to find member_casual
        rideMemberTempString = rideEndLongTempString.substr(rideEndLongTempString.find(',') + 1);
        // This is the last deliminated value so I use string length to get index of the end of the string,
        // and then subtract 1 because we don't want the newline character (included by getline) to be included.
        aRide.member_casual = rideMemberTempString.substr(0, rideMemberTempString.length() - 1);

        //Add data assigned to DivvyRide struct members to dataStore Vector
        dataStore.push_back(aRide);
    }

    // Display total number of trips in the data
    cout << "   Total # of trips found in datafile:  " << dataStore.size() << endl;

    //close stream
    inStream.close();
} // end readCVSFile()


//---------------------------------------------------------------------------------
// Clean the data so it only includes records with data in each column
void cleanData(
         vector<DivvyRide> dataStore,        // Original vector with all rides
         vector<DivvyRide>& cleanDataStore)  // Vector to be created here, with only complete rides
{
    //cleanDataStore vector should be empty before adding records
    cleanDataStore.clear();

    //Looping structure to iterate through each item in dataStore vector
    for (int x = 0; x < dataStore.size(); x++) {
        // Single Alternative decision structure to determine if any of the columns are empty
        if( (!dataStore.at(x).ride_id.empty()) && (!dataStore.at(x).rideable_type.empty()) &&
            (!dataStore.at(x).started_at.empty()) && (!dataStore.at(x).ended_at.empty()) &&
            (!dataStore.at(x).start_station_name.empty()) && (!dataStore.at(x).end_station_name.empty()) &&
            (!dataStore.at(x).start_lat.empty()) && (!dataStore.at(x).start_lng.empty()) &&
            (!dataStore.at(x).end_lat.empty()) && (!dataStore.at(x).end_lng.empty()) &&
            (!dataStore.at(x).member_casual.empty())
          ) {
            //Add only dataStore vector items that have data in each column.
            cleanDataStore.push_back(dataStore.at(x));
        }
    }
    
    //Output the total number of records found in clean data
    cout << "   Total # of trips in clean data:  " << cleanDataStore.size() << endl;
} // end cleanData()


//---------------------------------------------------------------------------------
// The nexts two functions are utility functions for getting distance
// between two map longitude,latitude points.
// Attribution: https://www.geeksforgeeks.org/program-distance-two-points-earth/
// Convert degrees to radians
long double toRadians(const long double degree)
{
    // cmath library in C++ defines the constant M_PI as the value of pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
} // end toRadians()


//---------------------------------------------------------------------------------
// Given the longitude and latitude of two points, find and return the distance
// between those two points.
long double distance(
               long double lat1, long double long1,   // longitude and latitude of point 1
               long double lat2, long double long2)   // longitude and latitude of point 2
{
    // Convert the latitudes and longitudes from degree to radians.
    lat1 = toRadians( lat1);
    long1 = toRadians( long1);
    lat2 = toRadians( lat2);
    long2 = toRadians( long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow( sin( dlat / 2), 2) +
        cos( lat1) * cos( lat2) *
        pow( sin( dlong / 2), 2);

    ans = 2 * asin( sqrt(ans));

    // Radius of Earth in Kilometers, R = 6371.  Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
} // end distance()


//---------------------------------------------------------------------------------
// Function to get average trip duration and longest trip by miles
void findTripLengthData(
      vector<DivvyRide> cleanDataStore, // Cleaned data
      double& average,                  // Average trip length, to be computed
      double& longestTripByMiles,       // Longest trip length, to be computed
      DivvyRide& longestTripInfo,       // Longest trip information to be found
      double& total)                    // Total of all trips length, to be computed
{
    vector<long double> tripLength;
    double totalMiles = 0.0;
    long double startLat, startLng, endLat, endLng;

    //Loop through vector of Divvy Trips and call the utility function to get distance in miles
    for (int n = 1; n < cleanDataStore.size(); n++) {
        //convert string variables into long double data type
        startLat = stold(cleanDataStore.at(n).start_lat);
        startLng = stold(cleanDataStore.at(n).start_lng);
        endLat = stold(cleanDataStore.at(n).end_lat);
        endLng = stold(cleanDataStore.at(n).end_lng);

        //call distance function to calculate miles traveled
        totalMiles = distance(startLat, startLng, endLat, endLng);
        
        //increment the total amount of miles for all trips which will be used to calculate the average
        total += totalMiles;

        //Decision structure to determine the longest trip
        if (totalMiles >= longestTripByMiles) {
            longestTripByMiles = totalMiles;
            longestTripInfo = cleanDataStore.at(n);
        }
    }
    //Computes the average miles traveled
    average = total / cleanDataStore.size();
} // end findTripLengthData()


//---------------------------------------------------------------------------------
// Display cleaned general data
void displayTripLengthData(
         vector<DivvyRide> cleandDataStore, // Vector of clean data
         double avgTripLength,              // Pre-computed average trip length
         double longestTrip,                // Pre-computed longest trip
         DivvyRide longestTripInfo,         // Trip information for longest trip
         double totalMiles)                 // Total Divvy miles travelled
{
    cout << "\n"
         << "\n"
         << "   Total # of miles traveled: " << setprecision( 0) << fixed << totalMiles <<  "\n"
         << "   Average length of trips in miles:  " << setprecision( 1) << fixed << avgTripLength <<  "\n"
         << "   \n"
         << "   Longest trip information below: " <<  "\n"
         << "   -------------------------------"  <<  "\n"
         << "   Trip ID: " << longestTripInfo.ride_id <<  "\n"
         << "   Trip start location: " << longestTripInfo.start_station_name <<  "\n"
         << "   Trip end location: " << longestTripInfo.end_station_name << "\n"
         << "   Trip distance in miles: " << setprecision( 1) << fixed  << longestTrip << "\n"
         << endl;
} // end displayTripLengthData()


//---------------------------------------------------------------------------------
// Dataset is taken from Divvy data from September 2021, which has the following
// calendar days:
//     S  M  T  W  T  F  S
//              1  2  3  4
//     5  6  7  8  9 10 11
//    12 13 14 15 16 17 18
//    19 20 21 22 23 24 25
//    26 27 28 29 30
//
// Weekend days (Sat or Sun) are: 4,5,11,12,18,19,25,26
// If day is on a weekend, return true, else return false
bool isWeekend( int day)
{
    int weekendDays[ 8] = {4,5,11,12,18,19,25,26};
    bool isWeekend = false;
    
    // See if day is one of the weekend days.  If so, return true
    for( int i=0; i<8; i++) {
        if( day == weekendDays[ i]) {
            isWeekend = true;
            break;      // Break out of enclosing loop
        }
    }
    
    return isWeekend;
} //end isWeekend()


//---------------------------------------------------------------------------------
// Function to tally rides by time-of-day range
void weekdayWeekendAnalysis( vector<DivvyRide> cleanDataStore)
{
    int howManyRidesWeekday[ 24];  // Store how many rides in each hour of the day for the weekDAY
    int howManyRidesWeekend[ 24];  // Store how many rides in each hour of the day for the weekEND
    // Initialize counts to all zeros
    for( int i=0; i<24; i++) {
        howManyRidesWeekday[ i] = 0;
        howManyRidesWeekend[ i] = 0;
    }
    
    // For each trip find the start time and accumulate how many trips start in each hour of the day.
    // Separate this by weekday or weekend.
    for (int i = 0; i < cleanDataStore.size(); i++) {
        // Convert time string to numeric value.  First separate out the hours
        string theTime = cleanDataStore.at(i).started_at_time;
        string hoursString = theTime.substr( 0, theTime.find(":"));
        int hours = stoi( hoursString);
        
        //                                                               01234
        // Extract day of the month from the started_at_date, of format "9/21/2021"
        string theDate = cleanDataStore.at( i).started_at_date;
        long int firstSlash = theDate.find("/");            // Find index of first '/'
        long int dateLength = theDate.find_last_of("/") - firstSlash - 1;   // Calculate length of date
        string dayString = theDate.substr( firstSlash + 1, dateLength);
        int day = stoi( dayString);     // Convert string e.g. "21" to integer e.g. 21
        
        // Increment the appropriate hours counter, either for weekend or week day
        if( isWeekend( day)) {
            // Was on weekend
            howManyRidesWeekend[ hours]++;
            
        }
        else {
            // Was on week day (Mon..Fri)
            howManyRidesWeekday[ hours]++;
        }
    }
    
    // Find out the largest number of rides, so we can scale our counts for a 50 column display
    int largestNumberOfRides = 0;
    // Step through all 24 hours, for both weekday and weekend, finding the largest count value.
    for( int i=0; i<24; i++) {
        if( howManyRidesWeekday[ i] > largestNumberOfRides) {
            largestNumberOfRides = howManyRidesWeekday[ i];
        }
        if( howManyRidesWeekend[ i] > largestNumberOfRides) {
            largestNumberOfRides = howManyRidesWeekend[ i];
        }
    }
    
    // Display the counts
    int displayType;
    cout << "   Select type of display: \n"
         << "      1. Counts of rides per hour in the day\n"
         << "      2. Proportional 50 column graph with @ for weekday and + for weekend\n"
         << "   Your selection--> ";
    cin >> displayType;
    
    if( displayType == 1) {
        // Display counts per hour
        cout << "   LargestNumberOfRides is: " << largestNumberOfRides << endl;
        cout << "   Rides per hour for weekday and weekend:" << endl;
        for( int i=0; i<24; i++) {
            cout << "   " << setw( 2) << i << ":" << setw( 7) << howManyRidesWeekday[ i] << setw( 7) << howManyRidesWeekend[ i] << endl;
        }
    }
    else if( displayType == 2) {
        // Display proportional graph of counts per hour
        const int displayWidth = 50;       // 50 column display for graph
        for( int i=0; i<24; i++) {
            int weekdayValue = 1.0 * howManyRidesWeekday[ i] / largestNumberOfRides * displayWidth;
            int weekendValue = 1.0 * howManyRidesWeekend[ i] / largestNumberOfRides * displayWidth;
            cout << "   " << setw( 2) << i << ": " << setw( weekdayValue) << setfill('@') << " " << endl
                 << "       "                         << setw( weekendValue) << setfill('+') << " "
                 << setfill(' ') << endl;
        }
    }
    else {
        cout << "Invalid type of display for ride hours.  Exiting program.\n";
        exit( -1);
    }
} // end weekendWeekendAnalysis()


//---------------------------------------------------------------------------------
// Function to calculate percentage of casual riders and member riders
void casualMemberAnalysis( vector<DivvyRide> cleanDataStore)
{
    double casualCount = 0.0, memberCount = 0.0;
    double casualPercentage, memberPercentage;

    // Iterate through clean data store to get member and casual count
    for (int i = 0; i < cleanDataStore.size(); i++) {
        if( cleanDataStore.at(i).member_casual == "member") {
            //increment member count
            memberCount++;
        }
        else if( cleanDataStore.at(i).member_casual == "casual") {
            //increment casual count
            casualCount++;
        }
        else {
            cout << "Error, member data was: " << cleanDataStore.at(i).member_casual
                 << " with length " << cleanDataStore.at(i).member_casual.length()
                 << " Exiting program."
                 << endl;
            exit( -1);
        }
    }
    //Calculate percentage
    casualPercentage = (casualCount / (double)cleanDataStore.size()) * 100;
    memberPercentage = (memberCount / (double)cleanDataStore.size()) * 100;
    cout << "\n"
         << "   Casual Rider Percentage: " << setprecision( 1) << fixed << casualPercentage << "%\n"
         << "   Member Rider Percentage: " << setprecision( 1) << fixed << memberPercentage << "%\n"
         << endl;
} // end casualMemberAnalysis()


//---------------------------------------------------------------------------------
// Utility compare function used as part of built-in sort for Struct items
bool compare(NearestDivvyRide a, NearestDivvyRide b)
{
    return a.miles < b.miles;
}


//---------------------------------------------------------------------------------
// For extra credit find the closest Divvy bike location to the user-input
// latitude,longitude location and display its location, latitude,longitude and distance.
void getClosestDivvyLocation( vector<DivvyRide> cleanDataStore)
{
    NearestDivvyRide theStation;
    long double homeLat, homeLng;

    //get user latitude and longitutde
    cout << "   Input latitude and longitude of the home: ";
    cin >> homeLat >> homeLng;
    cout << "   You entered: " << homeLat << " for latitude and " << homeLng << " for longitude" << endl;

    // Loop through cleanDataStore vector, computing distance in miles from the home to this Divvy station.
    // Add each station along with its name, latitude and longitude to a vector.
    // As we process each one, keep track of the one with the smallest distance.
    double smallestDistance = 10000.0;     // Larger than the furthest Divvy distance in miles
    int indexOfClosestStation = -1;   // index of Divvy station with smallest distance
    // Now look at each one
    for (int n = 0; n < cleanDataStore.size(); n++) {
        // Add each item to NearestDivvyRide struct member
        theStation.location = cleanDataStore.at(n).start_station_name;
        theStation.startlat = stold( cleanDataStore.at(n).start_lat);
        theStation.startlng = stold( cleanDataStore.at(n).start_lng);

        // Call distance function and calculate miles and assign to theStation struct
        theStation.miles = distance( homeLat, homeLng, theStation.startlat, theStation.startlng);
        
        // See if it is a new shortest distance, and keep track of it if it is
        if( theStation.miles < smallestDistance) {
            smallestDistance = theStation.miles;
            indexOfClosestStation = n;
        }
    }

    // Display closest station
    DivvyRide closestStation = cleanDataStore.at( indexOfClosestStation);
    cout << "   Closest Divvy station is: " << closestStation.start_station_name
         << " at " << closestStation.start_lat << ", " << closestStation.start_lng << ", "
         << setprecision( 1) << fixed << smallestDistance << " miles away.\n"
         << endl;
} // end getClosestDivvyLocation()


//---------------------------------------------------------------------------------
int main()
{
    // Declarations
    int entrySelection;
    bool menuOption1NotYetChosen = true;
    double avgLength = 0, longestTrip = 0, totalMiles = 0;
    vector<DivvyRide> dataStore;
    vector<DivvyRide> cleanDataStore;
    DivvyRide longestTripInfo;

    // Intro message
    cout << "Analyze Divvy bike ride information using September trip data.\n"
         << "First select option 1 to read and clean the data."
         << endl;

    // Infinite loop to allow handling menu options
    while( true) {
        // Prompt user for menu selection
        cout << endl
             << "Select a menu option: \n"
             << "   1. Select datafile, display rides totals and clean data\n"
             << "   2. Display overall trip information\n"
             << "   3. Display percentage of members vs. casual riders\n"
             << "   4. Display weekday vs weekend usage\n"
             << "   5. Extra Credit: find closest station\n"
             << "   6. Exit\n"
             << "Your choice --> ";
        cin >> entrySelection;

        // If option 6 was chosen then exit the program
        if( entrySelection == 6) {
            break;     // Break out of loop to exit program.
        }
        
        // Defensive programming to enforce that data is read into program (option 1) prior to
        // Selecting entries 2,3,4 or 5
        if( entrySelection != 1 && menuOption1NotYetChosen) {
            cout << "   First read in data by selecting menu option 1"
                 << endl;
            continue;
        }

        // Determine which function to run
        switch( entrySelection) {
           case 1:  // Select preferred datafile
               menuOption1NotYetChosen = false;      // Now it HAS been chosen, which allows other subsequent menu options.
               readCVSFile(dataStore);               // Read data from file
               cleanData(dataStore, cleanDataStore); // Clean and store data from previous step
               break;
           case 2:  // Display general information
               findTripLengthData(cleanDataStore, avgLength, longestTrip, longestTripInfo, totalMiles);
               displayTripLengthData(cleanDataStore, avgLength, longestTrip, longestTripInfo, totalMiles);
               break;
           case 3:  // Display percentage of members vs. casual riders
               casualMemberAnalysis( cleanDataStore);
               break;
           case 4:  // Display weekday vs weekend trends
               weekdayWeekendAnalysis( cleanDataStore);
               break;
           case 5:  // For extra credit find closest Divvy station to some user-entered location
               getClosestDivvyLocation( cleanDataStore);
               break;
           // case 6 to exit the program was handled immediately after user input
           default: cout << "Invalid value.  Exiting Program.";
               exit(-1);
               break;
        } //end switch()
        
    } //end while( true)
    
    cout << endl;
    return 0;
} //end main()
