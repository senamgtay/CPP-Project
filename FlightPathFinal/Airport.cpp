/**
 * @author Senam Afi Glover-Tay
 * This is the implementation of the Airport class
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Airport.h"
using namespace std;

/**
 * default constructor
 */
Airport::Airport() {
    this->city = "none";
    this->country = "none";
    this->IATAcode = "none";
}

/**
 * parametrized constructor
 * @param airportId
 * @param a_city
 * @param a_country
 * @param a_code
 */
Airport::Airport(string airportId, string a_city, string a_country, string a_code) {
    this->airportId =airportId;
    this->city = a_city;
    this->country = a_country;
    this->IATAcode = a_code;
}

/**
 * @return city
 */
string Airport::getCity() {
    return city;
}

/**
 * @return country
 */
string Airport::getCountry() {
    return country;
}

/**
 * @return IATAcode
 */
string Airport::getIATAcode() {
    return IATAcode;
}

/**
 *
 * this function prints out the content of an airport object
 */
void Airport::toString() {
    cout <<"id: "<< airportId << endl;
    cout <<"City: "<< getCity() << endl;
    cout << "Country: " << getCountry() << endl;
    cout << "Airport Code: " << getIATAcode() <<endl;
    cout << ' ' <<endl;
}

/**
 * This function reads from the a csv file and
 * creates a hash map of locations and their airports
 *
 * * precondition : input stream must be able to open file
 * else error message is printed
 *
 * postcondition : successfully returns a hashmap
 *
 * @return airportMap
 */
unordered_map<string, vector<Airport>> Airport::readAirports(){
    ifstream thisFile;
    thisFile.open("airports.csv");
    string airportData;

    if (thisFile.fail()){
        perror("Could not open file");
    }else {
        while (getline(thisFile, airportData)) {
            string first_column;
            string second_column;
            string thisAirportCity;
            string thisAirportCountry;
            string thisAirportCode;

            stringstream for_each_airport(airportData);
            getline(for_each_airport, first_column, ',');
            getline(for_each_airport, second_column, ',');
            getline(for_each_airport, thisAirportCity, ',');
            getline(for_each_airport, thisAirportCountry, ',');
            getline(for_each_airport, thisAirportCode, ',');

            if (thisAirportCode != "\\N") {
                Airport airportObject(first_column, thisAirportCity,
                                      thisAirportCountry, thisAirportCode);

                string keyChecker = airportObject.getCity() + ',' + " " + airportObject.getCountry();
                itr = airportMap.find(keyChecker);
                if (itr != airportMap.end()) {
                    itr->second.push_back(airportObject);
                } else {
                    vector<Airport> airportsInCity;
                    airportsInCity.push_back(airportObject);
                    airportMap.insert({keyChecker, airportsInCity});
                }
            }
        }
    }
    thisFile.close();
    return airportMap;
}

