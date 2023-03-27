
#include "Network.h"
Network::Network(const std::string &station_A, const std::string &station_B, int capacity, const std::string &service)
        : station_A(station_A), station_B(station_B), capacity(capacity), service(service) {}

const std::string &Network::getStation_A() const {
    return station_A;
}

const std::string &Network::getStation_B() const {
    return station_B;
}

int Network::getCapacity() const {
    return capacity;
}

const std::string &Network::getService() const {
    return service;
}