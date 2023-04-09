#include <iostream>
#include <vector>
#include "CsvReader.h"
#include "Graph.h"
#include "menus/Menu.h"

int errorCheck(Graph* graph, Graph* directedGraph, std::vector<Station> stations, std::vector<Railway> railways){
    if(stations.empty()){
        std::cout << "Error reading stations file" << std::endl;
        return 1;
    }

    if(railways.empty()){
        std::cout << "Error reading network file" << std::endl;
        return 1;
    }

    for(const Station& station:stations){
        if(!graph->addStation(station)){
            std::cout << "Error adding station " << station.getName() << std::endl;
        }
        directedGraph->addStation(station);
    }

    for(const Railway& railway:railways){
        if(!graph->addBidirectionalRailway(railway.getSourceStationString(), railway.getDestinyStationString(), railway)){
            std::cout << "Error adding railway " << railway.getSourceStationString() << " -> " << railway.getDestinyStationString() << std::endl;
        }
        if(!directedGraph->addRailway(railway.getSourceStationString(), railway.getDestinyStationString(), railway)){
            std::cout << "Error adding railway " << railway.getSourceStationString() << " -> " << railway.getDestinyStationString() << std::endl;
        }
    }

    return 0;
}


int main() {
    //Setting up the graph
    Graph graph;
    Graph directedGraph;

    std::vector<Station> stations = CsvReader::readStations("../dataset/stations.csv");
    std::vector<Railway> railways= CsvReader::readNetwork("../dataset/network.csv");

    if (errorCheck(&graph, &directedGraph, stations, railways)) return 1;
    //----------------------------------------------------

    for(auto station: graph.getStations()){
        if(station->getName()=="Cruz Quebrada" || station->getName() == "Caxias"){
            std::cout << "|--------------------\n";
            std::cout << "Station name: " << station->getName() << std::endl;
            std::cout << "Station township: " << station->getTownship() << std::endl;
            for(auto railway: station->getOutgoingRailways()){
                std::cout << "  Destination: " << railway->getDestinyStationPointer()->getName() << ", Capacity: " << railway->getCapacity() << ", Service: " << railway->getService() << std::endl;
            }
            for(auto railway: station->getIncomingRailways()){
                std::cout << "  Incoming from: " << railway->getSourceStationPointer()->getName() << ", Capacity: " << railway->getCapacity() << ", Service: " << railway->getService() << std::endl;
            }
        }
    }
    /*
    std::cout << "Stations without outgoing railways:" << std::endl;
    for(auto station: graph.getStations()) {
        if (station->getOutgoingRailways().empty()) {
            std::cout << station->getName() << std::endl;
        }
    }

    std::cout << "Stations without incoming railways:" << std::endl;
    for(auto station: graph.getStations()) {
        if (station->getIncomingRailways().size() == 0) {
            std::cout << station->getName() << std::endl;
        }
    }
     */
    Menu menu = Menu(graph, directedGraph);
    menu.start();
    return 0;
}