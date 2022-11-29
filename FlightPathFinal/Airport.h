/**
 * @author Senam Afi Glover-Tay
 * This is the of the Airport class
 */

#ifndef FLIGHTPATHFINAL_AIRPORT_H
#define FLIGHTPATHFINAL_AIRPORT_H
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Airport {
private:
    string city;
    string country;
    string IATAcode;

public:
    string airportId;
    Airport();
    Airport(string airportId, string a_city, string a_country, string a_code);
    unordered_map<string, vector<Airport>> airportMap;
    unordered_map<string, vector<Airport>>:: iterator  itr;
    string getCity();
    string getCountry();
    string getIATAcode();
    void toString();
    unordered_map<string, vector<Airport>> readAirports();

};

#endif //FLIGHTPATHFINAL_AIRPORT_H
