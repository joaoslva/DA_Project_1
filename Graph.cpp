#include "Graph.h"



bool Graph::addStation(const Station& station) {
    if(findStation(station.getName()) != nullptr){
        return false;
    }
    stations.push_back(new Station(station));
    return true;
}

bool Graph::addRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const {
    auto source = findStation(sourceStation);
    auto destiny = findStation(destinyStation);
    if(source == nullptr || destiny == nullptr){
        return false;
    }
    source->addRailway(destiny, sourceStation, destinyStation, railway.getCapacity(), railway.getService());
    return true;
}

bool Graph::addBidirectionalRailway(const std::string& sourceStation, const std::string& destinyStation, const Railway& railway) const {
    auto source = findStation(sourceStation);
    auto destiny = findStation(destinyStation);
    if(source == nullptr || destiny == nullptr){
        return false;
    }
    auto railway1 = source->addRailway(destiny, sourceStation, destinyStation, railway.getCapacity(), railway.getService());
    auto railway2 = destiny->addRailway(source, sourceStation, destinyStation, railway.getCapacity(), railway.getService());
    railway1->setReverseRailway(railway2);
    railway2->setReverseRailway(railway1);
    return true;
}

Station* Graph::findStation(const std::string &name) const {
    for(auto &station : stations){
        if(station->getName() == name){
            return station;
        }
    }
    return nullptr;
}

std::vector<Station*> Graph::getStations() const {
    return stations;
}

bool Graph::removeStation(const std::string& name) {
    // Find the station to remove
    Station* stationToRemove = findStation(name);
    if (!stationToRemove) {
        return false; // Station not found, cannot remove
    }

    // Remove all incoming and outgoing railways connected to the station
    std::vector<Railway*> outgoingRailways = stationToRemove->getOutgoingRailways();
    for (Railway* railway : outgoingRailways) {
        stationToRemove->removeRailway(railway);
    }
    std::vector<Railway*> incomingRailways = stationToRemove->getIncomingRailways();
    for (Railway* railway : incomingRailways) {
        Station* sourceStation = railway->getSourceStationPointer();
        sourceStation->removeRailway(railway);
    }

    // Remove the station from the graph
    auto it = std::find(stations.begin(), stations.end(), stationToRemove);
    if (it != stations.end()) {
        stations.erase(it);
        delete stationToRemove; // Free the memory used by the station
        return true;
    } else {
        return false; // Station not found, cannot remove
    }
}

void Graph::visitStation(std::queue<Station*>& queue, Railway* railway, Station* station, double residualCapacity) {
    if (!station->isVisited() && residualCapacity > 0) {
        station->setVisited(true);
        station->setPath(railway);
        queue.push(station);
    }
}

bool Graph::findPath(Station* source, Station* destiny) {
    for (auto station : stations) {
        station->setVisited(false);
    }

    source->setVisited(true);
    std::queue<Station*> queue;
    queue.push(source);

    while (!queue.empty() && !destiny->isVisited()) {
        auto station = queue.front();
        queue.pop();
        for (auto railway : station->getOutgoingRailways()) {
            visitStation(queue, railway, railway->getDestinyStationPointer(), railway->getCapacity() - railway->getFlow());
        }
        for (auto railway : station->getIncomingRailways()) {
            visitStation(queue, railway, railway->getSourceStationPointer(), railway->getFlow());
        }
    }
    return destiny->isVisited();
}
/**
 * @brief Calculates the minimum residual capacity along the path from source to destiny station.
 * @param source Pointer to the source station.
 * @param destiny Pointer to the destiny station.
 * @return Minimum residual capacity of the path.
 * @note Time complexity: O(|V|) for a graph with |V| vertices.
 */
double Graph::minResidualCapacity(Station* source, Station* destiny) {
    double minResidualCapacity = INT_MAX;
    for (auto station = destiny; station != source;) {
        auto railway = station->getPath();
        if (railway->getDestinyStationPointer() == station) {
            minResidualCapacity = std::min(minResidualCapacity, railway->getCapacity() - railway->getFlow());
            station = railway->getSourceStationPointer();
        }
        else {
            minResidualCapacity = std::min(minResidualCapacity, railway->getFlow());
            station = railway->getDestinyStationPointer();
        }
    }
    return minResidualCapacity;
}
/**
 * @brief Augments the flow along the path from source to destiny station by the given residual capacity.
 * @param source Pointer to the source station.
 * @param destiny Pointer to the destiny station.
 * @param residualCapacity The amount by which the flow should be augmented.
 * @note Time complexity: O(|V|) for a graph with |V| vertices.
 */

