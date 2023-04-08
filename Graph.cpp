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


double Graph::edmondsKarp(Station* sourceStation, Station* destinyStation) {
    for (auto station : stations) {
        for (auto railway : station->getOutgoingRailways()) {
            railway->setFlow(0);
        }
    }

    double maxFlow = 0;

    while (findPath(sourceStation, destinyStation)) {
        auto residualCapacity = minResidualCapacity(sourceStation, destinyStation);
        maxFlow += residualCapacity;
        augmentFlow(sourceStation, destinyStation, residualCapacity);
    }

    return maxFlow;
}



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
    std::cout << "| Calculating pairs:                                        |" << std::endl;
    sleep(3);
    std::cout << "| [                    ]" << std::flush; // initial progress bar

    int max = 521;
    int j= 0;
    for(auto station : stations){
        for(auto station2 : stations){
            if(station != station2){
                pairs.emplace_back(std::make_pair(station->getName(), station2->getName()), getTrainsBetweenStations(station->getName(), station2->getName()));
            }
        }
        ++j;
        float progress = static_cast<float>(j) / static_cast<float>(max);
        int barWidth = 20;
        std::cout << "\r| [";
        int pos = static_cast<int>(barWidth * progress);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << static_cast<int>(progress * 100.0) << "% " << std::flush;
    }
    std::cout << std::endl;
    std::cout << "| Done!                                                     |\n";
    std::cout << "|                                                           |\n";

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

    double minCost;
    if(dijkstra(const_cast<std::string &>(sourceStation->getName()),
                   const_cast<std::string &>(destinyStation->getName()))){
        printPath(sourceStation, destinyStation);
        minCost = destinyStation->getDistance()*destinyStation->getBottleneck();
        std::cout << ".\n The cost of this path is " << destinyStation->getDistance() << "€. ";
        std::cout << "It can support " << destinyStation->getBottleneck() << " trains.\n";
        std::cout << "Total: " << destinyStation->getDistance()*destinyStation->getBottleneck() << "€. \n\n";

    }
    else return 0;

    return minCost;
}


bool Graph::dijkstra(std::string& source, std::string& dest) {

    MutablePriorityQueue<Station> q;
    for (Station *station: stations) {
        station->setVisited(false);
        station->setDistance(INT32_MAX);
        station->setPath(nullptr);
        station->setBottleneck(INT32_MAX);
    }
    auto first = findStation(source);
    first->setDistance(0);
    q.insert(first);
    while (!q.empty()) {
        Station *top = q.extractMin();

        if (top->isVisited()) continue;
        top->setVisited(true);

        if (top->getName() == dest) {
            break;
        }
        for (Railway *railway: top->getOutgoingRailways()) {
            Station * contender = railway->getDestinyStationPointer();
            if (contender->isVisited()) continue;

            double cost = (railway->getService() == "STANDARD" ? 2 : 4);
            int bottleNeck = std::min(top->getBottleneck(),static_cast<int> (railway->getCapacity()));

            if (contender->getDistance() > top->getDistance() + cost) {
                contender->setDistance(top->getDistance() + cost);
                contender->setPath(railway);
                contender->setBottleneck(bottleNeck);
                q.insert(contender);
            }

            else if (contender->getDistance() == top->getDistance() + cost && contender->getBottleneck()<bottleNeck) {
                contender->setPath(railway);
                contender->setBottleneck(bottleNeck);
            }

        }
    }

    if (!findStation(dest)->isVisited()) return false;
    return true;
}


void Graph::printPath(Station* orig, Station* dest){
    /*
    auto itr = dest;
    std::stack<std::string> stations;
    auto it = dest;
    for(; it != orig;){
        stations.push(it->getName());
        it = it->getPath()->getSourceStationPointer();
    }
    stations.push(it->getName());
    std::string output;
    std::cout << "| Here's the path from " << orig->getName() << " to " << dest->getName() << ":";
    for(int i = 0; i < 59 - orig->getName().length() - dest->getName().length() - 27; i++) std::cout << " ";
    std::cout << "|\n";
    std::cout << "Here\n";

    while (stations.size() > 1){
        if(output.length() + stations.top().length() + 5 < 57){
            output += stations.top() + " -> ";
            stations.pop();
        }

        else{
            std::cout << "| " << output;
            for(int i = 0; i < 59 - output.length() - 1; i++) std::cout << " ";
            std::cout << "|";
        }
    }

    if(output.length() + stations.top().length() + 5 < 57){
        output += stations.top() + " -> ";
        stations.pop();
        std::cout << output;
        for(int i = 0; i < 59 - output.length() - 1; i++) std::cout << " ";
        std::cout << "|\n";
    }

    else{
        std::cout << "| " << output;
        for(int i = 0; i < 59 - output.length() - 1; i++) std::cout << " ";
        std::cout << "| " << stations.top();
        stations.pop();
        for(int i = 0; i < 59 - output.length() - 1; i++) std::cout << " ";
        std::cout << "|\n";
    }
     */


    auto it = dest;
    if(it != orig){
        printPath(orig, it->getPath()->getSourceStationPointer());
    }

    if(it == orig){
        std::cout << it->getName();
    }

    else {
        std::cout << "->" << it->getName();
    }

}

double Graph::getTrainsBetweenStationsReduced(const std::string &source, const std::string &destiny, const std::string &line) {
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
    if(sourceStation->getLine()==line && destinyStation->getLine()==line){
        return -4;
    }
    if(sourceStation->getLine()==line){
        return -5;
    }
    if(destinyStation->getLine()==line){
        return -6;
    }
    std::vector<Railway> severedRailways;
    for(auto station:stations){
        if(station->getLine()==line){
            auto outgoingRailways = station->getOutgoingRailways();
            for(Railway* railway:outgoingRailways){
                severedRailways.emplace_back(railway->getSourceStationString(),railway->getDestinyStationString(),railway->getCapacity(),railway->getService());
                station->removeRailway(railway);
            }
        }
    }
    sourceStation = findStation(source);
    destinyStation = findStation(destiny);
    double ans = edmondsKarp(sourceStation, destinyStation);
    for(const auto& railway:severedRailways){
        addBidirectionalRailway(railway.getSourceStationString(),railway.getDestinyStationString(),railway);
    }
    return ans;
}