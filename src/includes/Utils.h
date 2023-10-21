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
#include <cstring>
#include <getopt.h>

// Functions related to use of the app
void Usage(int argc, char *argv[], std::string& file_name, int& m, int& v, int& p);

// Funtions related to managing the matrix
void NormalizeMatrix(std::vector<std::vector<double>> &matrix, double min, double max);
void DenormalizeMatrix(std::vector<std::vector<double>> &normalized_matrix, double min, double max);
void PrintMatrix(std::vector<std::vector<double>> matrix);
std::vector<std::vector<double>> FillMatrix(std::vector<std::string> lines_vec, double min, double max);
void FillGap(std::vector<std::vector<double>> &matrix, int usu , int item, double prediction, double max);

// Funtions related to checking thing 
bool CheckIfItsNum(char character_to_check);
void CheckCorrectMatrixElement(double checked_num, double min, double max);

// Functions related to calculating and converting things
double ArithmeticMean(std::vector<double> usu, std::vector<double> pivot_user, double min);
std::vector<double> ConvertStringVec_Into_DoubleVec (std::string line, double min, double max);

// Functions related to the use of the application
void Start(std::vector<std::vector<double>>& matrix, int metric, int neighbors, int prediction, double min, double max);
std::vector<std::pair<int,double>> GetAllSimilarity(std::vector<std::vector<double>> matrix, int metric, int inicio, double min);
std::vector<std::pair<int,double>> GetNHighest(int neighbors, std::vector<std::pair<int,double>> pairs);
std::vector<std::pair<int,int>> FindAllQuestions(std::vector<std::vector<double>> matrix, double min);
double GetPrediction(std::vector<std::vector<double>> data, int item, std::vector<std::pair<int,double>> similarity_neighbors, int prediction, int user, int min);
