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
    /**
     * @brief Removes a railway from the list of outgoing railways of the station and deletes the railway object.
     * @param railway A pointer to the Railway object to be removed and deleted.
     * @note Time complexity: O(k) where k is the number of outgoing railways from the station.
     */
    void removeRailway(Railway* railway);

    /**
     * @brief Deletes a railway object and removes it from the list of incoming railways of the destiny station.
     * @param railway A pointer to the Railway object to be deleted.
     * @note Time complexity: O(k) where k is the number of incoming railways to the destiny station.
     */
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


    /**
     * @brief Adds a railway between the current station and the specified destination station, with the provided source and destination names, capacity, and service.
     * @param station A pointer to the destination Station object.
     * @param sourceName A reference to a string representing the source station name.
     * @param destinyName A reference to a string representing the destination station name.
     * @param capacity A double representing the capacity of the railway.
     * @param service A reference to a string representing the service type of the railway.
     * @return A pointer to the newly created Railway object.
     * @note Time complexity: O(1) assuming that the push_back operation takes constant time.
     */
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
    /**
     * @brief Constructs a new Railway object with the specified source station, destination station, capacity, and service.
     * @param sourceStation A reference to a string representing the source station name.
     * @param destinyStation A reference to a string representing the destination station name.
     * @param capacity A double representing the capacity of the railway.
     * @param service  A reference to a string representing the service type of the railway.
     * @note Time complexity: O(1).
     */
    Railway(const std::string& sourceStation, const std::string& destinyStation, double capacity, const std::string& service);

    /**
     * @brief Constructs a new Railway object with the specified source station, destination station, source and destination names, capacity, and service.
     * @param sourceStation A pointer to the source Station object.
     * @param destinyStation A pointer to the destination Station object.
     * @param sourceName A reference to a string representing the source station name.
     * @param destinyName A reference to a string representing the destination station name.
     * @param capacity A double representing the capacity of the railway.
     * @param service A reference to a string representing the service type of the railway.
     * @note Time complexity: O(1).
     */
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
