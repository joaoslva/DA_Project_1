#include "Station.h"

Station::Station(const string &name, const string &district, const string &municipality,
                 const string &township, const string &line)
        : name(name), district(district), municipality(municipality), township(township), line(line) {}

const string &Station::getName() const {
    return name;
}

const string &Station::getDistrict() const {
    return district;
}

const string &Station::getMunicipality() const {
    return municipality;
}

const string &Station::getTownship() const {
    return township;
}

const string &Station::getLine() const {
    return line;
}