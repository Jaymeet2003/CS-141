Divvy Bike Data Analysis program.
    Author: Jimmy Patel
    Date: 10/31/2021
    Class: CS 141, Fall 2021, UIC
    System: Visual Studio Code 2021 IDE Windows
    Menu Option 5 Extra Credit URL: https://www.google.com/maps/d/u/0/edit?mid=1kEBEpX9wK7_L-cxFBnXy6ZYR_u0mVIs6&usp=sharing
    Coordinates for Home I would like to live in:  41.8645  -87.6292


#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include <limits.h>
#include <map>
using namespace std;

class Ride {
    public:
        string id;
        string type;
        string started_at;
        string ended_at;
        string start_station_name;
        string end_station_name;
        pair<long double, long double> startlatlng;
        pair<long double, long double> endlatlng;
        string member_casual;
};

long double toRadians(const long double degree) {
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1, long double lat2, long double long2) {
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
        cos(lat1) * cos(lat2) *
        pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
}

vector<string> parseCsvString(string x) {
    string temp = "";
    vector<string> ans;
    for(int i=0; i<(int)x.size(); i++){
        if(x[i] != ',') temp += x[i];
        else {
            ans.push_back(temp);
            temp = "";
        }
    }
    ans.push_back(temp);
    return ans;
}

Ride getNewRide(string x) {
    Ride ride;
    vector<string> data = parseCsvString(x);
    if (data.size() != 11) return ride;
    for (int i =0 ; i < (int)data.size(); i++) {
        if (data[i] == "") return ride;
    }
    ride.id = data[0];
    ride.type = data[1];
    ride.started_at = data[2];
    ride.ended_at = data[3];
    ride.start_station_name = data[4];
    ride.end_station_name = data[5];
    ride.startlatlng = {stod(data[6]), stod(data[7])};
    ride.endlatlng = {stod(data[8]), stod(data[9])};
    ride.member_casual = data[10];
    return ride;
}

void displayMenu() {
    cout << endl <<  "Select a menu option: " << endl;
    cout << "   1. Select datafile, display rides totals and clean data" << endl;
    cout << "   2. Display overall trip information" << endl;
    cout << "   3. Display percentage of members vs. casual riders" << endl;
    cout << "   4. Display weekday vs weekend usage" << endl;
    cout << "   5. Extra Credit: find closest station" << endl;
    cout << "   6. Exit" << endl;
}

void displayOverAllTripInformation(vector<Ride> cleanRides) {

    long double totalmiles = 0, longmiles = 0;
    int longmilesIndex;

    for (int i = 0 ; i < (int)cleanRides.size(); i++) {
        long double miles = distance(cleanRides[i].startlatlng.first, 
            cleanRides[i].startlatlng.second,
            cleanRides[i].endlatlng.first,
            cleanRides[i].endlatlng.second);
        totalmiles += miles;
        if (longmiles < miles) {
            longmiles = miles;
            longmilesIndex = i;
        }
    }

    cout << "   Total # of miles traveled: " << round(totalmiles) << endl;
    cout << "   Average length of trips in miles:  ";
    printf("%.1Lf\n", (totalmiles / (cleanRides.size())));
    cout << "   Longest trip information below: " << endl;
    cout << "   -------------------------------" << endl;
    cout << "   Trip ID: " << cleanRides[longmilesIndex].id << endl;
    cout << "   Trip start location: " << cleanRides[longmilesIndex].start_station_name << endl;
    cout << "   Trip end location: " << cleanRides[longmilesIndex].end_station_name << endl;
    cout << "   Trip distance in miles: ";
    printf("%.1Lf\n\n", longmiles);
}

void casualMemberRiderPercentage(vector<Ride> cleanRides) {

    int casual = 0, member = 0;

    for (int i = 0 ; i < (int)cleanRides.size(); i++) {
        if ((cleanRides[i].member_casual).find("casual") != std::string::npos) casual++;
        else member++;
    }

    double casualPerc = ((casual*1.0)/cleanRides.size()) * 100.0;
    double memberPerc = ((member*1.0)/cleanRides.size()) * 100.0;
    cout << "   Casual Rider Percentage: ";
    printf("%.1f", casualPerc);
    cout << "%" << endl;
    cout << "   Member Rider Percentage: ";
    printf("%.1f", memberPerc);
    cout << "%" << endl;
    cout << endl;
}

void closestStation(vector<Ride> cleanRides, long double lat, long double lng) {

    long double closestmiles = INT_MAX;
    pair<long double, long double> closestlatlng;
    string closestStation;

    for (int i = 0 ; i < (int) cleanRides.size(); i++) {
        long double dist = distance(lat, lng, cleanRides[i].startlatlng.first, cleanRides[i].startlatlng.second);
        
        cout << lat << " " << lng << " " << cleanRides[i].startlatlng.first << " " << cleanRides[i].startlatlng.second << " " << dist << endl;
        if (dist < closestmiles) {
            closestmiles = dist;
            closestlatlng = {cleanRides[i].startlatlng.first, cleanRides[i].startlatlng.second};
            closestStation = cleanRides[i].start_station_name;
        }
        dist = distance(lat, lng, cleanRides[i].endlatlng.first, cleanRides[i].endlatlng.second);
        
        cout << lat << " " << lng << " " << cleanRides[i].endlatlng.first << " " << cleanRides[i].endlatlng.second << " " << dist << endl;
        if (dist < closestmiles) {
            closestmiles = dist;
            closestlatlng = {cleanRides[i].endlatlng.first, cleanRides[i].endlatlng.second};
            closestStation = cleanRides[i].end_station_name;
        }
    }

    cout << "   Closest Divvy station is: " << closestStation << " at ";
    cout << closestlatlng.first << ", " << closestlatlng.second << ", ";
    cout << closestmiles << "miles away." << endl << endl;
}

