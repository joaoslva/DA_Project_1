
#ifndef PROJETO_1_NETWORK_H
#define PROJETO_1_NETWORK_H


#include <string>

class Network {
public:
    Network(const std::string &station_A, const std::string &station_B, int capacity, const std::string &service);

    const std::string &getStation_A() const;
    const std::string &getStation_B() const;
    int getCapacity() const;
    const std::string &getService() const;

private:
    std::string station_A;
    std::string station_B;
    int capacity;
    std::string service;
};

#endif
