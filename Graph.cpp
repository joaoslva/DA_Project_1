#include <stdexcept>
#include "Graph.h"

Graph::Graph() {}

bool Graph::addStation(const Station &station) {
    if(findStation(station.getName()) != nullptr){
        return false;
    }
    stations.push_back(new Station(station));
    return true;
}

bool Graph::addRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) {
    auto source = findStation(sourceStation);
    auto destiny = findStation(destinyStation);
    if(source == nullptr || destiny == nullptr){
        return false;
    }
    source->addRailway(destiny, railway.getCapacity(), railway.getService());
    return true;
}

bool Graph::addBidirectionalRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) {
    auto source = findStation(sourceStation);
    auto destiny = findStation(destinyStation);
    if(source == nullptr || destiny == nullptr){
        return false;
    }
    auto railway1 = source->addRailway(destiny, railway.getCapacity(), railway.getService());
    auto railway2 = destiny->addRailway(source, railway.getCapacity(), railway.getService());
    railway1->setPreviousRailway(railway2);
    railway2->setPreviousRailway(railway1);
    return true;
}

Station* Graph::findStation(const std::string &name) const {
    for(auto &station : stations){
        if(station->getName() == name){
            return station;
        }
    }
    return nullptr;
}

std::vector<Station*> Graph::getStations() const {
    return stations;
}
