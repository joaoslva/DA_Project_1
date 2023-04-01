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
        std::string choice;
        std::cout << "| 1 - Service Metrics                                      \n";
        std::cout << "| 2 - Operation Cost Optimization                          \n";
        std::cout << "| 3 - Line Reliability                                     \n";
        std::cout << "| 4 - Help                                                 \n";
        std::cout << "| q - Quit the program                                     \n";
        std::cout << "|                                                          \n";
        std::cout << "| Enter here your choice: ";
        std::cin >> choice;
        std::cout << "|                                                          \n";

        if(choice == "1") {
            Service_Metrics serviceMetrics = Service_Metrics(graph);
            running = serviceMetrics.start();
        }
        else if(choice == "2"){
            Operation_Cost_optimization serviceMetrics = Operation_Cost_optimization(graph);
            running = serviceMetrics.start();
        }

        else if(choice == "3"){
            Line_Reliability lineReliability = Line_Reliability(graph);
            running = lineReliability.start();
        }

        else if(choice == "4"){
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

        else if(choice == "q"){
            std::cout << "| Thank you for using our program, have a nice day!         \n";
            std::cout << "|---------------------------------------------------------- \n";
            running = false;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}