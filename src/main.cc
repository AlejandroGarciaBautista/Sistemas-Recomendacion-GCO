#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Ejecución ./sistemas_recomendacion -f <fichero> -m <metrica> -v <vecinos> -p <prediccion>

void Usage()
{
}

int MIN, MAX;

void fillMatrix(std::vector<std::vector<int>> &Matrix, std::string line, int fila)
{
    for (int i = 0; i < line.size(); i++)
    {

        char car = line[i];

        // Matrix.emplace_back(1);
        // Matrix.emplace_back(2);
        // Matrix.emplace_back(3);
        // Matrix.emplace_back(4);
        if (car == ' ')
        {
            // std::cout << line[i];
        }
        else if (car == '-')
        {
            Matrix[fila].emplace_back(MIN - 1);
        }
        else
        {

            Matrix[fila].emplace_back(std::stoi(std::to_string(car)));
        }
    }

    // std::cout << Matrix[0][0] << "AQUI" << std::endl;
}

void printMatrix(std::vector<std::vector<int>> Matrix)
{
    for (int i = 0; i < Matrix.size(); i++)
    {
        for (int j = 0; i < Matrix[i].size(); j++)
        {
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int ConvertirANumero(std::string caracter);

int main(int argc, char *argv[])
{
    std::ifstream matriz{argv[1]};

    std::string linea;

    std::vector<std::vector<int>> Matrix;

    // valor minimo de puntuación asignable
    std::getline(matriz, linea);
    MIN = std::stoi(linea);
    // valor máximo de puntuación asignable
    std::getline(matriz, linea);
    MAX = std::stoi(linea);

    int fila = 0;
    while (std::getline(matriz, linea))
    {
        fillMatrix(Matrix, linea, fila);
        fila++;
    }
    // printMatrix(Matrix);
    return 0;
}

int ConvertirANumero(std::string caracter)
{
    if (caracter == "-")
    {
        return MIN - 1;
    }
    return std::stoi(caracter);
}