void Graph::augmentFlow(Station* source, Station* destiny, double residualCapacity) {
    for (auto station = destiny; station != source;) {
        auto railway = station->getPath();
        double flow = railway->getFlow();
        if (railway->getDestinyStationPointer() == station) {
            railway->setFlow(flow + residualCapacity);
            station = railway->getSourceStationPointer();
        }
        else {
            railway->setFlow(flow - residualCapacity);
            station = railway->getDestinyStationPointer();
        }
    }
}
/**
 * @brief Computes the maximum flow in a flow network using the Edmonds-Karp algorithm.
 * @param sourceStation Pointer to the source station.
 * @param destinyStation Pointer to the destination station.
 * @return Maximum flow between source and destination stations.
 * @note Time complexity: O(|V|^3) for a graph with |V| vertices.
 */

double Graph::edmondsKarp(Station* sourceStation, Station* destinyStation) {
    for (auto station : stations) {
        for (auto railway : station->getOutgoingRailways()) {
            railway->setFlow(0);
        }
    }

    double maxFlow = 0;
    int i = 0;

    while (findPath(sourceStation, destinyStation)) {
        std::cout << "Path " << i++ << std::endl;
        auto residualCapacity = minResidualCapacity(sourceStation, destinyStation);
        maxFlow += residualCapacity;
        augmentFlow(sourceStation, destinyStation, residualCapacity);
    }

    return maxFlow;
}

/**
 * @brief Calculates the maximum number of trains that can travel between two stations using the Edmonds-Karp algorithm.
 * @param source The name of the source station.
 * @param destiny The name of the destiny station.
 * @return Maximum number of trains between the source and destiny stations, or an error code (-1, -2, or -3) if the stations are invalid or the same.
 * @note Time complexity: O(|V|^3) for a graph with |V| vertices, as it calls the edmondsKarp function.
 */

double Graph::getTrainsBetweenStations(const std::string &source, const std::string &destiny) {
    auto sourceStation = findStation(source);
    auto destinyStation = findStation(destiny);
    if(sourceStation == nullptr){
        return -1;
    }

    if(destinyStation == nullptr){
        return -2;
    }

    if(sourceStation == destinyStation){
        return -3;
    }

    return edmondsKarp(sourceStation, destinyStation);
}

std::vector<std::pair<std::pair<std::string, std::string>, double>> Graph::pairsWithMostTrains() {
    std::vector<std::pair<std::pair<std::string, std::string>, double>> pairs;
    std::vector<std::pair<std::pair<std::string, std::string>, double>> returnPairs;
    for(auto station : stations){
        for(auto station2 : stations){
            if(station != station2){
                pairs.emplace_back(std::make_pair(station->getName(), station2->getName()), getTrainsBetweenStations(station->getName(), station2->getName()));
            }
        }
    }

    std::sort(pairs.begin(), pairs.end(), [](const std::pair<std::pair<std::string, std::string>, double>& a, const std::pair<std::pair<std::string, std::string>, double>& b){
        return a.second > b.second;
    });

    returnPairs.push_back(pairs[0]);
    for(int i = 1; i < pairs.size(); i++){
        if(pairs[i].second == pairs[0].second){
            returnPairs.push_back(pairs[i]);
        }
        else{
            break;
        }
    }

    return returnPairs;
}

std::vector<std::pair<std::pair<std::string, std::string>, double>> Graph::largerBudgets() {

    // Create the super source and super sink stations
    Station superSource = Station(-1, "SuperSource", "", "", "", "");
    Station superSink = Station(-2, "SuperSink", "", "", "", "");

    // Add the super source and super sink stations to the graph
    if (!addStation(superSource) || !addStation(superSink)) {
        std::cout << "Error adding super source or super sink" << std::endl;
        return {};
    }

    Railway stub = Railway("", "", std::numeric_limits<double>::infinity(), "");
    for(auto station : stations){
        if(station->getIncomingRailways().empty() && !station->getOutgoingRailways().empty()){
            addRailway("SuperSource", station->getName(), stub);
        }
    }

    for(auto station : stations){
        if(station->getOutgoingRailways().empty() && !station->getIncomingRailways().empty()){
            addRailway(station->getName(), "SuperSink", stub);
        }
    }


    auto superSourcePointer = findStation(superSource.getName());
    auto superSinkPointer = findStation(superSink.getName());

    edmondsKarp(superSourcePointer, superSinkPointer);

    std::map<std::pair<std::string, std::string>, double> pairBudgets;
    std::vector<std::pair<std::pair<std::string, std::string>, double>> returnPairs;

    for(auto station : stations){
        for(auto railway : station->getOutgoingRailways()){
            if(railway->getFlow() > 0){
                pairBudgets[std::make_pair(station->getDistrict(), station->getTownship())] += railway->getFlow();
            }
        }
    }

    for (const auto& element : pairBudgets){
        returnPairs.emplace_back(element);
    }

    std::sort(returnPairs.begin(), returnPairs.end(), [](const std::pair<std::pair<std::string, std::string>, double>& a, const std::pair<std::pair<std::string, std::string>, double>& b){
        return a.second > b.second;
    });

    //Remove the super source and super sink stations from the graph
    if(!removeStation("SuperSource")) std::cout << "SuperSource not removed" << std::endl;
    if(!removeStation("SuperSink")) std::cout << "SuperSink not removed" << std::endl;

    return returnPairs;
}
/**
 * @brief Calculates the total number of trains arriving at a given station using the Edmonds-Karp algorithm.
 * @param stationName The name of the station for which the arriving trains should be calculated.
 * @return The total number of trains arriving at the specified station, or -1 if the station is not found or an error occurs.
 * @note Time complexity: O(|V|^3) for a graph with |V| vertices, as it calls the edmondsKarp function.
 */

