//
// Created by Joao on 4/1/2023.
//

#ifndef PROJETO_1_LINE_RELIABILITY_H
#define PROJETO_1_LINE_RELIABILITY_H

#include "Menu.h"

class Line_Reliability: public Menu{
public:
    explicit Line_Reliability(const Graph &graph);
    bool start();
};


#endif //PROJETO_1_LINE_RELIABILITY_H