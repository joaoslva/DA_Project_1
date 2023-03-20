
#include "Csv_reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Station.h"


std::vector<Station> Csv_reader::read_stations(const std::string &filename) {
    std::vector<Station> stations;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return stations;
    }

    std::string line;
    getline(file, line); // Skip header line
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string name, district, municipality, township, line_name;

        getline(iss, name, ',');
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        getline(iss, township, ',');
        getline(iss, line_name, ',');

        stations.emplace_back(name, district, municipality, township, line_name);
    }

    file.close();
    return stations;


}
std::vector<Network> Csv_reader::read_network_csv(const std::string &filename){
    std::vector<Network> network_segments;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        getline(file, line); // Skip header line

        while (getline(file, line)) {
            std::istringstream line_stream(line);
            std::string station_A, station_B, capacity_str, service;

            getline(line_stream, station_A, ',');
            getline(line_stream, station_B, ',');
            getline(line_stream, capacity_str, ',');
            getline(line_stream, service, ',');

            int capacity = stoi(capacity_str);
            network_segments.emplace_back(station_A, station_B, capacity, service);
        }

        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return network_segments;
}