double Graph::arrivingTrains(const std::string& stationName) {
    auto stationDestPointer = findStation(stationName);
    if(!stationDestPointer)
        return -1;

    Station superSource = Station(-1, "SuperSource", "", "", "", "");

    // Add the super source and super sink stations to the graph
    if (!addStation(superSource)) {
        std::cout << "Error adding super source" << std::endl;
        return -1;
    }

    Railway stub = Railway("", "", std::numeric_limits<double>::infinity(), "");
    for(auto station : stations){
        if(station->getOutgoingRailways().size() == 1 && station->getName() != stationName){
            addRailway("SuperSource", station->getName(), stub);
        }
    }

    auto superSourcePointer = findStation(superSource.getName());

    double totalTrains;

    //The total number of trains that can reach the dest station is the max flow of the edmonds karp algorithm
    totalTrains = edmondsKarp(superSourcePointer, stationDestPointer);

    if(!removeStation("SuperSource")) std::cout << "SuperSource not removed" << std::endl;

    return totalTrains;
}
/**
 * @brief Calculates the optimal cost of trains traveling between two stations using a cost variant of the Edmonds-Karp algorithm.
 * @param source The name of the source station.
 * @param destiny The name of the destiny station.
 * @return Optimal cost of trains between the source and destiny stations, or an error code (-1, -2, or -3) if the stations are invalid or the same.
 * @note Time complexity depends on the implementation of the costEdmondsKarp function.
 */

double Graph::optimalCostTrains(const std::string& source, const std::string& destiny){
    for (auto station : stations) {
        for (auto railway : station->getOutgoingRailways()) {
            railway->setFlow(0);
        }
    }
    auto sourceStation = findStation(source);
    auto destinyStation = findStation(destiny);
    if(sourceStation == nullptr){
        return -1;
    }

    if(destinyStation == nullptr){
        return -2;
    }

    if(sourceStation == destinyStation){
        return -3;
    }

    int minCost = 0;
    while(dijkstra(const_cast<std::string &>(sourceStation->getName()),
                   const_cast<std::string &>(destinyStation->getName()))){
        printPath(sourceStation, destinyStation);
        auto residualCapacity = minResidualCapacity(sourceStation, destinyStation);
        augmentFlow(sourceStation, destinyStation, residualCapacity);
        minCost += destinyStation->getDistance()*residualCapacity;
        std::cout << " |- The cost of this path is " << minCost << "€;\n";
    }
    return minCost;
}
/**
 * @brief Computes the minimum cost for maximum flow in a flow network using a cost variant of the Edmonds-Karp algorithm.
 * @param sourceStation Pointer to the source station.
 * @param destinyStation Pointer to the destination station.
 * @return Minimum cost for maximum flow between source and destination stations.
 * @note Time complexity depends on the implementation of findPath, minResidualCapacityCost, and augmentFlow functions.
 */

bool Graph::dijkstra(std::string& source, std::string& dest) {

    std::priority_queue<Station *> q;
    for (Station *station: stations) {
        station->setVisited(false);
        station->setDistance(INT32_MAX);
        station->setPath(nullptr);
    }
    auto first = findStation(source);
    first->setDistance(0);
    q.push(first);
    while (!q.empty()) {
        Station *top = q.top();
        q.pop();

        if (top->isVisited()) continue;
        top->setVisited(true);

        if (top->getName() == dest) {
            break;
        }
        for (Railway *railway: top->getOutgoingRailways()) {
            Station * contender = railway->getDestinyStationPointer();
            if (contender->isVisited()) continue;

            double cost = (railway->getService() == "STANDARD" ? 2 : 4);
            double residualCapacity = railway->getCapacity()-railway->getFlow();

            if (contender->getDistance() > top->getDistance() + cost && residualCapacity>0) {
                contender->setDistance(top->getDistance() + cost);
                contender->setPath(railway);
                q.push(contender);
            }
        }
    }

    if (!findStation(dest)->isVisited()) return false;
    return true;
}
/**
 * @brief Calculates the minimum residual capacity and cost along the path from source to destiny station.
 * @param source Pointer to the source station.
 * @param destiny Pointer to the destiny station.
 * @return A pair where the first element is the cost and the second element is the minimum residual capacity of the path.
 * @note Time complexity: O(|V|) for a graph with |V| vertices.
 */

void Graph::printPath(Station* orig, Station* dest){
    auto it = dest;
    if(it != orig){
        printPath(orig, it->getPath()->getSourceStationPointer());
    }
    std::cout << "->" << it->getName();
}