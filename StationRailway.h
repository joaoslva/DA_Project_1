//
// Created by Joao on 3/28/2023.
//

#ifndef PROJETO_1_STATIONRAILWAY_H
#define PROJETO_1_STATIONRAILWAY_H

#include <string>
#include <vector>
#include "MutablePriorityQueue.h"

class Railway;

/* Station class */
class Station{
public:
    Station();
    Station(const int &id,
            const std::string &name,
            const std::string &district,
            const std::string &municipality,
            const std::string &township,
            const std::string &line
    );

    void removeRailway(Railway* railway);
    void deleteRailway(Railway* railway);
    //Getters
    const std::string &getName() const;
    const std::string &getDistrict() const;
    const std::string &getMunicipality() const;
    const std::string &getTownship() const;
    const std::string &getLine() const;
    int getId() const;
    std::vector<Railway*> getOutgoingRailways() const;
    std::vector<Railway*> getIncomingRailways() const;
    bool isVisited() const;
    bool isProcessing() const;
    int getDistance() const;
    Railway* getPath() const;
    int getBottleneck() const;

    //Setters
    void setID(int id);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setDistance(int distance);
    void setPath(Railway* previousRailway);
    void setBottleneck(int bottleneck);

    Railway* addRailway(Station* station, std::string sourceName, std::string destinyName, double capacity, const std::string& service);
    bool operator< (const Station station) const{
        return this->getDistance() < station.getDistance();
    }

protected:
    int queueIndex;

private:
    //Fields read from the csv file
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

    //Other
    int id;

    std::vector<Railway*> outgoingRailways;
    std::vector<Railway*> incomingRailways;

    bool visited = false;
    bool processing = false;

    int distance;
    int bottleneck;

    Railway* path = nullptr;

friend class MutablePriorityQueue<Station>;
};

/* Railway class */
class Railway{
public:
    Railway(const std::string& sourceStation, const std::string& destinyStation, double capacity, const std::string& service);
    Railway(Station *sourceStation, Station *destinyStation, std::string sourceName, std::string destinyName, double capacity, const std::string& service);

    //Getters
    Station* getSourceStationPointer() const;
    Station* getDestinyStationPointer() const;
    const std::string &getSourceStationString() const;
    const std::string &getDestinyStationString() const;
    double getCapacity() const;
    const std::string &getService() const;
    double getFlow() const;
    Railway* getReverseRailway() const;

    //Setters
    void setFlow(double flow);
    void setReverseRailway(Railway* reverseRailway);

private:
    std::string sourceStationString;
    std::string destinyStationString;
    double capacity;
    std::string service;

    Station* sourceStationPointer;
    Station* destinyStationPointer;

    double flow;
    Railway* reverseRailway;
};


#endif //PROJETO_1_STATIONRAILWAY_H
