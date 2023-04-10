#include <iostream>
#include <vector>
#include "CsvReader.h"
#include "Graph.h"
#include "menus/Menu.h"

int errorCheck(Graph* graph, std::vector<Station> stations, std::vector<Railway> railways){
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
    }

    for(const Railway& railway:railways){
        if(!graph->addBidirectionalRailway(railway.getSourceStationString(), railway.getDestinyStationString(), railway)){
            std::cout << "Error adding railway " << railway.getSourceStationString() << " -> " << railway.getDestinyStationString() << std::endl;
        }
    }

    return 0;
}


int main() {
    //Setting up the graph
    Graph graph;

    std::vector<Station> stations = CsvReader::readStations("../dataset/stations.csv");
    std::vector<Railway> railways= CsvReader::readNetwork("../dataset/network.csv");

    if (errorCheck(&graph, stations, railways)) return 1;
    //----------------------------------------------------
    Menu menu = Menu(graph);
    menu.start();
    return 0;
}