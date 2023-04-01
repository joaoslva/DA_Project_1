#ifndef PROJETO_1_GRAPH_H
#define PROJETO_1_GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>
#include "StationRailway.h"

class Graph {
public:
    Graph();
    bool addStation(const Station &station);
    bool addRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway);
    bool addBidirectionalRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway);
    Station* findStation(const std::string &name) const;
    std::vector<Station*> getStations() const;

private:
    std::vector<Station*> stations;
};

#endif
