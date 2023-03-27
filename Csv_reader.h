
#ifndef PROJETO_1_CSV_READER_H
#define PROJETO_1_CSV_READER_H
#include <vector>
#include <string>
#include "Station.h"
#include "Network.h"
class Csv_reader {
public:
    std::vector<Station> read_stations(const std::string &filename);
    std::vector<Network> read_network_csv(const std::string& filename);
};

#endif
