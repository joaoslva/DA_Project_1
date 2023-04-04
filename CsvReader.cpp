
#include "CsvReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


std::vector<Station> CsvReader::readStations(const std::string &filename) {
    std::vector<Station> stations;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return stations;
    }

    std::string line;
    std::string name, district, municipality, township, lineName;
    int id = 1;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        std::istringstream iss(line);

        if(iss.peek() == '"'){
            iss.ignore();
            std::string temp;
            getline(iss, temp, '"');
            getline(iss, name, ',');
            name = temp + name;
        } else {
            getline(iss, name, ',');
        }
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        if(iss.peek() == '"'){
            iss.ignore();
            std::string temp;
            getline(iss, temp, '"');
            getline(iss, township, ',');
            township = temp + township;
        } else {
            getline(iss, township, ',');
        }
        getline(iss, lineName, ',');

        stations.emplace_back(id, name, district, municipality, township, lineName);
        id++;
    }

    file.close();
    return stations;
}

std::vector<Railway> CsvReader::readNetwork(const std::string &filename){
    std::vector<Railway> networkSegments;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return networkSegments;
    }

    std::string line;
    getline(file, line); // Skip header line
    std::string sourceStation, destinyStation, capacityString, service;
    int capacity;

    while (getline(file, line))
    {
        std::istringstream line_stream(line);

        if(line_stream.peek() == '"'){
            line_stream.ignore();
            std::string temp;
            getline(line_stream, temp, '"');
            getline(line_stream, sourceStation, ',');
            sourceStation = temp + sourceStation;
        } else {
            getline(line_stream, sourceStation, ',');
        }

        if(line_stream.peek() == '"'){
            line_stream.ignore();
            std::string temp;
            getline(line_stream, temp, '"');
            getline(line_stream, destinyStation, ',');
            destinyStation = temp + destinyStation;
        } else {
            getline(line_stream, destinyStation, ',');
        }
        getline(line_stream, capacityString, ',');
        getline(line_stream, service, ',');

        capacity = stoi(capacityString);

        networkSegments.emplace_back(sourceStation, destinyStation, capacity, service);
    }

    file.close();

    return networkSegments;
}

