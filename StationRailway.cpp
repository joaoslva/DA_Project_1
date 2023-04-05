//
// Created by Joao on 3/28/2023.
//

#include "StationRailway.h"

// Station
Station::Station() {
    this->id = 0;
    this->name = "";
    this->district = "";
    this->municipality = "";
    this->township = "";
    this->line = "";
}

Station::Station(const int &id, const std::string &name, const std::string &district, const std::string &municipality,
                 const std::string &township, const std::string &line) {
    this->id = id;
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

void Station::removeRailway(Railway *railway) {
    auto it = outgoingRailways.begin();
    while (it != outgoingRailways.end()) {
        Railway* r = *it;
        Station* s = r->getDestinyStationPointer();
        if(s->getId() == railway->getDestinyStationPointer()->getId()){
            it = outgoingRailways.erase(it);
            deleteRailway(r);
        }
        else{
            it++;
        }
    }
}

void Station::deleteRailway(Railway *railway) {
    Station* destinyStation = railway->getDestinyStationPointer();
    auto it = destinyStation->incomingRailways.begin();
    while (it != destinyStation->incomingRailways.end()) {
        if((*it)->getSourceStationPointer()->getId() == this->getId()){
            it = destinyStation->incomingRailways.erase(it);
        }
        else{
            it++;
        }
    }
    delete railway;
}

const std::string &Station::getName() const {
    return name;
}

const std::string &Station::getDistrict() const {
    return district;
}

const std::string &Station::getMunicipality() const {
    return municipality;
}

const std::string &Station::getTownship() const {
    return township;
}

const std::string &Station::getLine() const {
    return line;
}

int Station::getId() const {
    return id;
}

std::vector<Railway *> Station::getOutgoingRailways() const {
    return outgoingRailways;
}

std::vector<Railway *> Station::getIncomingRailways() const {
    return incomingRailways;
}

bool Station::isVisited() const {
    return visited;
}

bool Station::isProcessing() const {
    return processing;
}

int Station::getDistance() const {
    return distance;
}

void Station::setID(int id) {
    Station::id = id;
}

void Station::setVisited(bool visited) {
    Station::visited = visited;
}

void Station::setProcessing(bool processing) {
    Station::processing = processing;
}

void Station::setDistance(int distance) {
    Station::distance = distance;
}

Railway *Station::addRailway(Station *station, std::string sourceName, std::string destinyName, double capacity, const std::string &service) {
    Railway* railway = new Railway(this, station, sourceName, destinyName, capacity, service);
    outgoingRailways.push_back(railway);
    station->incomingRailways.push_back(railway);
    return railway;
}

void Station::setPath(Railway *previousRailway) {
    this->path = previousRailway;
}

Railway *Station::getPath() const {
    return path;
}

// Raillway

Railway::Railway(const std::string& sourceStation, const std::string& destinyStation, double capacity, const std::string &service) {
    this->sourceStationString = sourceStation;
    this->destinyStationString = destinyStation;
    this->capacity = capacity;
    this->service = service;
    this->flow = 0;
}

Railway::Railway(Station *origin, Station *destination, std::string sourceName, std::string destinyName, double capacity, const std::string &service) {
    this->sourceStationPointer = origin;
    this->destinyStationPointer = destination;
    this->destinyStationString = destinyName;
    this->sourceStationString = sourceStationString;
    this->capacity = capacity;
    this->service = service;
    this->flow = 0;
}

double Railway::getCapacity() const {
    return capacity;
}

double Railway::getFlow() const {
    return flow;
}

const std::string &Railway::getService() const {
    return service;
}

void Railway::setFlow(double flow) {
    Railway::flow = flow;
}

Station *Railway::getSourceStationPointer() const {
    return sourceStationPointer;
}

Station *Railway::getDestinyStationPointer() const {
    return destinyStationPointer;
}

const std::string &Railway::getSourceStationString() const {
    return sourceStationString;
}

const std::string &Railway::getDestinyStationString() const {
    return destinyStationString;
}

Railway* Railway::getReverseRailway() const {
    return reverseRailway;
}

void Railway::setReverseRailway(Railway *reverseRailway) {
    reverseRailway = reverseRailway;
}