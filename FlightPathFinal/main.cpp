/**
 * @author Senam Afi Glover-Tay
 * This is the driver code
 */

 #include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <deque>
#include <set>
#include <bits/stdc++.h>
#include "Route.h"
#include "Airport.h"
using namespace std;

/*
 * Function Prototypes
 */
vector<string> breadthFirst (Airport initialAirport, Airport targetAirport, unordered_map<string, vector<Route>> a_routeMap);
vector<string> solutionPath (string targetAirportCode);
vector<string> getAirlinePath (vector<string> theSolutionPath, unordered_map<string, vector<string>> AirlineMap);
unordered_map <string, vector<string>> airlineCreator();
void writer(vector<string> path, vector<string> an_airlinePath, string startCity, string targetCity);

/*
 * Unordered maps utilized in main function
 */
unordered_map <string, string> parentChild;
unordered_map <string, string> :: iterator  iter;
unordered_map <string, vector<Airport>> mainClassAirportMap;
unordered_map <string, vector<Route>> mainClassRouteMap;
unordered_map <string, vector<string>> mainClassAirlineMap;
unordered_map<string, vector<string>>:: iterator  Route_itr;

/*
 * Vectors utilized in main function
 */
vector<string> mainClassSolution;
vector<Airport> possible_start_airports;
vector<Airport> possible_end_airports;
vector<Route> destinations;
vector<string> myFalse = {"nothing", "found"};
vector<string> airlinePath;



int main() {

    string filename;
    string startLocation;
    string endLocation;
    vector<string> citycountries;

    cout << "Enter the name of the file you wish to read" << endl;
    cin >> filename;
    ifstream Filestream;
    Filestream.open(filename);
    string inputInfo;


    //pre : input stream must be able to open file
    // else error message is printed
    if (Filestream.fail()){
        perror("Could not open file");
    }else {
        while (getline(Filestream, inputInfo)) {
            string aCity;
            string aCountry;

            stringstream for_each_line(inputInfo);
            getline(for_each_line, aCity, ',');
            citycountries.push_back(aCity);
            getline(for_each_line, aCountry, ',');
            citycountries.push_back(aCountry);
        }
    }
    //post: if successful, content of file is read to variables

    startLocation = citycountries[0] + ',' + citycountries[1];
    endLocation = citycountries[2] + ',' + citycountries[3];

    Filestream.close();

   //new Airport object to read airports.csv
   Airport newAirport = Airport();
   mainClassAirportMap = newAirport.readAirports();

   //list of possible airports in source and destination locations
   possible_start_airports = mainClassAirportMap.at(startLocation);
   possible_end_airports = mainClassAirportMap.at(endLocation);

   //new Route object to read from routes.csv
   Route newRoute = Route();
   mainClassRouteMap = newRoute.readRoutes();

   //call on breadth first search for valid source and destination airports
   int i = 0;
   int j = 0;
    mainClassSolution = breadthFirst(possible_start_airports[i],
                 possible_end_airports[j],
                 mainClassRouteMap);
    if (mainClassSolution == myFalse && possible_start_airports.size() > 1){
        i += 1;
        mainClassSolution = breadthFirst(possible_start_airports[i],
                                           possible_end_airports[j],
                                           mainClassRouteMap);
    } else if (mainClassSolution == myFalse && possible_end_airports.size() > 1){
        i = 0;
        j += 1;
        mainClassSolution = breadthFirst(possible_start_airports[i],
                                         possible_end_airports[j],
                                         mainClassRouteMap);}

    // map of routes as keys and possible airlines as values
    mainClassAirlineMap = airlineCreator();

    //vector of the airline path gained from airline map based on solution path
   airlinePath = getAirlinePath(mainClassSolution, mainClassAirlineMap);

   //writes to output file
    writer(mainClassSolution, airlinePath, citycountries[0], citycountries[2]);

    return 0;
}

/**
 * This function implements a breadth first search
 *  optimal path from source to destination
 * @param initialAirport
 * @param targetAirport
 * @param a_routeMap
 * @return solutionPath(targetAirport)
 */

