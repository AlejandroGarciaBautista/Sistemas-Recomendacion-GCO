#pragma once 
#include "../Utils.h"

double SimplePrediction(std::vector<std::vector<double>> data, int item, std::vector<std::pair<int,double>> similarity_neighbors);
double DifferenceWithAverage(std::vector<std::vector<double>> data, int item, int user, std::vector<std::pair<int,double>> similarity_neighbors, int min);
