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
#include <iomanip>

void normalizarMatrix(std::vector<std::vector<double>> &matrix, double min, double max);
void denormalizarMatrix(std::vector<std::vector<double>> &matrixNormalizada, double min, double max);
void Usage(int argc, char* argv[]);
bool checkIfItsNum(char character_to_check);
std::vector<double> convertStringVec_Into_DoubleVec (std::string line, double min);
void printMatrix(std::vector<std::vector<double>> Matrix);
std::vector<std::vector<double>> fillMatrix(std::vector<std::string> lines_vec, double min);
double calcularMedia (std::vector<double> usu, std::vector<double> pivot_user, double min);


// Uso de la aplicación
void Start(std::vector<std::vector<double>>& matrix, int metodo, int vecinos, int prediccion, double min, double max);
std::vector<std::pair<int,double>> GetAllSimilarity(std::vector<std::vector<double>> matrix, int metodo, int inicio, double min);
std::vector<std::pair<int,double>> GetNHighest(int vecinos, std::vector<std::pair<int,double>> pairs);
std::vector<std::pair<int,int>> FindAllQuestions(std::vector<std::vector<double>> matrix, double min);
double GetPrediction(std::vector<std::vector<double>> data, int item, std::vector<std::pair<int,double>> similarity_neighbors, int prediction, int user, int min);
void fillGap(std::vector<std::vector<double>> &Matrix, int usu , int item, double prediction, double max);
