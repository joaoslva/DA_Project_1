#ifndef STATION_H
#define STATION_H
using namespace std;

#include <string>

class Station {
public:
    Station();
    Station(const string &name, const string &district, const string &municipality,
            const string &township, const string &line);

    const string &getName() const;
    const string &getDistrict() const;
    const string &getMunicipality() const;
    const string &getTownship() const;
    const string &getLine() const;

private:
    string name;
    string district;
    string municipality;
    string township;
    string line;
};

#endif