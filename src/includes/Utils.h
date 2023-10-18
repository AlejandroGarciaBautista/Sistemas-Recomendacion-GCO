#pragma once 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <algorithm>

double MIN, MAX;

void normalizarMatrix(std::vector<std::vector<double>> &matrix);
void denormalizarMatrix(std::vector<std::vector<double>> &matrixNormalizada);
void Usage(int argc, char* argv[]);
bool checkIfItsNum(char character_to_check);
std::vector<double> convertStringVec_Into_DoubleVec (std::string line );
void printMatrix(std::vector<std::vector<double>> Matrix);
std::vector<std::vector<double>> fillMatrix(std::vector<std::string> lines_vec);
double calcularMedia (std::vector<double> usu, double MIN);


// Uso de la aplicación
void Start(std::vector<std::vector<double>> matrix, int metodo, int vecinos, int prediccion);
std::vector<std::pair<int,double>> GetAllSimilarity(std::vector<std::vector<double>> matrix, int metodo, int inicio);
std::vector<std::pair<int,double>> GetNHighest(int vecinos, std::vector<std::pair<int,double>> pairs);
