//
// Created by Joao on 4/1/2023.
//

#include "Operation_Cost_optimization.h"

Operation_Cost_optimization::Operation_Cost_optimization(const Graph &graph): Menu(graph) {}

bool Operation_Cost_optimization::start() {
    std::cout << "|-----------------------------------------------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Welcome to Operation Cost Optimization. Select one of the |\n";
    std::cout << "| options below to get started.                             |\n";
    std::cout << "|                                                           |\n";
    std::cout << "| - OPERATION COST OPTIMIZATION MENU -                      |\n";

    while (true){
        std::string operationCostOptimizationChoice;
        std::cout << "|                                                           |\n";
        std::cout << "| 1 - Maximum Number of Trains between A a B with optimal   |\n";
        std::cout << "|     cost                                                  |\n";
        std::cout << "| 2 - Help                                                  |\n";
        std::cout << "| r - Return to previous Menu                               |\n";
        std::cout << "| q - Quit application                                      |\n";
        std::cout << "|                                                           |\n";
        std::cout << "| Enter here your choice: ";
        std::getline(std::cin, operationCostOptimizationChoice);
        std::cout << "|                                                           |\n";

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
            std::cout << "| Not a valid input, please try again                       |\n";
            std::cout << "| Select on of the following options                        |\n";
        }
    }
}

void Operation_Cost_optimization::help() {
    std::string helpChoice;

    std::cout << "|------------------------Help Page--------------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| How each option works                                     |\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Maximum Number of Trains between A a B with optimal cost: |\n";
    std::cout << "|   Given two train stations, this option will return the   |\n";
    std::cout << "|   maximum number of trains that can travel between them   |\n";
    std::cout << "|   at the same time, taking in account the train type and  |\n";
    std::cout << "|   respective cost of operation.                           |\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Write 'back' to go to the previous page                   |\n";
    std::cout << "| Enter here: ";

    while(true){
        std::getline(std::cin, helpChoice);
        std::cout << "|                                                           |\n";

        if(helpChoice == "back"){
            std::cout << "|-----------------------------------------------------------|\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Select one of the Operation Cost Optimization options     |\n";
            break;
        }

        else{
            std::cout << "| Not a valid input, please try again                       |\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Enter here: ";
        }
    }
}

void Operation_Cost_optimization::optimalCost(){
    bool option1Stay = true;
    double maxTrains;
    std::string sourceStation, destinyStation;
    std::cout << "| Welcome to Maximum Number of Trains between stations      |\n";
    std::cout << "| A and B with optimal cost.                                |\n";
    std::cout << "|                                                           |\n";
    while(option1Stay){
        std::cout << "| Enter the source station: ";
        std::getline(std::cin, sourceStation);
        std::cout << "| Enter the destiny station: ";
        std::getline(std::cin, destinyStation);
        std::cout << "|                                                           |\n";
        maxTrains = graph.optimalCostTrains(sourceStation, destinyStation);

        if(maxTrains == -1){
            std::cout << "| Error: Invalid source station name                        |\n";
            std::cout << "|                                                           |\n";
            checkStay(option1Stay, "Operation Cost Optimization");
        }

        else if(maxTrains == -2){
            std::cout << "| Error: Invalid destiny station name                       |\n";
            std::cout << "|                                                           |\n";
            checkStay(option1Stay, "Operation Cost Optimization");
        }

        else if(maxTrains == -3){
            std::cout << "| Error: Source and destiny stations are the same           |\n";
            std::cout << "|                                                           |\n";
            checkStay(option1Stay, "Operation Cost Optimization");
        }

        else if(maxTrains == 0){
            std::cout << "| Error: No railway between source and destiny stations     |\n";
            std::cout << "|                                                           |\n";
            checkStay(option1Stay, "Operation Cost Optimization");
        }
        else {
            std::cout << "| Source Station: " << sourceStation;
            for(int i = 0; i < 59 - sourceStation.length() - 17; i++){
                std::cout << " ";
            }
            std::cout << "|\n";
            std::cout << "| Destiny Station: " << destinyStation;
            for(int i = 0; i < 59 - destinyStation.length() - 18; i++){
                std::cout << " ";
            }
            std::cout << "|\n";
            std::cout<< "| The total cost of operation is: " << maxTrains << "€";
            for(int i = 0; i < 59 - 34 - (maxTrains >= 10 ? (maxTrains >= 100 ? 3 : 2) : 1); i++){
                std::cout << " ";
            }
            std::cout << "|\n";
            std::cout << "|                                                           |\n";
            checkStay(option1Stay, "Operation Cost Optimization");
        }
    }
}