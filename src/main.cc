/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Gestión del Conocimiento en las Organizaciones
 * Curso: 4º
 * Sistemas de Recomendación. Métodos de filtrado colaborativo
 * @authors: 
 *  -Alejandro García Bautista (alu0101387604)
 *  -Lucas Pérez Rosario (alu0101399928)
 *  -Adrián González Expósito (alu0101404813)
 * @date: 24/10/2023
 */

#include "includes/Utils.h"
#include "includes/Metricas/Metricas.h"
#include "includes/Predicciones/Predicciones.h"

int main(int argc, char *argv[])
{
    // Variables declaration for the file name, metrics, neighbors, prediction and the matrix that will be used along the program
    std::string file_name;
    int metrics = -1, neighbors = -1, prediction = -1;
    std::vector<std::vector<double>> Matrix;

    // Check correct use of the application and read the arguments of the CLI
    Usage(argc, argv, file_name, metrics, neighbors, prediction);
    std::ifstream matrix_file{file_name};

    // Lets start reading the file
    std::string line;

    // Getting minimum valuation possible
    std::getline(matrix_file, line);
    double min = std::stoi(line);
    // Getting maximum valuation possible
    std::getline(matrix_file, line);
    double max = std::stoi(line);

    // Declaration of a variable to know number off row (users)
    int rows = 0;
    std::vector<std::string> lines_vec;
    while (std::getline(matrix_file, line))
    {
        lines_vec.emplace_back(line);
        rows++;
    }

    // Checking that the neighbors are in the correct range
    if (neighbors >= rows)
    {
        std::cout << "Error, el número de vecinos debe ser <= al número de usuario -1" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Filling the matrix
    Matrix = FillMatrix(lines_vec, min, max);
    
    // Normalize the matrix and start the program
    NormalizeMatrix(Matrix, min, max);
    Start(Matrix, metrics, neighbors, prediction, min, max);

    // Once the program is finished the matrix is denormalized and the resulting matrix is shown
    DenormalizeMatrix(Matrix, min, max);
    PrintMatrix(Matrix);
    return 0;
}
