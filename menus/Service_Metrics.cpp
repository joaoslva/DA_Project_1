//
// Created by Joao on 4/1/2023.
//

#include "Service_Metrics.h"

Service_Metrics::Service_Metrics(const Graph &graph): Menu(graph) {}

bool Service_Metrics::start() {
    std::cout << "|---------------------------------------------------------- \n";
    std::cout << "|                                                           \n";
    std::cout << "| Welcome to Service Metrics. Select one of the options     \n";
    std::cout << "| below to get started.                                     \n";
    std::cout << "|                                                           \n";

    while (true){
        std::string serviceMetricsChoice;
        std::cout << "### SERVICE METRICS MENU ###                                \n";
        std::cout << "|                                                           \n";
        std::cout << "| 1 - Maximum Number of Trains between stations A and B     \n";
        std::cout << "| 2 - Pair of Station with more trains, at top capacity     \n";
        std::cout << "| 3 - Locations to up the budget                            \n";
        std::cout << "| 4 - Maximum Number of Trains that arrive at a station     \n";
        std::cout << "| 5 - Help                                                  \n";
        std::cout << "| r - Return to previous Menu                               \n";
        std::cout << "| q - Quit application                                      \n";
        std::cout << "|                                                           \n";
        std::cout << "| Enter here your choice: ";
        std::cin >> serviceMetricsChoice;
        std::cout << "|                                                           \n";

        if(serviceMetricsChoice == "1"){
            maxTrainsAB();
        }

        else if(serviceMetricsChoice == "2"){
            bool option2Stay = true;
            while(option2Stay){
                std::cout << "| Option 2 selected \n";
                checkStay(option2Stay, "Service Metrics");
            }
        }

        else if(serviceMetricsChoice == "3"){
            bool option3Stay = true;
            while(option3Stay){
                std::cout << "| Option 3 selected \n";
                checkStay(option3Stay, "Service Metrics");
            }
        }

        else if(serviceMetricsChoice == "4"){
            bool option4Stay = true;
            while(option4Stay){
                std::cout << "| Option 4 selected \n";
                checkStay(option4Stay, "Service Metrics");
            }
        }

        else if(serviceMetricsChoice == "5")
            help();


        else if(serviceMetricsChoice == "r"){
            returnMessage();
            return true;
        }

        else if(serviceMetricsChoice == "q"){
            quitMessage();
            return false;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "| Select on of the following options                       \n";
            serviceMetricsChoice = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Service_Metrics::help() {
    std::string helpChoice;

    std::cout << "|------------------------Help Page-------------------------\n";
    std::cout << "|                                                          \n";
    std::cout << "| How each option works                                    \n";
    std::cout << "|                                                          \n";
    std::cout << "| Maximum NUmber of Trains between A and B: Given two train\n";
    std::cout << "|   stations, this option will return the maximum number of\n";
    std::cout << "|   trains that can be in between them at the same time.   \n";
    std::cout << "| Pair of Station with more trains, at top capacity: This  \n";
    std::cout << "|   option will return the pair of stations that have the  \n";
    std::cout << "|   most trains at the same time, when the network is at   \n";
    std::cout << "|   top capacity.                                          \n";
    std::cout << "| Locations to up the budget: This functionality, upon     \n";
    std::cout << "|   receiving an integer k, will return the k locations,   \n";
    std::cout << "|   districts or municipalities, that should have their    \n";
    std::cout << "|   budget increased in order to improve their performance \n";
    std::cout << "| Maximum Number of Trains that arrive at a station: This  \n";
    std::cout << "|   option will return the maximum number of trains that   \n";
    std::cout << "|   can arrive at a given station at the same time.        \n";
    std::cout << "|                                                          \n";
    std::cout << "| Write 'back' to go to the previous page                  \n";
    std::cout << "| Enter here: ";

    while(true){
        std::cin >> helpChoice;
        std::cout << "|                                                          \n";

        if(helpChoice == "back"){
            std::cout << " ---------------------------------------------------------- \n";
            std::cout << "|                                                          \n";
            std::cout << "| Select one of the Service Metrics options below          \n";
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

void Service_Metrics::maxTrainsAB() {
    bool option1Stay = true;
    double maxTrains;
    std::string sourceStation, destinyStation;
    std::cout << "| Welcome to Maximum Number of Trains between stations A and B  \n|\n";
    while(option1Stay){
        std::cout << "| Enter the source station: ";
        std::cin >> sourceStation;
        std::cout << "| Enter the destiny station: ";
        std::cin >> destinyStation;
        std::cout << "|                                                           \n";
        maxTrains = graph.getTrainsBetweenStations(sourceStation, destinyStation);

        if(maxTrains == -1){
            std::cout << "| Error: Invalid source station name\n";
        }

        if(maxTrains == -2){
            std::cout << "| Error: Invalid destiny station name\n";
        }

        if(maxTrains == -3){
            std::cout << "| Error: Source and destiny stations are the same\n";
        }

        if(maxTrains == 0){
            std::cout << "| Error: No railway between source and destiny stations\n";
        }

        std::cout << "| Maximum number of trains between " << sourceStation << " and " << destinyStation << ": " << maxTrains << "\n";
        std::cout << "|                                                           \n";
        checkStay(option1Stay, "Service Metrics");
    }
}