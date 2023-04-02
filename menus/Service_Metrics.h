//
// Created by Joao on 4/1/2023.
//

#ifndef PROJETO_1_SERVICE_METRICS_H
#define PROJETO_1_SERVICE_METRICS_H

#include "Menu.h"
#include "../Graph.h"

class Service_Metrics: public Menu {
public:
    explicit Service_Metrics(const Graph &graph);
    void help();
    bool start();
};


#endif //PROJETO_1_SERVICE_METRICS_H
