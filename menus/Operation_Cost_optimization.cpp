//
// Created by Joao on 4/1/2023.
//

#include "Operation_Cost_optimization.h"

Operation_Cost_optimization::Operation_Cost_optimization(const Graph &graph): Menu(graph) {}

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
        std::cin >> operationCostOptimizationChoice;
        std::cout << "|                                                           \n";

        if(operationCostOptimizationChoice == "1"){
            bool option1Stay = true;
            while(option1Stay){
                std::cout << "| Option 1 selected \n";
                checkStay(option1Stay, "Operation Cost Optimization");
            }
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
            operationCostOptimizationChoice = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        std::cin >> helpChoice;
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
            helpChoice = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}