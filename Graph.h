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


    /**
     * @brief Adds a station to the graph if it doesn't already exist.
     * @param station The station object to be added.
     * @return True if the station was added, False if the station already exists.
     * @note Time-complexity: O(V) (where V is the number of vertices (stations)).
     */
    bool addStation(const Station& station);






    /**
     * @brief Adds a railway between the source and destiny stations if they both exist.
     * @param sourceStation The name of the source station.
     * @param destinyStation The name of the destiny station.
     * @param railway The railway object to be added.
     * @return True if the railway was added, False if either source or destiny stations do not exist.
     * @note Time-complexity: O(V) (where V is the number of vertices (stations)).
     */
    bool addRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const;







    /**
     * @brief Adds a bidirectional railway between the source and destiny stations if they both exist.
     * @param sourceStation The name of the source station.
     * @param destinyStation The name of the destiny station.
     * @param railway The railway object to be added.
     * @return True if the bidirectional railway was added, False if either source or destiny stations do not exist.
     * @note Time-complexity: O(V) (where V is the number of vertices (stations)).
     */
    bool addBidirectionalRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const;







    /**
     * @brief Searches for a station in the graph by its name.
     * @param name The name of the station to be found.
     * @return Pointer to the Station if found, nullptr if not found.
     * @note Time-complexity: O(V) (where V is the number of vertices (stations))
     */
    Station* findStation(const std::string &name) const;







    /**
     * @brief Retrieves the list of stations in the graph.
     * @return Vector of pointers to the Station objects in the graph.
     * @note Time-complexity: O(1).
     */
    std::vector<Station*> getStations() const;






    /**
    * @brief Removes a station from the graph along with its incoming and outgoing railways.
    * @param name The name of the station to remove.
    * @return true if the station was removed successfully, false otherwise.
    * @note Time-complexity: O(V + E) (where V is the number of vertices and E is the number of edges connected to the station being removed).
    */
    bool removeStation(const std::string& name);





    /**
     * @brief Calculates the number of unique districts in the graph.
     * @return The number of unique districts in the graph.
     * @note Time-complexity: O(V^2) (where V is the number of vertices).
     */
    int getDistrictNumber() const;







    /**
     * @brief Calculates the number of unique municipalities in the graph.
     * @return The number of unique municipalities in the graph.
     * @note Time-complexity: O(V^2) (where V is the number of vertices).
     */
    int getMunicipalityNumber() const;





    /**
     * @brief Marks a station as visited and enqueues it for further processing if it has not been visited yet and the residual capacity is positive.
     * @param queue Reference to the queue used for station processing.
     * @param railway Pointer to the railway connecting the previously visited station with the current station.
     * @param station Pointer to the station being visited.
     * @param residualCapacity The residual capacity of the path leading to the current station
     * @note Time-complexity: O(1) (constant time operations).
     */
    void visitStation(std::queue<Station*> &queue, Railway* railway, Station* station, double residualCapacity);




    /**
     * @brief Finds a path with available capacity between the source and destiny stations using a modified Breadth-First Search (BFS) algorithm.
     * @param source Pointer to the source station.
     * @param destiny Pointer to the destiny station.
     * @return true if a path with available capacity is found, false otherwise.
     * @note Time-complexity: O(V + E) (where V is the number of vertices and E is the number of edges)
     */
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




    /**
     * @brief Calculates pairs of stations with the most trains between them and displays a progress bar while processing.
     * @return A vector of station pairs with the highest number of trains between them.
     * @note Time-complexity: O(V^2) (where V is the number of vertices (stations)).
     */
    std::vector<std::pair<std::pair<std::string, std::string>, double>> pairsWithMostTrains();





    /**
     * @brief Calculates the total train flow for each district-municipality pair and returns a sorted vector of pairs (district, municipality) and their corresponding train flows in descending order.
     * @return A sorted vector of pairs (district, municipality) and their corresponding train flows.
     * @note Time-complexity: O(V^2) (where V is the number of vertices (stations))
     */
    std::vector<std::pair<std::pair<std::string, std::string>, double>> largerBudgetsMunicipalities();





    /**
     * @brief Calculates the total train flow for each district and returns a sorted vector of district names and their corresponding train flows in descending order.
     * @return A sorted vector of district names and their corresponding train flows.
     * @note Time-complexity: O(V^2) (where V is the number of vertices (stations))
     */
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




    /**
    * @brief Calculates the impact of a failure in a set of railway segments by comparing the normal and new global flow for each station.
    * @param segmentsImpacted Vector of pointers to the railway segments impacted by a failure
    * @return A sorted vector of pairs where the first element is a pair of station name and normal flow, and the second element is the changed flow due to the failure
    * @note Time-complexity: O(V^2 * E) (where V is the number of vertices and E is the number of edges)
    */
    std::vector<std::pair<std::pair<std::string, double>,double>> stationSegmentFailureImpact(const std::vector<Railway*>& segmentsImpacted);

private:
    std::vector<Station*> stations;
};

#endif
