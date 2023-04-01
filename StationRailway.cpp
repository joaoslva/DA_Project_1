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

Railway *Station::addRailway(Station *station, int capacity, const std::string &service) {
    Railway* railway = new Railway(this, station, capacity, service);
    outgoingRailways.push_back(railway);
    station->incomingRailways.push_back(railway);
    return railway;
}

// Raillway

Railway::Railway(const std::string& sourceStation, const std::string& destinyStation, int capacity, const std::string &service) {
    this->sourceStationString = sourceStation;
    this->destinyStationString = destinyStation;
    this->capacity = capacity;
    this->service = service;
    flow = 0;
}

Railway::Railway(Station *origin, Station *destination, int capacity, const std::string &service) {
    this->sourceStationPointer = origin;
    this->destinyStationPointer = destination;
    this->capacity = capacity;
    this->service = service;
}

int Railway::getCapacity() const {
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

Railway* Railway::getPreviousRailway() const {
    return previousRailway;
}

void Railway::setPreviousRailway(Railway *previousRailway) {
    Railway::previousRailway = previousRailway;
}
