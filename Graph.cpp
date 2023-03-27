#include <stdexcept>
#include "Graph.h"

Graph::Graph() {}

void Graph::addStation(const Station &station) {
    stations[station.getName()] = station;
}

void Graph::addConnection(const Network &network) {
    connections[network.getStation_A()].push_back(network);
    connections[network.getStation_B()].push_back(network);
}
const Station &Graph::getStation(const std::string &name) const {
    auto it = stations.find(name);
    if (it != stations.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Station not found");
    }
}

const std::vector<Network> &Graph::getConnections(const std::string &stationName) const {
    auto it = connections.find(stationName);
    if (it != connections.end()) {
        return it->second;
    } else {
        throw std::runtime_error("No connections found for the given station");
    }
}
