#ifndef PROJETO_1_GRAPH_H
#define PROJETO_1_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include "StationRailway.h"

class Graph {
public:
    bool addStation(const Station& station);
    bool addRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const;
    bool addBidirectionalRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const;
    Station* findStation(const std::string &name) const;
    std::vector<Station*> getStations() const;
    bool removeStation(const std::string& name);



    //Edmonds-Karp and auxiliary functions
    void visitStation(std::queue<Station*> &queue, Railway* railway, Station* station, double residualCapacity);
    bool findPath(Station* source, Station* destiny);
    double minResidualCapacity(Station* source, Station* destiny);
    void augmentFlow(Station* source, Station* destiny, double residualCapacity);
    double edmondsKarp(Station* sourceStation, Station* destinyStation);

    //Functions for the requests
    double getTrainsBetweenStations(const std::string& source, const std::string& destiny);
    std::vector<std::pair<std::pair<std::string, std::string>, double>> pairsWithMostTrains();
    std::vector<std::pair<std::pair<std::string, std::string>, double>> largerBudgets();
    double arrivingTrains(const std::string& stationName);
    double optimalCostTrains(const std::string& source, const std::string& destiny);

    bool dijkstra(std::string& source, std::string& dest);

    void printPath(Station* orig, Station* dest);

private:
    std::vector<Station*> stations;
};

#endif
