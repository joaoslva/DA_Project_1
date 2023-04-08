
#ifndef PROJETO_1_CSVREADER_H
#define PROJETO_1_CSVREADER_H
#include <vector>
#include <string>
#include "StationRailway.h"

class CsvReader {
public:
    /**
     * @brief Reads a CSV file containing station data and returns a vector of Station objects.
     * @param filename A reference to a string representing the name of the CSV file to be read.
     * @return A vector of Station objects created from the data in the CSV file.
     * @note Time complexity: O(n) where n is the number of lines in the CSV file.
     */
    static std::vector<Station> readStations(const std::string &filename);

    /**
     * @brief Reads a CSV file containing railway network data and returns a vector of Railway objects.
     * @param filename A reference to a string representing the name of the CSV file to be read.
     * @return A vector of Railway objects created from the data in the CSV file.
     * @note Time complexity: O(n) where n is the number of lines in the CSV file.
     */
    static std::vector<Railway> readNetwork(const std::string& filename);
};

#endif
