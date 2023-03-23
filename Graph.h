#ifndef PROJETO_1_GRAPH_H
#define PROJETO_1_GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Network.h"
#include "Station.h"
class Graph {
public:
    Graph();
    void addStation(const Station &station);
    void addConnection(const Network &network);
    const Station &getStation(const std::string &name) const;
    const std::vector<Network> &getConnections(const std::string &stationName) const;

private:
    std::unordered_map<std::string, Station> stations;
    std::unordered_map<std::string, std::vector<Network>> connections;
};


#endif

