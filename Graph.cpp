#include "Graph.h"



bool Graph::addStation(const Station& station) {
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
    auto railway1 = source->addRailway(destiny, railway.getCapacity(), railway.getService());
    auto railway2 = destiny->addRailway(source, railway.getCapacity(), railway.getService());
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

bool Graph::removeStation(const std::string& name) {
    // Find the station to remove
    Station* stationToRemove = findStation(name);
    if (!stationToRemove) {
        return false; // Station not found, cannot remove
    }

    // Remove all incoming and outgoing railways connected to the station
    std::vector<Railway*> outgoingRailways = stationToRemove->getOutgoingRailways();
    for (Railway* railway : outgoingRailways) {
        stationToRemove->removeRailway(railway);
    }
    std::vector<Railway*> incomingRailways = stationToRemove->getIncomingRailways();
    for (Railway* railway : incomingRailways) {
        Station* sourceStation = railway->getSourceStationPointer();
        sourceStation->deleteRailway(railway);
    }

    // Remove the station from the graph
    auto it = std::find(stations.begin(), stations.end(), stationToRemove);
    if (it != stations.end()) {
        stations.erase(it);
        delete stationToRemove; // Free the memory used by the station
        return true;
    } else {
        return false; // Station not found, cannot remove
    }
}

void Graph::visitStation(std::queue<Station*>& queue, Railway* railway, Station* station, double residualCapacity) {
    if (!station->isVisited() && residualCapacity > 0) {
        station->setVisited(true);
        station->setPath(railway);
        queue.push(station);
    }
}

bool Graph::findPath(Station* source, Station* destiny) {
    for (auto station : stations) {
        station->setVisited(false);
    }

    source->setVisited(true);
    std::queue<Station*> queue;
    queue.push(source);

    while (!queue.empty() && !destiny->isVisited()) {
        auto station = queue.front();
        queue.pop();
        for (auto railway : station->getOutgoingRailways()) {
            visitStation(queue, railway, railway->getDestinyStationPointer(), railway->getCapacity() - railway->getFlow());
        }
        for (auto railway : station->getIncomingRailways()) {
            visitStation(queue, railway, railway->getSourceStationPointer(), railway->getFlow());
        }
    }
    return destiny->isVisited();
}

double Graph::minResidualCapacity(Station* source, Station* destiny) {
    double minResidualCapacity = INT_MAX;
    for (auto station = destiny; station != source;) {
        auto railway = station->getPath();
        if (railway->getDestinyStationPointer() == station) {
            minResidualCapacity = std::min(minResidualCapacity, railway->getCapacity() - railway->getFlow());
            station = railway->getSourceStationPointer();
        }
        else {
            minResidualCapacity = std::min(minResidualCapacity, railway->getFlow());
            station = railway->getDestinyStationPointer();
        }
    }
    return minResidualCapacity;
}

void Graph::augmentFlow(Station* source, Station* destiny, double residualCapacity) {
    for (auto station = destiny; station != source;) {
        auto railway = station->getPath();
        double flow = railway->getFlow();
        if (railway->getDestinyStationPointer() == station) {
            railway->setFlow(flow + residualCapacity);
            station = railway->getSourceStationPointer();
        }
        else {
            railway->setFlow(flow - residualCapacity);
            station = railway->getDestinyStationPointer();
        }
    }
}

double Graph::edmondsKarp(Station* sourceStation, Station* destinyStation) {
    for (auto station : stations) {
        for (auto railway : station->getOutgoingRailways()) {
            railway->setFlow(0);
        }
    }

    double maxFlow = 0;
    int i = 0;

    while (findPath(sourceStation, destinyStation)) {
        std::cout << "Path " << i++ << std::endl;
        auto residualCapacity = minResidualCapacity(sourceStation, destinyStation);
        maxFlow += residualCapacity;
        augmentFlow(sourceStation, destinyStation, residualCapacity);
    }

    return maxFlow;
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

    return edmondsKarp(sourceStation, destinyStation);
}

std::vector<std::pair<std::pair<std::string, std::string>, double>> Graph::pairsWithMostTrains() {
    std::vector<std::pair<std::pair<std::string, std::string>, double>> pairs;
    std::vector<std::pair<std::pair<std::string, std::string>, double>> returnPairs;
    for(auto station : stations){
        for(auto station2 : stations){
            if(station != station2){
                pairs.emplace_back(std::make_pair(station->getName(), station2->getName()), getTrainsBetweenStations(station->getName(), station2->getName()));
            }
        }
    }

    std::sort(pairs.begin(), pairs.end(), [](const std::pair<std::pair<std::string, std::string>, double>& a, const std::pair<std::pair<std::string, std::string>, double>& b){
        return a.second > b.second;
    });

    returnPairs.push_back(pairs[0]);
    for(int i = 1; i < pairs.size(); i++){
        if(pairs[i].second == pairs[0].second){
            returnPairs.push_back(pairs[i]);
        }
        else{
            break;
        }
    }

    return returnPairs;
}

std::vector<std::pair<std::pair<std::string, std::string>, double>> Graph::largerBudgets() {

    // Create the super source and super sink stations
    Station superSource = Station(-1, "SuperSource", "", "", "", "");
    Station superSink = Station(-2, "SuperSink", "", "", "", "");

    // Add the super source and super sink stations to the graph
    if (!addStation(superSource) || !addStation(superSink)) {
        std::cout << "Error adding super source or super sink" << std::endl;
        return {};
    }

    Railway stub = Railway("", "", std::numeric_limits<double>::infinity(), "");
    for(auto station : stations){
        if(station->getIncomingRailways().empty() && !station->getOutgoingRailways().empty()){
            addRailway("SuperSource", station->getName(), stub);
        }
    }

    for(auto station : stations){
        if(station->getOutgoingRailways().empty() && !station->getIncomingRailways().empty()){
            addRailway(station->getName(), "SuperSink", stub);
        }
    }


    auto superSourcePointer = findStation(superSource.getName());
    auto superSinkPointer = findStation(superSink.getName());

    edmondsKarp(superSourcePointer, superSinkPointer);

    std::map<std::pair<std::string, std::string>, double> pairBudgets;
    std::vector<std::pair<std::pair<std::string, std::string>, double>> returnPairs;

    for(auto station : stations){
        for(auto railway : station->getOutgoingRailways()){
            if(railway->getFlow() > 0){
                pairBudgets[std::make_pair(station->getDistrict(), station->getTownship())] += railway->getFlow();
            }
        }
    }

    for (const auto& element : pairBudgets){
        returnPairs.emplace_back(element);
    }

    std::sort(returnPairs.begin(), returnPairs.end(), [](const std::pair<std::pair<std::string, std::string>, double>& a, const std::pair<std::pair<std::string, std::string>, double>& b){
        return a.second > b.second;
    });

    //Remove the super source and super sink stations from the graph
    if(!removeStation("SuperSource")) std::cout << "SuperSource not removed" << std::endl;
    if(!removeStation("SuperSink")) std::cout << "SuperSink not removed" << std::endl;

    return returnPairs;
}

double Graph::arrivingTrains(const std::string& stationName) {
    Station superSource = Station(-1, "SuperSource", "", "", "", "");
    Station superSink = Station(-2, "SuperSink", "", "", "", "");

    // Add the super source and super sink stations to the graph
    if (!addStation(superSource) || !addStation(superSink)) {
        std::cout << "Error adding super source or super sink" << std::endl;
        return -1;
    }

    Railway stub = Railway("", "", std::numeric_limits<double>::infinity(), "");
    for(auto station : stations){
        if(station->getIncomingRailways().empty() && !station->getOutgoingRailways().empty()){
            addRailway("SuperSource", station->getName(), stub);
        }
    }

    for(auto station : stations){
        if(station->getOutgoingRailways().empty() && !station->getIncomingRailways().empty()){
            addRailway(station->getName(), "SuperSink", stub);
        }
    }

    auto superSourcePointer = findStation(superSource.getName());
    auto superSinkPointer = findStation(superSink.getName());

    edmondsKarp(superSourcePointer, superSinkPointer);

    if(!removeStation("SuperSource")) std::cout << "SuperSource not removed" << std::endl;
    if(!removeStation("SuperSink")) std::cout << "SuperSink not removed" << std::endl;

    auto station = findStation(stationName);
    if(station == nullptr){
        return -2;
    }

    double totalTrains = 0;

    if(station->getIncomingRailways().empty()){
        for(auto railway : station->getOutgoingRailways()){
            totalTrains += railway->getFlow();
        }
    }
    else{
        for(auto railway : station->getIncomingRailways()){
            totalTrains += railway->getFlow();
        }
    }

    return totalTrains;
}