vector<string> breadthFirst (Airport initialAirport, Airport targetAirport,
                             unordered_map<string, vector<Route>> a_routeMap) {

    parentChild.insert(pair<string, string>(initialAirport.getIATAcode(), "none"));

    string initialAirportCode = initialAirport.getIATAcode();

    if (targetAirport.getIATAcode() == initialAirport.getIATAcode()){
        return solutionPath(targetAirport.getIATAcode());
    }
    deque<string> frontier;
    frontier.push_back(initialAirportCode);
    deque<string>::iterator frontierIterator;

    set<string> explored;

while (!frontier.empty()){
    string an_airport = frontier.front();
    frontier.pop_front();

    if (an_airport == targetAirport.getIATAcode()){
        return solutionPath(targetAirport.getIATAcode());
    }

    if(a_routeMap.find(an_airport)!= a_routeMap.end()){
        for ( auto x : a_routeMap.at(an_airport) ){
            frontierIterator = find(frontier.begin(), frontier.end(), x.getendAirport());
            if((explored.find(x.getendAirport()) == explored.end()) && frontierIterator == frontier.end()){
               iter = parentChild.begin();
               for( ; iter != parentChild.end(); iter++){
                        if (iter->first == initialAirport.getIATAcode()){
                            iter->second = "none";
                        }
                       if (iter->first != x.getendAirport() ){
                           parentChild.insert({x.getendAirport(), an_airport});
                       }
                       else {
                           parentChild[x.getendAirport()] = an_airport;
                       }
               }
                frontier.push_back(x.getendAirport());
                explored.insert(x.getendAirport());
            }
            }
        }
    }
   return myFalse;
}

/**
 * This function back traces the a map to
 * get the solution path
 * @param targetAirportCode
 * @return solution
 */
vector<string> solutionPath (string targetAirportCode){
    vector<string> solution_path;
    solution_path.push_back(targetAirportCode);
    string thisNode = targetAirportCode;


    while(parentChild.find(thisNode) != parentChild.end()){
        thisNode = parentChild.find(thisNode)->second;

        if(thisNode == "none"){
            break;
        }

        solution_path.push_back(thisNode);

    }
    reverse(solution_path.begin(), solution_path.end());
    return solution_path;
}

/**
 * This function returns a map for airline retrieval
 * @return RoutesAirlines
 */
unordered_map <string, vector<string>> airlineCreator() {
    unordered_map<string, vector<string>> RoutesAirlines;
    ifstream mystream;
    mystream.open("routes.csv");
    string airline_info;

    while (getline(mystream, airline_info)) {
        string airline_id;
        string second_column;
        string startAirport;
        string column_four;
        string dest_airport;

        stringstream for_each_route(airline_info);
        getline(for_each_route, airline_id, ',');
        getline(for_each_route, second_column, ',');
        getline(for_each_route, startAirport, ',');
        getline(for_each_route, column_four, ',');
        getline(for_each_route, dest_airport, ',');

        string keyChecker = startAirport + ',' + dest_airport;

        if (startAirport != "\\N" && dest_airport != "\\N") {
            //Route_itr = RoutesAirlines.find(keyChecker);
            //if (Route_itr != RoutesAirlines.end()) {
                //Route_itr->second.push_back(airline_id);
                if (RoutesAirlines.find(keyChecker) != RoutesAirlines.end()){
                    RoutesAirlines.at(keyChecker).push_back(airline_id);
            } else {
                vector<string> airlines_on_route;
                airlines_on_route.push_back(airline_id);
                RoutesAirlines.insert({keyChecker, airlines_on_route});
            }
        }
    }
    mystream.close();
    return RoutesAirlines;
}

/**
 * This function returns a list of
 * airlines
 * @param theSolutionPath
 * @param AirlineMap
 * @return functionPath
 */
vector<string> getAirlinePath (vector<string> theSolutionPath, unordered_map<string, vector<string>> AirlineMap){
    vector<string> functionPath;
    string thisRoute;

    for (int i = 0; i < theSolutionPath.size()-1; i++){
        thisRoute = theSolutionPath[i] + ',' + theSolutionPath[i+1];
        if (AirlineMap.find(thisRoute) != AirlineMap.end()){
            string airline = AirlineMap.at(thisRoute)[0];
            functionPath.push_back(airline);
        }
    }

    return functionPath;
}

/**
 * This function writes the results of
 * the search into an output file
 * @param path
 * @param an_airlinePath
 * @param startCity
 * @param targetCity
 */
void writer(vector<string> path, vector<string> an_airlinePath, string startCity, string targetCity){
    string outputFileName = startCity + "-" + targetCity + "_output.txt";
    ofstream outputFile(outputFileName);

    int count = 0;
    int i = 0;
    int j = i + 1;

    while(j < path.size()){
        string source = path[i];
        string target = path[j];

        outputFile << j << '.' << an_airlinePath[i] << " from "  << source << " to " << target << " 0 stops." << endl;
        count +=1;
        i+=1;
        j+=1;
    }

    outputFile << "Total flights = " << i << endl;
    outputFile << "Total additional stops = 0" << endl;
    outputFile << "Optimality criteria: number of flights" << endl;

    outputFile.close();
}

