//
// Created by Joao on 4/1/2023.
//

#ifndef PROJETO_1_SERVICE_METRICS_H
#define PROJETO_1_SERVICE_METRICS_H

#include "Menu.h"
#include "../Graph.h"

class Service_Metrics: public Menu {
public:
    explicit Service_Metrics(const Graph &graph, const Graph &directedGraph);
    void help();
    bool start();
    void maxTrainsAB();
    void pairsWithMostTrains();
    void upTheBudget();
    void arrrivingTrains();
};


#endif //PROJETO_1_SERVICE_METRICS_H
