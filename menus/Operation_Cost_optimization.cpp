//
// Created by Joao on 4/1/2023.
//

#include "Operation_Cost_optimization.h"

Operation_Cost_optimization::Operation_Cost_optimization(const Graph &graph, const Graph &directedGraph): Menu(graph, directedGraph) {}

bool Operation_Cost_optimization::start() {
    std::cout << "|---------------------------------------------------------- \n";
    std::cout << "|                                                           \n";
    std::cout << "| Welcome to Operation Cost Optimization. Select one of the \n";
    std::cout << "| options below to get started.                             \n";
    std::cout << "|                                                           \n";

    while (true){
        std::string operationCostOptimizationChoice;
        std::cout << "### OPERATION COST OPTIMIZATION MENU ###                    \n";
        std::cout << "|                                                           \n";
        std::cout << "| 1 - Maximum Number of Trains between A a B with optimal   \n";
        std::cout << "|     cost                                                  \n";
        std::cout << "| 2 - Help                                                  \n";
        std::cout << "| r - Return to previous Menu                               \n";
        std::cout << "| q - Quit application                                      \n";
        std::cout << "|                                                           \n";
        std::cout << "| Enter here your choice: ";
        std::getline(std::cin, operationCostOptimizationChoice);
        std::cout << "|                                                           \n";

        if(operationCostOptimizationChoice == "1"){
            optimalCost();
        }

        else if(operationCostOptimizationChoice == "2")
            help();


        else if(operationCostOptimizationChoice == "r"){
            returnMessage();
            return true;
        }
        else if(operationCostOptimizationChoice == "q"){
            quitMessage();
            return false;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "| Select on of the following options                       \n";
        }
    }
}

void Operation_Cost_optimization::help() {
    std::string helpChoice;

    std::cout << "|------------------------Help Page-------------------------\n";
    std::cout << "|                                                          \n";
    std::cout << "| How each option works                                    \n";
    std::cout << "|                                                          \n";
    std::cout << "| Maximum Number of Trains between A a B with optimal cost: \n";
    std::cout << "|   Given two train stations, this option will return the  \n";
    std::cout << "|   maximum number of trains that can travel between them  \n";
    std::cout << "|   at the same time, taking in account the train type and \n";
    std::cout << "|   respective cost of operation.                                 \n";
    std::cout << "|                                                          \n";
    std::cout << "| Write 'back' to go to the previous page                  \n";
    std::cout << "| Enter here: ";

    while(true){
        std::getline(std::cin, helpChoice);
        std::cout << "|                                                          \n";

        if(helpChoice == "back"){
            std::cout << " ---------------------------------------------------------- \n";
            std::cout << "|                                                          \n";
            std::cout << "| Select one of the Operation Cost Optimization options below \n";
            break;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            std::cout << "| Enter here: ";
        }
    }
}

void Operation_Cost_optimization::optimalCost(){
    bool option1Stay = true;
    double maxTrains;
    std::string sourceStation, destinyStation;
    std::cout << "| Welcome to Maximum Number of Trains between stations A and B  \n|\n";
    while(option1Stay){
        std::cout << "| Enter the source station: ";
        std::getline(std::cin, sourceStation);
        std::cout << "| Enter the destiny station: ";
        std::getline(std::cin, destinyStation);
        std::cout << "|                                                           \n";
        maxTrains = graph.optimalCostTrains(sourceStation, destinyStation);

        if(maxTrains == -1){
            std::cout << "| Error: Invalid source station name\n";
            std::cout << "|                                                           \n";
            return;
        }

        if(maxTrains == -2){
            std::cout << "| Error: Invalid destiny station name\n";
            std::cout << "|                                                           \n";
            return;
        }

        if(maxTrains == -3){
            std::cout << "| Error: Source and destiny stations are the same\n";
            std::cout << "|                                                           \n";
            return;
        }

        if(maxTrains == 0){
            std::cout << "| Error: No railway between source and destiny stations\n";
            std::cout << "|                                                           \n";
            return;
        }

        std::cout << "| Minimum price for max trains between " << sourceStation << " and " << destinyStation << ": " << maxTrains << "\n";
        std::cout << "|                                                           \n";
        checkStay(option1Stay, "Operation Cost Optimization");
    }
}