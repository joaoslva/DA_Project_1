//
// Created by Joao on 4/1/2023.
//

#include "Line_Reliability.h"
Line_Reliability::Line_Reliability(const Graph &graph, const Graph &directedGraph): Menu(graph, directedGraph) {}

bool Line_Reliability::start() {
    std::cout << "|-----------------------------------------------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| Welcome to Line Reliability. Select one of the options    |\n";
    std::cout << "| below to get started.                                     |\n";
    std::cout << "|                                                           |\n";
    std::cout << "| - LINE RELIABILITY MENU -                                 |\n";
    while (true) {
        std::string lineReliabilityChoice;
        std::cout << "|                                                           |\n";
        std::cout << "| 1 - Maximum Number of Trains between A a B, taking into   |\n";
        std::cout << "|     account reduced connectivity                          |\n";
        std::cout << "| 2 - Stations more affected by segment failure             |\n";
        std::cout << "| 3 - Help                                                  |\n";
        std::cout << "| r - Return to previous Menu                               |\n";
        std::cout << "| q - Quit application                                      |\n";
        std::cout << "|                                                           |\n";
        std::cout << "| Enter here your choice: ";
        std::getline(std::cin, lineReliabilityChoice);
        std::cout << "|                                                           |\n";

        if(lineReliabilityChoice == "1"){
            reducedMaxTrainsAB();
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
            std::cout << "| Not a valid input, please try again                        |\n";
            std::cout << "| Select on of the following options                         |\n";
        }
    }
}

void Line_Reliability::help() {
    std::string helpChoice;

    std::cout << "|------------------------Help Page---------------------------|\n";
    std::cout << "|                                                            |\n";
    std::cout << "| How each option works                                      |\n";
    std::cout << "|                                                            |\n";
    std::cout << "| Maximum Number of Trains between A a B, taking into        |\n";
    std::cout << "|   account reduced connectivity: Given two train stations,  |\n";
    std::cout << "|   this option will return the maximum number of trains     |\n";
    std::cout << "|   that can travel between them at the same time, taking    |\n";
    std::cout << "|   in account a reduced connectivity version of the         |\n";
    std::cout << "|   network.                                                 |\n";
    std::cout << "|                                                            |\n";
    std::cout << "| Stations more affected by segment failure: Given a         |\n";
    std::cout << "|   segment of the line, this option will return the         |\n";
    std::cout << "|   stations that are more affected by the segment failure.  |\n";
    std::cout << "|                                                            |\n";
    std::cout << "| Write 'back' to go to the previous page                    |\n";
    std::cout << "| Enter here: ";

    while (true) {
        std::getline(std::cin, helpChoice);
        std::cout << "|                                                            |\n";

        if (helpChoice == "back") {
            std::cout << "|-----------------------------------------------------------|\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Select one of the Line Reliability options below          |\n";
            break;
        } else {
            std::cout << "| Not a valid input, please try again                       |\n";
            std::cout << "|                                                           |\n";
            std::cout << "| Enter here: ";
        }
    }
}

void Line_Reliability::reducedMaxTrainsAB(){
    bool option1Stay = true;
    std::string option, sourceStation, destinyStation;
    std::cout << "| Welcome to Maximum Number of Trains between A a B, taking |\n";
    std::cout << "| into account reduced connectivity                         |\n";
    std::cout << "|                                                           |\n";
    while(option1Stay){
        std::cout << "| Please, enter the number corresponding to the line you    |\n";
        std::cout << "| want to assess it's reliability                           |\n";
        std::cout << "|                                                           |\n";
        std::cout << "| (type l to see the list)                                  |\n";
        std::cout << "|                                                           |\n";
        std::cout << "| Enter here: ";
        std::getline(std::cin, option);
        std::cout << "|                                                           |\n";
        if(option == "l"){
            listTrainLines();
            continue;
        }
        else{
            int num;
            try{
                num = std::stoi(option);
            } catch (const std::invalid_argument& e) {
                std::cout << "| Not a valid input, please try again                       |\n";
                std::cout << "|                                                           |\n";
                continue;
            }
            if (num<1 || num>27){
                std::cout << "| The number must be a digit between 1 and 27               |\n";
                std::cout << "|                                                           |\n";
                continue;
            }
            std::cout << "| Enter the source station: ";
            std::getline(std::cin, sourceStation);
            std::cout << "| Enter the destiny station: ";
            std::getline(std::cin, destinyStation);
            std::cout << "|                                                           \n";
            std::string line = lineSelected(num);
            Graph g = Graph(graph);
            int maxTrains = g.getTrainsBetweenStationsReduced(sourceStation, destinyStation,line);
            switch (maxTrains) {
                case 0:
                    std::cout << "| Error: No railway between source and destiny stations     |\n";
                    std::cout << "|                                                           |\n";
                    break;
                case -1:
                    std::cout << "| Error: Invalid source station name                        |\n";
                    std::cout << "|                                                           |\n";
                    break;
                case -2:
                    std::cout << "| Error: Invalid destiny station name                       |\n";
                    std::cout << "|                                                           |\n";
                    break;
                case -3:
                    std::cout << "| Error: Source and destiny stations are the same           |\n";
                    std::cout << "|                                                           |\n";
                    break;
                case -4:
                    std::cout << "| Error: Source and destiny stations belong to line chosen  |\n";
                    std::cout << "|                                                           |\n";
                    break;
                case -5:
                    std::cout << "| Error: Source station belongs to line chosen              |\n";
                    std::cout << "|                                                           |\n";
                    break;
                case -6:
                    std::cout << "| Error: Destiny station belongs to line chosen             |\n";
                    std::cout << "|                                                           |\n";
                    break;
                default:
                    std::cout << "| Itinerary: " << sourceStation << " -> " << destinyStation;
                    for(int i = 0; i < 59 - sourceStation.size() - destinyStation.size() - 16; i++) std::cout << " ";
                    std::cout << "|\n";
                    std::cout << "| Maximum number of trains: " << maxTrains;
                    for(int i = 0; i < 59 - maxTrains - 26; i++) std::cout << " ";
                    std::cout << "|\n";
                    std::cout << "|                                                           |\n";
                    break;

            }
            checkStay(option1Stay, "Line Reliability");
        }
    }
}

