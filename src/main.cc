#include "includes/Utils.h"
#include "includes/Metricas/Metricas.h"
#include "includes/Predicciones/Predicciones.h"

int main(int argc, char *argv[])
{
    // Usage(argc, argv);
    std::ifstream matriz{argv[2]};
    int metodo = std::stoi(argv[4]), vecinos = std::stoi(argv[6]), prediccion = std::stoi(argv[8]);
    std::string linea;

    std::vector<std::vector<double>> Matrix;

    // valor minimo de puntuación asignable
    std::getline(matriz, linea);
    double min = std::stoi(linea);
    // valor máximo de puntuación asignable
    std::getline(matriz, linea);
    double max = std::stoi(linea);

    int fila = 0;
    std::vector<std::string> lines_vec;
    while (std::getline(matriz, linea))
    {
        lines_vec.emplace_back(linea);
        fila++;
    }

    Matrix = fillMatrix(lines_vec, min);
    std::cout << "MATRIZ DE ENTRADA:\n";
    // printMatrix(Matrix);
    
    // normalizarMatrix(Matrix, min, max);
    // std::cout << "\nMatriz Normalizada:\n";
    // printMatrix(Matrix);

    Start(Matrix, metodo, vecinos, prediccion, min, max);

    return 0;
}