void displayNumberOfCharacters(char c, int count) {
    for (int i = 0; i < count; i++) {
        cout << c;
    }
    cout << endl;
}

void calculationPerHour(vector<Ride> cleanRides, int choice) {

    map<int, int> weekday, weekend;
    int largestHour = 0;

    for (int i = 0; i < (int)cleanRides.size(); i++) {
        string started_at = cleanRides[i].started_at;
        if (started_at.find("9/1/2021") != std::string::npos) {
            int hour = started_at[10] == ':' ?  int(started_at[9] - '0')  : int(started_at[9] - '0') * 10 + int(started_at[10] - '0');
            weekday[hour]++;
            largestHour = max (largestHour, weekday[hour]);
        }
        else if (started_at.find("9/4/2021") != std::string::npos) {
            int hour = started_at[10] == ':' ? int(started_at[9] - '0')  : int(started_at[9] - '0') * 10 + int(started_at[10] - '0');
            weekend[hour]++;
            largestHour = max (largestHour, weekend[hour]);
        }
    }
    
    if (choice == 1) {
        cout << "   LargestNumberOfRides is: " << largestHour << endl ;
        cout << "   Rides per hour for weekday and weekend:" << endl;
        for (int i = 0 ; i <= 23; i++) {
            if ( i < 10) {
                cout << "    " << i << ":      " << weekday[i] << "      " << weekend[i] << endl;
            }
            else {
                cout << "   " << i << ":      " << weekday[i] << "      " << weekend[i] << endl;
            }
            
        }
    }
    
    else if (choice == 2) {
        for (int i = 0 ; i <= 23; i++) {
            if ( i < 10) {
                cout << "    " << i << ": ";
                displayNumberOfCharacters('@', (weekday[i] * 1.0/largestHour) * 50);
                cout << "      ";
                displayNumberOfCharacters('+', (weekend[i] * 1.0/largestHour) * 50);
            }
            else {
                cout << "   " << i << ": ";
                displayNumberOfCharacters('@', (weekday[i] * 1.0/largestHour) * 50);
                cout << "       ";
                displayNumberOfCharacters('+', (weekend[i] * 1.0/largestHour) * 50);
            }
        }
    }

}

int main() {
    
    int choice, innerChoice;
    bool firstTime = true;
    
    cout << "Analyze Divvy bike ride information using September trip data." << endl;
    cout << "First select option 1 to read and clean the data." << endl;

    vector<Ride> cleanRides;
    
    while(true) {
        displayMenu();
        cout << "Your choice --> ";
        cin >> choice;
        
        if (firstTime == true && choice != 1) {
            cout << "   First read in data by selecting menu option 1" << endl;
            continue;
        }
        
        if (choice == 1) {
            firstTime = false;
            cout << "   Select datafile: " << endl;
            cout << "      1. Small subset of data with 14 rides to help create your program" << endl;
            cout << "      2. Week day vs weekend rides" << endl;
            cout << "      3. All September 2021 data (not tested in Zybooks)" << endl;
            cout << "   Your selection--> ";
            cin >> innerChoice;
            string filename;
            
            if (innerChoice == 1) filename = "divvyridesampledata.csv";
            else if (innerChoice == 2) filename = "weekdayweekend.csv";
            else filename = "all_divvy_rides_september.csv";

            string text;
            ifstream datafile(filename);
            getline (datafile, text);   

            int count = 0;
            while (getline (datafile, text)) {
                count++;
                Ride newRide  = getNewRide(text);
                if (newRide.id != "")  {
                    cleanRides.push_back(newRide);
                }
            }
            datafile.close();
            cout << "   Total # of trips found in datafile:  " << count << endl;
            cout << "   Total # of trips in clean data:  " << cleanRides.size() << endl;
        }

        if (choice == 2) {
            displayOverAllTripInformation(cleanRides);
        }

        if (choice == 3) {
            casualMemberRiderPercentage(cleanRides);
        }

        if (choice == 4) {
            cout << "   Select type of display:";
            cout << "      1. Counts of rides per hour in the day" << endl;
            cout << "      2. Proportional 50 column graph with @ for weekday and + for weekend" << endl;
            cout << "   Your selection--> ";
            cin >> innerChoice;
            calculationPerHour(cleanRides, innerChoice);

        }

        if (choice == 5) {
            cout << "   Input latitude and longitude of the home: ";
            long double lat, lng;
            cin >> lat >> lng;
            cout << "   You entered: " << floor(lat * 10)/10.0 << " for latitude and " << floor(lng * 10)/10.0 << " for longitude" << endl;
            closestStation(cleanRides, lat, lng);
        }

        if (choice == 6) {
            return 0;
        }

    }
    
}
