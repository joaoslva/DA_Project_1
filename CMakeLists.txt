cmake_minimum_required(VERSION 3.24)
project(Projeto_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Projeto_1 main.cpp CsvReader.cpp Graph.cpp Graph.h StationRailway.cpp StationRailway.h menus/Service_Metrics.cpp menus/Service_Metrics.h menus/Operation_Cost_optimization.cpp menus/Operation_Cost_optimization.h menus/Line_Reliability.cpp menus/Line_Reliability.h menus/Menu.cpp menus/Menu.h)
