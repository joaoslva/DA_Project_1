//
// Created by Joao on 4/1/2023.
//

#include "Service_Metrics.h"

Service_Metrics::Service_Metrics(const Graph &graph, const Graph &directedGraph): Menu(graph, directedGraph) {}

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
            pairsWithMostTrains();
        }

        else if(serviceMetricsChoice == "3"){
            upTheBudget();
        }

        else if(serviceMetricsChoice == "4"){
            arrrivingTrains();
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

        std::cout << "| Maximum number of trains between " << sourceStation << " and " << destinyStation << ": " << maxTrains << "\n";
        std::cout << "|                                                           \n";
        checkStay(option1Stay, "Service Metrics");
    }
}

void Service_Metrics::pairsWithMostTrains() {
    std::cout << "| Welcome to Pair of Station with more trains, at top capacity  \n|\n";
    std::vector<std::pair<std::pair<std::string, std::string>, double>> pairs;
    pairs = graph.pairsWithMostTrains();
    pairs.pop_back();
    if(pairs.size() == 1){
        std::cout << "| The pair of stations with the most trains at the same time is: " << pairs[0].first.first << " and " << pairs[0].first.second << "\n";
    }
    else{
        std::cout << "| There are " << pairs.size() << " pairs of stations with the most trains at the same time: \n";
        for(int i = 1; i <= pairs.size(); i++){
            std::cout << "| Pair nº " << i << ": " << pairs[i].first.first << " and " << pairs[i].first.second << ", with " << pairs[i].second << " trains;" <<"\n";
        }
    }
    std::cout << "|                                                           \n";
}

void Service_Metrics::upTheBudget() {
    bool option3Stay = true;
    int option;
    std::cout << "| Welcome to Locations to up the budget  \n|\n";
    while(option3Stay){
        std::cout << "| Please, choose on of the following options: \n";
        std::cout << "|\n";
        std::cout << "| 1 - See the top-k districts where the budget should be increased \n";
        std::cout << "| 2 - See the top-k municipalities where the budget should be increased \n";
        std::cout << "|\n";
        std::cout << "| Enter here: ";
        std::cin >> option;
        std::cout << "|                                                           \n";
        if(option == 1){
            int i;
            std::cout << "| Please, enter the number of districts you want to see: ";
            std::cin >> i;
            std::cout << "|                                                           \n";
            if(std::cin.eof()) {
                std::cout << "| Not a valid input, please try again                      \n";
                std::cout << "|                                                          \n";
                i = 0;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else{
                std::vector<std::pair<std::pair<std::string, std::string>, double>> values;
                values = directedGraph.largerBudgets();
                std::map<std::string, double> valuesMap;
                for(auto element : values){
                    valuesMap[element.first.first] += element.second;
                }
                std::vector<std::pair<std::string, double>> valuesVector;
                for(auto element : valuesMap){
                    valuesVector.push_back(element);
                }
                std::sort(valuesVector.begin(), valuesVector.end(), [](std::pair<std::string, double> a, std::pair<std::string, double> b){
                    return a.second > b.second;
                });
                std::cout << "| The top " << i << " districts where the budget should be increased are: \n";
                for(int j = 0; j<i; j++){
                    std::cout << "| District nº " << j+1 << ": " << valuesVector[j].first << ", since it has " << valuesVector[j].second << " trains flowing at maximum capacity;" <<"\n";
                }
            }
            std::cout << "|                                                           \n";
            checkStay(option3Stay, "Service Metrics");
        }
        else if(option == 2){
            int i;
            std::cout << "| Please, enter the number of municipalities you want to see: ";
            std::cin >> i;
            std::cout << "|                                                           \n";
            if(std::cin.eof()) {
                std::cout << "| Not a valid input, please try again                      \n";
                std::cout << "|                                                          \n";
                i = 0;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else{
                std::vector<std::pair<std::pair<std::string, std::string>, double>> values;
                values = directedGraph.largerBudgets();
                std::map<std::pair<std::string, std::string>, double> valuesMap;
                for(auto element : values){
                    valuesMap[element.first] += element.second;
                }
                std::vector<std::pair<std::pair<std::string, std::string>, double>> valuesVector;
                for(auto element : valuesMap){
                    valuesVector.push_back(element);
                }

                std::sort(valuesVector.begin(), valuesVector.end(), [](std::pair<std::pair<std::string, std::string>, double> a, std::pair<std::pair<std::string, std::string>, double> b){
                    return a.second > b.second;
                });
                std::cout << "| The top " << i << " municipalities where the budget should be increased are: \n";
                int j = 0;
                for(auto element : valuesVector){
                    if(element.first.first != ""){
                        std::cout << "| Municipality nº " << ++j << ": " << element.first.second << ", in district " << element.first.first << ", since it has " << element.second << " trains flowing at maximum capacity;" <<"\n";
                    }
                    if(j == i){
                        break;
                    }
                }
            }
            std::cout << "|                                                           \n";
            checkStay(option3Stay, "Service Metrics");
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            option = 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Service_Metrics::arrrivingTrains() {
    bool option4Stay = true;
    std::string station;
    double result;
    std::cout << "| Welcome to Arriving Trains  \n|\n";
    while(option4Stay) {
        std::cout << "| Please, write a station name: ";
        std::cin >> station;
        std::cout << "|                                                           \n";
        result = directedGraph.arrivingTrains(station);
        if(result == -2){
            std::cout << "| The station " << station << " does not exist. \n";
        }
        else{
            std::cout << "| The station " << station << " has " << result << " trains arriving, taking into account the whole grid. \n";
        }
        std::cout << "|                                                           \n";
        checkStay(option4Stay, "Service Metrics");
    }
}