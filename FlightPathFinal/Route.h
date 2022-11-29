//
// Created by Senam on 28/11/2022.
//

/**
 * @author Senam Afi Glover-Tay
 * This is a class of route objects
 */

#ifndef FLIGHTPATHFINAL_ROUTE_H
#define FLIGHTPATHFINAL_ROUTE_H
#include <iostream>
#include <string>
using namespace std;


class Route {
private:

    //Declare member variables
    string startAirport;
    string endAirport;
    string airlineID;

public:
    Route();
    Route(string a_start_airport, string an_end_airport, string an_id);

    string getstartAirport();
    string getendAirport();
    string getairlineId();

    void setstartAirport(string an_airport);
    void setendAirport(string other_airport);

    void toString();

    unordered_map<string, vector<Route>> routeMap;
    unordered_map<string, vector<Route>> readRoutes();
};

#endif //FLIGHTPATHFINAL_ROUTE_H
