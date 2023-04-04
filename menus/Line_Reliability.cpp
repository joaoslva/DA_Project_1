//
// Created by Joao on 4/1/2023.
//

#include "Line_Reliability.h"
Line_Reliability::Line_Reliability(const Graph &graph, const Graph &directedGraph): Menu(graph, directedGraph) {}

bool Line_Reliability::start() {
    std::cout << "|---------------------------------------------------------- \n";
    std::cout << "|                                                           \n";
    std::cout << "| Welcome to Line Reliability. Select one of the options    \n";
    std::cout << "| below to get started.                                     \n";
    std::cout << "|                                                           \n";

    while (true) {
        std::string lineReliabilityChoice;
        std::cout << "### LINE RELIABILITY MENU ###                               \n";
        std::cout << "|                                                           \n";
        std::cout << "| 1 - Maximum Number of Trains between A a B, taking into   \n";
        std::cout << "|     account reduced connectivity                          \n";
        std::cout << "| 2 - Stations more affected by segment failure             \n";
        std::cout << "| 3 - Help                                                  \n";
        std::cout << "| r - Return to previous Menu                               \n";
        std::cout << "| q - Quit application                                      \n";
        std::cout << "|                                                           \n";
        std::cout << "| Enter here your choice: ";
        std::getline(std::cin, lineReliabilityChoice);
        std::cout << "|                                                           \n";

        if(lineReliabilityChoice == "1"){
            bool option1Stay = true;
            while(option1Stay){
                std::cout << "Option 1 selected \n";
                checkStay(option1Stay, "Line Reliability");
            }
        }

        else if(lineReliabilityChoice == "2"){
            bool option2Stay = true;
            while(option2Stay){
                std::cout << "Option 2 selected \n";
                checkStay(option2Stay, "Line Reliability");
            }
        }

        else if(lineReliabilityChoice == "3")
            help();

        else if(lineReliabilityChoice == "r"){
            returnMessage();
            return true;
        }
        else if(lineReliabilityChoice == "q"){
            quitMessage();
            return false;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "| Select on of the following options                       \n";
        }
    }
}

void Line_Reliability::help() {
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
        std::getline(std::cin, helpChoice);
        std::cout << "|                                                          \n";

        if (helpChoice == "back") {
            std::cout << "|----------------------------------------------------------\n";
            std::cout << "|                                                          \n";
            std::cout << "| Select one of the Line Reliability options below          \n";
            break;
        } else {
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            std::cout << "| Enter here: ";
        }
    }
}