void Line_Reliability::listTrainLines(){

    std::cout << "|-------------------Train Lines Numbers---------------------|\n";
    std::cout << "|                                                           |\n";
    std::cout << "| 1 - Linha do Norte                                        |\n";
    std::cout << "| 2 - Linha do Oeste                                        |\n";
    std::cout << "| 3 - Linha do Minho                                        |\n";
    std::cout << "| 4 - Linha do Sul                                          |\n";
    std::cout << "| 5 - Linha do Douro                                        |\n";
    std::cout << "| 6 - Linha do Vouga                                        |\n";
    std::cout << "| 7 - Linha da Beira Baixa                                  |\n";
    std::cout << "| 8 - Linha da Beira Alta                                   |\n";
    std::cout << "| 9 - Linha do Algarve                                      |\n";
    std::cout << "| 10 - Linha do Alentejo                                    |\n";
    std::cout << "| 11 - Linha de Cascais                                     |\n";
    std::cout << "| 12 - Linha de Sintra                                      |\n";
    std::cout << "| 13 - Linha do Leste                                       |\n";
    std::cout << "| 14 - Linha de Guimarães                                   |\n";
    std::cout << "| 15 - Linha de Vendas Novas                                |\n";
    std::cout << "| 16 - Ramal de Braga                                       |\n";
    std::cout << "| 17 - Linha de Cintura                                     |\n";
    std::cout << "| 18 - Ramal de Tomar                                       |\n";
    std::cout << "| 19 - Linha de Leixões                                     |\n";
    std::cout << "| 20 - Ramal de Alfarelos                                   |\n";
    std::cout << "| 21 - Linha de Sines                                       |\n";
    std::cout << "| 22 - Linha de Évora                                       |\n";
    std::cout << "| 23 - Ramal Neves Corvo                                    |\n";
    std::cout << "| 24 - Rede Espanhola                                       |\n";
    std::cout << "| 25 - Ramal da Lousã                                       |\n";
    std::cout << "| 26 - Concordância São Gemil                               |\n";
    std::cout << "| 27 - Ramal Petrogal - Asfaltos                            |\n";
    std::cout << "|                                                           |\n";
    std::cout << "|-----------------------------------------------------------|\n";
    std::cout << "|                                                           |\n";
}

std::string Line_Reliability::lineSelected(int num){
    std::vector<std::string> lines = {"Linha do Norte", "Linha do Oeste", "Linha do Minho", "Linha do Sul",
                                      "Linha do Douro", "Linha do Vouga", "Linha da Beira Baixa", "Linha da Beira Alta", "Linha do Algarve",
                                      "Linha do Alentejo", "Linha de Cascais", "Linha de Sintra", "Linha do Leste", "Linha de Guimarães",
                                      "Linha de Vendas Novas", "Ramal de Braga", "Linha de Cintura", "Ramal de Tomar", "Linha de Leixões",
                                      "Ramal de Alfarelos", "Linha de Sines", "Linha de Évora", "Ramal Neves Corvo", "Rede Espanhola",
                                      "Ramal da Lousã", "Concordância São Gemil", "Ramal Petrogal - Asfaltos"};
    return lines[num-1];
}