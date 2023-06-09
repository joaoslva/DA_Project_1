#ifndef PROJETO_1_SERVICE_METRICS_H
#define PROJETO_1_SERVICE_METRICS_H

#include "Menu.h"
#include "../Graph.h"

class Service_Metrics: public Menu {
public:
    explicit Service_Metrics(const Graph &graph);
    void help();
    bool start();
    void maxTrainsAB();
    void pairsWithMostTrains();
    void upTheBudget();
    void arrivingTrains();
};


#endif //PROJETO_1_SERVICE_METRICS_H
