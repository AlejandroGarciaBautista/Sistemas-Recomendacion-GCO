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

bool checkIfItsNum(char character_to_check) 
{
    // std::cout << character_to_check << "\n";
    // NO FUNCIONA PARA VALORES SUPERIORES A 9 DEBIDO A QUE SE EXAMINA DIGITO A DIGITO
    if (character_to_check == '0' || character_to_check == '1' || character_to_check == '2' || character_to_check == '3' || character_to_check == '4' || character_to_check == '5' || character_to_check == '6' || character_to_check == '7' || character_to_check == '8' || character_to_check == '9' )
    {
        // std::cout << "entro" << "\n";
        return true;
    }

    return false;
}

std::vector<double> convertStringVec_Into_DoubleVec (std::string line )
{
    std::vector<double> double_vec;
    //std::cout << line << "\n";
    for(int i = 0; i < line.size(); i++) 
    {
        std::string substr = "";
        // std::cout << "llega";
        // std::cout << "check(" << line[i] << ")";
        // std::cout << "check(" << std::to_string(line[i]) << ")";
        //std::cout << line[i] << " ";
        if (checkIfItsNum(line[i])) 
        {
            // std::cout << "llega2";
            substr = line[i];
            substr += line[i + 1];
            substr += line[i + 2];
            substr += line[i + 3];
            substr += line[i + 4];
            i += 4;
            // std::cout << substr;
            double_vec.emplace_back(std::stod(substr));
            // std::cout << ".\n";
        }
        else if (line[i] == '-') 
        {
            double_vec.emplace_back(-1.000);
        }
        else 
        {

        }
    }
    return double_vec;
}

void printMatrix(std::vector<std::vector<double>> Matrix) 
{
    for (int i = 0; i < Matrix.size(); i++) 
    {
        //std::cout << "entra\n";
        for (int j = 0; j < Matrix[i].size(); j++) 
        {
            //std::cout << "entra\n";
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<double>> fillMatrix(std::vector<std::string> lines_vec)
{
    std::vector<std::vector<double>> Matrix;
    for (int i= 0; i < lines_vec.size(); i++) 
    {
        Matrix.emplace_back(convertStringVec_Into_DoubleVec(lines_vec[i]));
    }
    return Matrix;
}


int main(int argc, char *argv[])
{
    std::ifstream matriz{argv[1]};

    std::string linea;

    std::vector<std::vector<double>> Matrix;

    // valor minimo de puntuación asignable
    std::getline(matriz, linea);
    MIN = std::stoi(linea);
    // valor máximo de puntuación asignable
    std::getline(matriz, linea);
    MAX = std::stoi(linea);

    //std::cout << "Min:" << MIN << "\n";
    //std::cout << "Max:" << MAX << "\n";

    int fila = 0;
    std::vector<std::string> lines_vec;
    while (std::getline(matriz, linea))
    {
        //fillMatrix(Matrix, linea, fila);
        lines_vec.emplace_back(linea);
        fila++;
    }

    // for (int i = 0; i  < lines_vec.size(); i++) 
    // {
    //     std::cout << lines_vec[i] << "\n";
    // }

    Matrix = fillMatrix(lines_vec);

    printMatrix(Matrix);
    return 0;
}