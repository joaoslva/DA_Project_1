
#ifndef PROJETO_1_CSVREADER_H
#define PROJETO_1_CSVREADER_H
#include <vector>
#include <string>
#include "StationRailway.h"

class CsvReader {
public:
    static std::vector<Station> readStations(const std::string &filename);
    static std::vector<Railway> readNetwork(const std::string& filename);
};

#endif
