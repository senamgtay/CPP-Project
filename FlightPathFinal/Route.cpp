/**
 * @author Senam Afi Glover-Tay
 * This is the implementation of the Route class
 */
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Route.h"

static unordered_map<string, vector<Route>> routeMap;

/**
 * default constructor
 */
Route::Route() {
    this->startAirport = "none";
    this->endAirport = "none";
    this->airlineID = "none";

}

/**
 * parametrized constructor
 * @param a_start_airport
 * @param an_end_airport
 * @param an_id
 */
Route::Route(string a_start_airport, string an_end_airport, string an_id) {
    this->startAirport = a_start_airport;
    this->endAirport = an_end_airport;
    this->airlineID = an_id;
}

/**
 * @return startAirport
 */
string Route::getstartAirport() {
    return startAirport;
}

/**
 * @return endAirport
 */
string Route::getendAirport() {
    return endAirport;
}

/**
 * @return airlineID
 */
string Route::getairlineId(){
    return airlineID;
}

/**
 * @param an_airport
 */
void Route::setstartAirport(string an_airport) {
    this->startAirport = an_airport;
}

/**
 * @param other_airport
 */
void Route::setendAirport(string other_airport) {
    this->endAirport = other_airport;
}

/**
 * This function prints out the content of a route object
 */
void Route::toString() {
    cout <<"Start Airport: "<< getstartAirport() << endl;
    cout << "End Airport: " << getendAirport() << endl;
    cout << "Airline id: " << getairlineId() << endl;
    cout << ' ' <<endl;
}

/**
 *This function reads from a csv file and
 * creates a hash map locations and destination
 *
 * precondition : input stream must be able to open file
 * else error message is printed
 *
 * postcondition : successfully returns a hashmap
 * @return routeMap
 */
unordered_map<string, vector<Route>> Route::readRoutes(){

    ifstream thisFile;
    thisFile.open("routes.csv");
    string routeData;


    if (thisFile.fail()){
        perror("Could not open file");
    }else {
        while (getline(thisFile, routeData)) {
            string first_column;
            string second_column;
            string this_start_airport;
            string fourth_column;
            string this_end_airport;

            stringstream for_each_route(routeData);
            getline(for_each_route, first_column, ',');
            getline(for_each_route, second_column, ',');

            getline(for_each_route, this_start_airport, ',');
            getline(for_each_route, fourth_column, ',');
            getline(for_each_route, this_end_airport, ',');

            if (this_start_airport != "\\N" & this_end_airport != "\\N") {
                Route routeObject = Route(this_start_airport,
                                          this_end_airport,
                                          first_column);

                string key_start_city = routeObject.getstartAirport();

                if (routeMap.find(key_start_city) != routeMap.end()) {
                    routeMap.at(key_start_city).push_back(routeObject);
                } else {
                    vector<Route> destinationRoutes;
                    destinationRoutes.push_back(routeObject);
                    routeMap.insert(pair<string, vector<Route>>(key_start_city, destinationRoutes));
                }
            }
        }
    }
    thisFile.close();
    return routeMap;

}
