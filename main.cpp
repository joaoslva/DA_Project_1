#include <iostream>
#include <limits>
#include <vector>
#include "CsvReader.h"
#include "Graph.h"

void checkStay(bool& condition, const std::string& previousChoice){
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

int main() {
    //Setting up the graph
    Graph graph;

    std::vector<Station> stations = CsvReader::readStations("../dataset/stations.csv");
    std::vector<Railway> railways= CsvReader::readNetwork("../dataset/network.csv");

    if(stations.empty()){
        std::cout << "Error reading stations file" << std::endl;
        return 1;
    }

    if(railways.empty()){
        std::cout << "Error reading network file" << std::endl;
        return 1;
    }

    for(const Station& station:stations){
        if(!graph.addStation(station)){
            std::cout << "Error adding station " << station.getName() << std::endl;
        }
    }

    for(const Railway& railway:railways){
        if(!graph.addBidirectionalRailway(railway.getSourceStationString(), railway.getDestinyStationString(), railway)){
            std::cout << "Error adding railway " << railway.getSourceStationString() << " -> " << railway.getDestinyStationString() << std::endl;
        }
    }

    //----------------------------------------------------

    for(auto station: graph.getStations()){
        std::cout << "|--------------------\n";
        std::cout << "Station name: " << station->getName() << std::endl;
        for(auto railway: station->getOutgoingRailways()){
            std::cout << "  Destination: " << railway->getDestinyStationPointer()->getName() << ", Capacity: " << railway->getCapacity() << ", Service: " << railway->getService() << std::endl;
        }
    }

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

        if(choice == 1){
            std::cout << "|---------------------------------------------------------- \n";
            std::cout << "|                                                           \n";
            std::cout << "| Welcome to Service Metrics. Select one of the options     \n";
            std::cout << "| below to get started.                                     \n";

            bool serviceMetricsStay = true;

            while (serviceMetricsStay){
                int serviceMetricsChoice = 0;
                std::cout << "|                                                           \n";
                std::cout << "| 1 - Maximum Number of Trains between stations A and B     \n";
                std::cout << "| 2 - Pair of Station with more trains, at top capacity     \n";
                std::cout << "| 3 - Locations to up the budget                            \n";
                std::cout << "| 4 - Maximum Number of Trains that arrive at a station     \n";
                std::cout << "| 5 - Help                                                  \n";
                std::cout << "| 6 - Go back                                               \n";
                std::cout << "|                                                           \n";
                std::cout << "| Enter here your choice: ";
                std::cin >> serviceMetricsChoice;
                std::cout << "|                                                           \n";

                if(serviceMetricsChoice == 1){
                    bool option1Stay = true;
                    double maxTrains = 0;
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

                else if(serviceMetricsChoice == 2){
                    bool option2Stay = true;
                    while(option2Stay){
                        std::cout << "| Option 2 selected \n";
                        checkStay(option2Stay, "Service Metrics");
                    }
                }

                else if(serviceMetricsChoice == 3){
                    bool option3Stay = true;
                    while(option3Stay){
                        std::cout << "| Option 3 selected \n";
                        checkStay(option3Stay, "Service Metrics");
                    }
                }

                else if(serviceMetricsChoice == 4){
                    bool option4Stay = true;
                    while(option4Stay){
                        std::cout << "| Option 4 selected \n";
                        checkStay(option4Stay, "Service Metrics");
                    }
                }

                else if(serviceMetricsChoice == 5){
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

                else if(serviceMetricsChoice == 6){
                    serviceMetricsStay = false;
                    std::cout << "|                                                           \n";
                    std::cout << "|---------------------------------------------------------- \n";
                    std::cout << "|                                                           \n";
                    std::cout << "| Select one of the options below to get started.           \n";
                    std::cout << "|                                                           \n";
                }

                else{
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "| Select on of the following options                       \n";
                    serviceMetricsChoice = 0;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }

        else if(choice == 2){
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
    return 0;
}
