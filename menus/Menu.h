//
// Created by Joao on 4/1/2023.
//

#ifndef PROJETO_1_MENU_H
#define PROJETO_1_MENU_H

#include <iostream>
#include <limits>
#include <string>
#include "../Graph.h"

class Menu {
protected:
    Graph graph;
public:
    explicit Menu(const Graph &graph);
    void start();
    void checkStay(bool& condition, const std::string& previousChoice);
};


#endif //PROJETO_1_MENU_H
