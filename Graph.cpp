#include <stdexcept>
#include "Graph.h"



bool Graph::addStation(const Station &station) {
    if(findStation(station.getName()) != nullptr){
        return false;
    }
    stations.push_back(new Station(station));
    return true;
}

bool Graph::addRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const {
    auto source = findStation(sourceStation);
    auto destiny = findStation(destinyStation);
    if(source == nullptr || destiny == nullptr){
        return false;
    }
    source->addRailway(destiny, railway.getCapacity(), railway.getService());
    return true;
}

bool Graph::addBidirectionalRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const {
    auto source = findStation(sourceStation);
    auto destiny = findStation(destinyStation);
    if(source == nullptr || destiny == nullptr){
        return false;
    }
    auto railway1 = source->addRailway(destiny, railway.getCapacity() / 2, railway.getService());
    auto railway2 = destiny->addRailway(source, railway.getCapacity() / 2, railway.getService());
    railway1->setReverseRailway(railway2);
    railway2->setReverseRailway(railway1);
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

void Graph::visitStation(std::queue<Station*> &queue, Railway* railway, Station* station, double residualCapacity) {
    if(!station->isVisited() && residualCapacity > 0){
        station->setVisited(true);
        station->setPath(railway);
        queue.push(station);
    }
}

bool Graph::findPath(Station *source, Station *destiny) {
    for(auto station: stations){
        station->setVisited(false);
    }

    source->setVisited(true);
    std::queue<Station*> queue;
    queue.push(source);

    while(!queue.empty() && !destiny->isVisited()){
        auto station = queue.front();
        std::cout<< station->getName() << std::endl;
        queue.pop();
        for(auto railway: station->getOutgoingRailways()){
            visitStation(queue, railway, railway->getDestinyStationPointer(), railway->getCapacity() - railway->getFlow());
        }
        for(auto railway: station->getIncomingRailways()){
            visitStation(queue, railway, railway->getSourceStationPointer(), railway->getFlow());
        }
    }
    return destiny->isVisited();
}

double Graph::minResidualCapacity(Station *source, Station *destiny) {
    double minResidualCapacity = INT_MAX;
    for(auto station = destiny; station != source;){
        auto railway = station->getPath();
        if(railway->getDestinyStationPointer() == station){ //1st iteration
            minResidualCapacity = std::min(minResidualCapacity, railway->getCapacity() - railway->getFlow());
            station = railway->getSourceStationPointer();
        } else {
            minResidualCapacity = std::min(minResidualCapacity, railway->getFlow());
            station = railway->getDestinyStationPointer();
        }
    }
    return minResidualCapacity;
}

void Graph::augmentFlow(Station *source, Station *destiny, double residualCapacity) {
    for(auto station = destiny; station != source;){
        auto railway = station->getPath();
        double flow = railway->getFlow();
        if(railway->getDestinyStationPointer() == station){
            railway->setFlow(flow + residualCapacity);
            station = railway->getSourceStationPointer();
        } else {
            railway->setFlow(flow - residualCapacity);
            station = railway->getDestinyStationPointer();
        }
    }
}

void Graph::edmondsKarp(Station* sourceStation, Station* destinyStation) {
    for(auto station: stations){
        for(auto railway: station->getOutgoingRailways()){
            railway->setFlow(0);
        }
    }
    int i = 1;
    while(findPath(sourceStation, destinyStation)){
        double residualCapacity = minResidualCapacity(sourceStation, destinyStation);
        augmentFlow(sourceStation, destinyStation, residualCapacity);
    }
}

double Graph::getTrainsBetweenStations(const std::string &source, const std::string &destiny) {
    auto sourceStation = findStation(source);
    auto destinyStation = findStation(destiny);
    if(sourceStation == nullptr){
        return -1;
    }

    if(destinyStation == nullptr){
        return -2;
    }

    if(sourceStation == destinyStation){
        return -3;
    }

    edmondsKarp(sourceStation, destinyStation);
    edmondsKarp(destinyStation, sourceStation);
    double trains = 0;

    for(auto station: stations){
        for(auto railway: station->getOutgoingRailways()){
            trains += railway->getFlow();
        }
    }
    return trains;
}


