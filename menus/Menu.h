#ifndef PROJETO_1_MENU_H
#define PROJETO_1_MENU_H

#include <iostream>
#include <limits>
#include <string>
#include <unistd.h>
#include <iomanip>
#include "../Graph.h"

class Menu {
protected:
    Graph graph;
public:
    explicit Menu(const Graph &graph);
    void start();
    void help();
    void returnMessage();
    void quitMessage();
    void checkStay(bool& condition, const std::string& previousChoice);
};


#endif //PROJETO_1_MENU_H
