//
// Created by Joao on 3/28/2023.
//

#ifndef PROJETO_1_STATIONRAILWAY_H
#define PROJETO_1_STATIONRAILWAY_H

#include <string>
#include <vector>

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

    //Setters
    void setID(int id);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setDistance(int distance);
    void setPreviousRailway(Railway* previousRailway);

    Railway* addRailway(Station* station, int capacity, const std::string& service);

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

    int distance = INT_MAX;
};

/* Railway class */
class Railway{
public:
    Railway(const std::string& sourceStation, const std::string& destinyStation, int capacity, const std::string& service);
    Railway(Station *sourceStation, Station *destinyStation, int capacity, const std::string& service);

    //Getters
    Station* getSourceStationPointer() const;
    Station* getDestinyStationPointer() const;
    const std::string &getSourceStationString() const;
    const std::string &getDestinyStationString() const;
    int getCapacity() const;
    const std::string &getService() const;
    double getFlow() const;
    Railway* getPreviousRailway() const;

    //Setters
    void setFlow(double flow);
    void setPreviousRailway(Railway* previousRailway);

private:
    std::string sourceStationString;
    std::string destinyStationString;

    Station* sourceStationPointer;
    Station* destinyStationPointer;
    int capacity;
    std::string service;

    double flow;

    Station* sourceVertex;
    Railway* previousRailway;
};


#endif //PROJETO_1_STATIONRAILWAY_H