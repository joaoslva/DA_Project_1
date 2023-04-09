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
    auto railway2 = destiny->addRailway(source, destinyStation, sourceStation, railway.getCapacity(), railway.getService());
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

    for(auto station : stations){
        if(station->getOutgoingRailways().size() == 1 && station->getName() != stationName){
            Railway stub = Railway("SuperSource", station->getName(), std::numeric_limits<double>::infinity(), "");
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
        std::cout << "|                                                           |\n";
        std::cout << "| The operation cost of this path is " << destinyStation->getDistance() << "€.";
        for(int i = 0; i < 59 - 38 - std::to_string(destinyStation->getDistance()).size(); i++){
            std::cout << " ";
        }
        std::cout << "|\n";
        std::cout << "| It can support " << destinyStation->getBottleneck() << " trains.";
        for(int i = 0; i < 59 - 24 - std::to_string(destinyStation->getBottleneck()).size(); i++){
            std::cout << " ";
        }
        std::cout << "|\n";
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
    auto itr = dest;
    std::vector<std::string> reversePath;
    while(itr != orig){
        reversePath.push_back(itr->getName());
        itr = itr->getPath()->getSourceStationPointer();
    }
    reversePath.push_back(itr->getName());

    std::cout << "| Here's the optimal path from " << orig->getName() << " to " << dest->getName() << ":";
    for(int i = 0; i < 59 - orig->getName().length() - dest->getName().length() - 35; i++){
        std::cout << " ";
    }
    std::cout << "|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| ";
    int charCount = 1;

    for(auto itr2 = reversePath.rbegin(); itr2 != reversePath.rend() - 1; itr2++){
        charCount += (*itr2).length() + 4;
        if(charCount > 57){
            std::cout << "\n| ";
            charCount = (*itr2).length() + 5;
        }
        std::cout << *itr2 << " -> ";
    }

    if(charCount + orig->getName().length() > 55){
        for(int i = 0; i < 59 - charCount; i++){
            std::cout << " ";
        }
        std::cout << "|\n| ";
    }
    std::cout << reversePath.front();
    for(int i = 0; i < 59 - charCount - reversePath.front().length(); i++){
        std::cout << " ";
    }
    std::cout << "|\n";
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
    if(sourceStation->getLine()!=line && destinyStation->getLine()!=line){
        return -4;
    }
    if(sourceStation->getLine()!=line){
        return -5;
    }
    if(destinyStation->getLine()!=line){
        return -6;
    }
    std::vector<Railway> severedRailways;
    for(auto station:stations){
        if(station->getLine()!=line){
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
        addRailway(railway.getSourceStationString(),railway.getDestinyStationString(),railway);
    }
    return ans;
}

std::vector<std::pair<std::pair<std::string, double>,double>> Graph::stationSegmentFailureImpact(const std::vector<Railway*>& segmentsImpacted){

    //Normal global flow for each station
    std::map<std::string, double> normalFlow;
    for(int i=0;i<stations.size();i++){
        std::string name = stations[i]->getName();
        normalFlow[name] = arrivingTrains(name);
    }
    //Sever connections between stations
    std::vector<Railway> restoreRailways;
    for (auto railway: segmentsImpacted){
        auto sourceStation = railway->getSourceStationPointer();
        restoreRailways.emplace_back(railway->getSourceStationString(),railway->getDestinyStationString(),railway->getCapacity(),railway->getService());
        sourceStation->removeRailway(railway);
    }
    for(auto station: stations){
        if(station->getName()=="Cruz Quebrada" || station->getName() == "Caxias"){
            std::cout << "|--------------------\n";
            std::cout << "Station name: " << station->getName() << std::endl;
            std::cout << "Station township: " << station->getTownship() << std::endl;
            for(auto railway: station->getOutgoingRailways()){
                std::cout << "  Destination: " << railway->getDestinyStationPointer()->getName() << ", Capacity: " << railway->getCapacity() << ", Service: " << railway->getService() << std::endl;
            }
        }
    }
    //Calculate new global flow for each station
    std::map<std::pair<std::string,double>,double> changedFlow;
    for(std::pair<std::string,double> p1:normalFlow){
        changedFlow[p1] = arrivingTrains(p1.first);
    }
    //Push results to a vector and sort
    std::vector<std::pair<std::pair<std::string, double>,double>> ans;
    ans.reserve(changedFlow.size());
    for(auto ele:changedFlow){
        ans.emplace_back(ele);
    }
    std::sort(ans.begin(),ans.end(), [](const std::pair<std::pair<std::string, double>,double>& p1, const std::pair<std::pair<std::string, double>,double>& p2){
        return (p1.first.second-p1.second) > (p2.first.second-p2.second);
    });
    //Restore severed connection
    for(auto railway:restoreRailways){
        addRailway(railway.getSourceStationString(),railway.getDestinyStationString(),railway);
    }
    for(auto station: stations){
        if(station->getName()=="Cruz Quebrada" || station->getName() == "Caxias"){
            std::cout << "|--------------------\n";
            std::cout << "Station name: " << station->getName() << std::endl;
            std::cout << "Station township: " << station->getTownship() << std::endl;
            for(auto railway: station->getOutgoingRailways()){
                std::cout << "  Destination: " << railway->getDestinyStationPointer()->getName() << ", Capacity: " << railway->getCapacity() << ", Service: " << railway->getService() << std::endl;
            }
        }
    }
    return ans;
}