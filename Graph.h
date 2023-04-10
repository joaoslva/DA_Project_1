#ifndef PROJETO_1_GRAPH_H
#define PROJETO_1_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unistd.h>
#include <map>
#include <limits>
#include <stack>
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


    /**
    * @brief Calculates the minimum residual capacity along the path from source to destiny station.
    * @param source Pointer to the source station.
    * @param destiny Pointer to the destiny station.
    * @return Minimum residual capacity of the path.
    * @note Time complexity: O(|V|) for a graph with |V| vertices.
    */
    double minResidualCapacity(Station* source, Station* destiny);
    /**
    * @brief Augments the flow along the path from source to destiny station by the given residual capacity.
    * @param source Pointer to the source station.
    * @param destiny Pointer to the destiny station.
    * @param residualCapacity The amount by which the flow should be augmented.
    * @note Time complexity: O(|V|) for a graph with |V| vertices.
    */
    void augmentFlow(Station* source, Station* destiny, double residualCapacity);

    /**
    * @brief Computes the maximum flow in a flow network using the Edmonds-Karp algorithm.
    * @param sourceStation Pointer to the source station.
    * @param destinyStation Pointer to the destination station.
    * @return Maximum flow between source and destination stations.
    * @note Time complexity: O(|V|^3) for a graph with |V| vertices.
    */
    double edmondsKarp(Station* sourceStation, Station* destinyStation);

    //Functions for the requests
    /**
    * @brief Calculates the maximum number of trains that can travel between two stations using the Edmonds-Karp algorithm.
    * @param source The name of the source station.
    * @param destiny The name of the destiny station.
    * @return Maximum number of trains between the source and destiny stations, or an error code (-1, -2, or -3) if the stations are invalid or the same.
    * @note Time complexity: O(|V|^3) for a graph with |V| vertices, as it calls the edmondsKarp function.
    */
    double getTrainsBetweenStations(const std::string& source, const std::string& destiny);
    std::vector<std::pair<std::pair<std::string, std::string>, double>> pairsWithMostTrains();
    std::vector<std::pair<std::pair<std::string, std::string>, double>> largerBudgetsMunicipalities();
    std::vector<std::pair<std::string, double>> largerBudgetsDistricts();
    /**
    * @brief Calculates the total number of trains arriving at a given station using the Edmonds-Karp algorithm.
    * @param stationName The name of the station for which the arriving trains should be calculated.
    * @return The total number of trains arriving at the specified station, or -1 if the station is not found or an error occurs.
    * @note Time complexity: O(|V|^3) for a graph with |V| vertices, as it calls the edmondsKarp function.
    */
    double arrivingTrains(const std::string& stationName);
    /**
    * @brief Calculates the optimal cost of trains traveling between two stations using a cost variant of the Edmonds-Karp algorithm.
    * @param source The name of the source station.
    * @param destiny The name of the destiny station.
    * @return Optimal cost of trains between the source and destiny stations, or an error code (-1, -2, or -3) if the stations are invalid or the same.
    * @note Time complexity depends on the implementation of the costEdmondsKarp function.
    */
    double optimalCostTrains(const std::string& source, const std::string& destiny);
    /**
    * @brief Computes the minimum cost for maximum flow in a flow network using a cost variant of the Edmonds-Karp algorithm.
    * @param sourceStation Pointer to the source station.
    * @param destinyStation Pointer to the destination station.
    * @return Minimum cost for maximum flow between source and destination stations.
    * @note Time complexity depends on the implementation of findPath, minResidualCapacityCost, and augmentFlow functions.
    */
    bool dijkstra(std::string& source, std::string& dest);
    /**
    * @brief Calculates the minimum residual capacity and cost along the path from source to destiny station.
    * @param source Pointer to the source station.
    * @param destiny Pointer to the destiny station.
    * @return A pair where the first element is the cost and the second element is the minimum residual capacity of the path.
    * @note Time complexity: O(|V|) for a graph with |V| vertices.
    */
    void printPath(Station* orig, Station* dest);
    /**
    *
    * @param source A reference to a string representing the name of the source station.
    * @param destiny A reference to a string representing the name of the destiny station.
    * @param line A reference to a string representing the line on which the stations reside.
    * @return A double representing the maximum number of trains that can be sent from the source to the destiny station.
    * @note Time complexity: O(|V|^2 * |E|) for a graph with |V| vertices and |E| edges, assuming the Edmonds-Karp algorithm is used to compute the maximum flow.
    */
    double getTrainsBetweenStationsReduced(const std::string &source, const std::string &destiny, const std::string &line, const std::vector<Railway*>& segmentsImpacted);
    std::vector<std::pair<std::pair<std::string, double>,double>> stationSegmentFailureImpact(const std::vector<Railway*>& segmentsImpacted);

private:
    std::vector<Station*> stations;
};

#endif
