#ifndef PROJETO_1_GRAPH_H
#define PROJETO_1_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include "StationRailway.h"

class Graph {
public:
    bool addStation(const Station &station);
    bool addRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const;
    bool addBidirectionalRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const;
    Station* findStation(const std::string &name) const;
    std::vector<Station*> getStations() const;


    //Edmonds-Karp and auxiliary functions
    void visitStation(std::queue<Station*> &queue, Railway* railway, Station* station, double residualCapacity);
    bool findPath(Station* source, Station* destiny);
    double minResidualCapacity(Station* source, Station* destiny);
    void augmentFlow(Station* source, Station* destiny, double residualCapacity);
    void edmondsKarp(Station* sourceStation, Station* destinyStation);

    //Functions for the requests
    double getTrainsBetweenStations(const std::string& source, const std::string& destiny);

private:
    std::vector<Station*> stations;
};

#endif
