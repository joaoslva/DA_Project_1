//
// Created by Joao on 4/1/2023.
//

#include "Menu.h"
#include "Service_Metrics.h"
#include "Operation_Cost_optimization.h"
#include "Line_Reliability.h"

Menu::Menu(const Graph &graph): graph(graph) {}

void Menu::checkStay(bool& condition, const std::string& previousChoice){
    std::string checkChoice;
    while(true){
        std::cout << "| Do you wish to use this functionality again or go back?  \n";
        std::cout << "| Write 'stay' to use it again, 'back' to go back          \n";
        std::cout << "|                                                          \n";
        std::cout << "| Enter here: ";
        std::cin >> checkChoice;
        std::cout << "|                                                          \n";

        if(checkChoice == "stay"){
            break;
        }

        else if(checkChoice == "back"){
            condition = false;
            std::cout << " ----------------------------------------------------------\n";
            std::cout << "|                                                          \n";
            std::cout << "| Select one of the " + previousChoice + " options below   \n";
            break;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            checkChoice = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Menu::start(){
    bool running = true;
    //Create a dope print saying "Train Management App" with characters

    std::cout << "|---------------------------------------------------------- \n";
    std::cout << "|                                                           \n";
    std::cout << "| Welcome to the Train Management App. Select one of the    \n";
    std::cout << "| options below to get started.                             \n";
    std::cout << "|                                                           \n";

    while (running){
        int choice = 0;
        std::cout << "| 1 - Service Metrics                                      \n";
        std::cout << "| 2 - Operation Cost Optimization                          \n";
        std::cout << "| 3 - Line Reliability                                     \n";
        std::cout << "| 4 - Help                                                 \n";
        std::cout << "| 5 - Quit the program                                     \n";
        std::cout << "|                                                          \n";
        std::cout << "| Enter here your choice: ";
        std::cin >> choice;
        std::cout << "|                                                          \n";

        if(choice == 1) {
            Service_Metrics serviceMetrics = Service_Metrics(graph);
            running = serviceMetrics.start();
        }
        else if(choice == 2){
            Operation_Cost_optimization serviceMetrics = Operation_Cost_optimization(graph);
            running = serviceMetrics.start();
            std::cout << "|---------------------------------------------------------- \n";
            std::cout << "|                                                           \n";
            std::cout << "| Welcome to Operation Cost Optimization. Select one of the \n";
            std::cout << "| options below to get started.                             \n";

            bool operationCostOptimizationStay = true;

            while (operationCostOptimizationStay){
                int operationCostOptimizationChoice = 0;
                std::cout << "|                                                           \n";
                std::cout << "| 1 - Maximum Number of Trains between A a B with optimal   \n";
                std::cout << "|     cost                                                  \n";
                std::cout << "| 2 - Help                                                  \n";
                std::cout << "| 3 - Go back                                               \n";
                std::cout << "|                                                           \n";
                std::cout << "| Enter here your choice: ";
                std::cin >> operationCostOptimizationChoice;
                std::cout << "|                                                           \n";

                if(operationCostOptimizationChoice == 1){
                    bool option1Stay = true;
                    while(option1Stay){
                        std::cout << "| Option 1 selected \n";
                        checkStay(option1Stay, "Operation Cost Optimization");
                    }
                }

                else if(operationCostOptimizationChoice == 2){
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

                else if(operationCostOptimizationChoice == 3){
                    operationCostOptimizationStay = false;
                    std::cout << "|                                                           \n";
                    std::cout << "|---------------------------------------------------------- \n";
                    std::cout << "|                                                           \n";
                    std::cout << "| Select one of the options below to get started.           \n";
                    std::cout << "|                                                           \n";
                }

                else{
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "| Select on of the following options                       \n";
                    operationCostOptimizationChoice = 0;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }

        else if(choice == 3){
            std::cout << "|---------------------------------------------------------- \n";
            std::cout << "|                                                           \n";
            std::cout << "| Welcome to Line Reliability. Select one of the options    \n";
            std::cout << "| below to get started.                                     \n";

            bool lineReliabilityStay = true;

            while (lineReliabilityStay) {
                int lineReliabilityChoice = 0;
                std::cout << "|                                                           \n";
                std::cout << "| 1 - Maximum Number of Trains between A a B, taking into   \n";
                std::cout << "|     account reduced connectivity                          \n";
                std::cout << "| 2 - Stations more affected by segment failure             \n";
                std::cout << "| 3 - Help                                                  \n";
                std::cout << "| 4 - Go back                                               \n";
                std::cout << "|                                                           \n";
                std::cout << "| Enter here your choice: ";
                std::cin >> lineReliabilityChoice;
                std::cout << "|                                                           \n";

                if(lineReliabilityChoice == 1){
                    bool option1Stay = true;
                    while(option1Stay){
                        std::cout << "Option 1 selected \n";
                        checkStay(option1Stay, "Line Reliability");
                    }
                }

                else if(lineReliabilityChoice == 2){
                    bool option2Stay = true;
                    while(option2Stay){
                        std::cout << "Option 2 selected \n";
                        checkStay(option2Stay, "Line Reliability");
                    }
                }

                else if(lineReliabilityChoice == 3) {
                    std::string helpChoice;

                    std::cout << "|------------------------Help Page-------------------------\n";
                    std::cout << "|                                                          \n";
                    std::cout << "| How each option works                                    \n";
                    std::cout << "|                                                          \n";
                    std::cout << "| Maximum Number of Trains between A a B, taking into      \n";
                    std::cout << "|   account reduced connectivity: Given two train stations,\n";
                    std::cout << "|   this option will return the maximum number of trains   \n";
                    std::cout << "|   that can travel between them at the same time, taking  \n";
                    std::cout << "|   in account a reduced connectivity version of the       \n";
                    std::cout << "|   network.                                               \n";
                    std::cout << "|                                                          \n";
                    std::cout << "| Stations more affected by segment failure: Given a       \n";
                    std::cout << "|   segment of the line, this option will return the       \n";
                    std::cout << "|   stations that are more affected by the segment failure.\n";
                    std::cout << "|                                                          \n";
                    std::cout << "| Write 'back' to go to the previous page                  \n";
                    std::cout << "| Enter here: ";

                    while (true) {
                        std::cin >> helpChoice;
                        std::cout << "|                                                          \n";

                        if (helpChoice == "back") {
                            std::cout << "|----------------------------------------------------------\n";
                            std::cout << "|                                                          \n";
                            std::cout << "| Select one of the Line Reliability options below          \n";
                            break;
                        } else {
                            std::cout << "| Not a valid input, please try again                      \n";
                            std::cout << "|                                                          \n";
                        }
                    }
                }

                else if(lineReliabilityChoice == 4){
                    lineReliabilityStay = false;
                    std::cout << "|                                                           \n";
                    std::cout << "|---------------------------------------------------------- \n";
                    std::cout << "|                                                           \n";
                    std::cout << "| Select one of the options below to get started.           \n";
                    std::cout << "|                                                           \n";
                }

                else{
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "| Select on of the following options                       \n";
                    lineReliabilityChoice = 0;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }

        else if(choice == 4){
            std::string helpChoice;

            std::cout << "|------------------------Help Page-------------------------\n";
            std::cout << "|                                                          \n";
            std::cout << "| How each section works                                   \n";
            std::cout << "|                                                          \n";
            std::cout << "| Service Metrics: This sections is designed to analyze    \n";
            std::cout << "|   the number of trains that can be operated in various   \n";
            std::cout << "|   scenarios, so that the company can make decisions      \n";
            std::cout << "|   regarding the number of trains that should be bought.  \n";
            std::cout << "| Operation Cost Optimization: This section is designed to \n";
            std::cout << "|   analyze the cost of operating different trains, so     \n";
            std::cout << "|   that the company can make decisions regarding the      \n";
            std::cout << "|   allocation of resources to minimize costs.             \n";
            std::cout << "| Line Reliability: This section is designed to help the   \n";
            std::cout << "|   company accessing the sensitivity of some segments of  \n";
            std::cout << "|   the line to failures due to maintenance, disasters,    \n";
            std::cout << "|   etc., so that the company can make decisions regarding \n";
            std::cout << "|   the network's reliability.                             \n";
            std::cout << "|                                                          \n";
            std::cout << "| Write 'back' to go to the previous page                  \n";
            std::cout << "| Enter here: ";

            while (true) {
                std::cin >> helpChoice;
                std::cout << "|                                                          \n";

                if (helpChoice == "back") {
                    std::cout << "|----------------------------------------------------------\n";
                    std::cout << "|                                                          \n";
                    std::cout << "| Select one of the options below to get started.          \n";
                    std::cout << "|                                                          \n";
                    break;
                } else {
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "|                                                          \n";
                }
            }
        }

        else if(choice == 5){
            std::cout << "| Thank you for using our program, have a nice day!        \n";
            std::cout << "|---------------------------------------------------------- \n";
            running = false;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            choice = 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}