#ifndef PROJETO_1_OPERATION_COST_OPTIMIZATION_H
#define PROJETO_1_OPERATION_COST_OPTIMIZATION_H

#include "Menu.h"

class Operation_Cost_optimization: public Menu {
public:
    explicit Operation_Cost_optimization(const Graph &graph);
    void optimalCost();
    void help();
    bool start();
};


#endif //PROJETO_1_OPERATION_COST_OPTIMIZATION_H
