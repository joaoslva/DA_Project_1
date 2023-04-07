//
// Created by Joao on 4/1/2023.
//

#include "Menu.h"
#include "Service_Metrics.h"
#include "Operation_Cost_optimization.h"
#include "Line_Reliability.h"

Menu::Menu(const Graph &graph, const Graph &directedGraph): graph(graph), directedGraph(directedGraph) {}

void Menu::start(){
    bool running = true;
    //Create a dope print saying "Train Management App" with characters

    std::cout << "\n|-----------------------------------------------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Welcome to the Train Management App. This app is designed |\n";
    std::cout << "| to help the company make decisions regarding the railway  |\n";
    std::cout << "| network operation. Use the Help section to have a glance  |\n";
    std::cout << "| of how each section and functionality works.              |\n";
    std::cout << "|                                                           |\n";
    std::cout << "|-----------------------------------------------------------|\n";
    std::cout << "|                                                           |\n";

    while (running){
        std::string choice;
        std::cout << "| - MAIN MENU -                                             |\n";
        std::cout << "|                                                           |\n";
        std::cout << "| 1 - Service Metrics                                       |\n";
        std::cout << "| 2 - Operation Cost Optimization                           |\n";
        std::cout << "| 3 - Line Reliability                                      |\n";
        std::cout << "| 4 - Help                                                  |\n";
        std::cout << "| q - Quit the program                                      |\n";
        std::cout << "|                                                           |\n";
        std::cout << "| Enter here your choice: ";
        std::getline(std::cin, choice);
        std::cout << "|                                                           |\n";

        if(choice == "1") {
            Service_Metrics serviceMetrics = Service_Metrics(graph, directedGraph);
            running = serviceMetrics.start();
        }
        else if(choice == "2"){
            Operation_Cost_optimization serviceMetrics = Operation_Cost_optimization(graph, directedGraph);
            running = serviceMetrics.start();
        }

        else if(choice == "3"){
            Line_Reliability lineReliability = Line_Reliability(graph, directedGraph);
            running = lineReliability.start();
        }

        else if(choice == "4")
            help();

        else if(choice == "q"){
            quitMessage();
            running = false;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
        }
    }
}

void Menu::help() {
    std::string helpChoice;

    std::cout << "|------------------------Help Page--------------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| How each section works                                    |\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Service Metrics: This sections is designed to analyze     |\n";
    std::cout << "|   the number of trains that can be operated in various    |\n";
    std::cout << "|   scenarios, so that the company can make decisions       |\n";
    std::cout << "|   regarding the number of trains that should be bought.   |\n";
    std::cout << "| Operation Cost Optimization: This section is designed to  |\n";
    std::cout << "|   analyze the cost of operating different trains, so      |\n";
    std::cout << "|   that the company can make decisions regarding the       |\n";
    std::cout << "|   allocation of resources to minimize costs.              |\n";
    std::cout << "| Line Reliability: This section is designed to help the    |\n";
    std::cout << "|   company accessing the sensitivity of some segments of   |\n";
    std::cout << "|   the line to failures due to maintenance, disasters,     |\n";
    std::cout << "|   etc., so that the company can make decisions regarding  |\n";
    std::cout << "|   the network's reliability.                              |\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Write 'back' to go to the previous page                   |\n";
    std::cout << "| Enter here: ";

    while (true) {
        std::getline(std::cin,helpChoice);
        std::cout << "|                                                           |\n";

        if (helpChoice == "back") {
            std::cout << "|-----------------------------------------------------------|\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Select one of the options below to get started.           |\n";
            std::cout << "|                                                           |\n";
            break;
        } else {
            std::cout << "| Not a valid input, please try again                       |\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Enter here: ";
        }
    }
}

void Menu::checkStay(bool& condition, const std::string& previousChoice){
    std::string checkChoice;
    while(true){
        std::cout << "| Do you wish to use this functionality again or go back?   |\n";
        std::cout << "| Write 'stay' to use it again, 'back' to go back           |\n";
        std::cout << "|                                                           |\n";
        std::cout << "| Enter here: ";
        std::getline(std::cin, checkChoice);
        std::cout << "|                                                           |\n";

        if(checkChoice == "stay"){
            break;
        }
        else if(previousChoice == "Operation Cost Optimization" && checkChoice == "back"){
            condition = false;
            std::cout << "|-----------------------------------------------------------|\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Select one of the Operation Cost Optimization options     |\n";
            std::cout << "| bellow to get started                                     |\n";
            break;
        }
        else if(previousChoice != "Operation Cost Optimization" && checkChoice == "back"){
            condition = false;
            std::cout << "|-----------------------------------------------------------|\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Select one of the " + previousChoice + " options below";
            for(int i = 0; i < 59 - 33 - previousChoice.size(); i++) std::cout << " ";
            std::cout << "|\n";
            break;
        }

        else{
            std::cout << "| Not a valid input, please try again                       |\n";
            std::cout << "|                                                           |\n";
        }
    }
}

void Menu::returnMessage() {
    std::cout << "|                                                           |\n";
    std::cout << "|-----------------------------------------------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Select one of the options below to get started.           |\n";
    std::cout << "|                                                           |\n";
}

void Menu::quitMessage() {
    std::cout << "|                                                           |\n";
    std::cout << "|-----------------------------------------------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Thank you for using our program, have a nice day!         |\n";
    std::cout << "|                                                           |\n";
    std::cout << "|-----------------------------------------------------------|\n";
}