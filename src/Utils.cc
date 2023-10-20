#include "./includes/Utils.h"
#include "./includes/Metricas/Metricas.h"
#include "./includes/Predicciones/Predicciones.h"

double normalizarNumero(double num, int min,int max)
{
    return ((num - min) / (max - min));
}

void normalizarMatrix(std::vector<std::vector<double>> &matrix, double min, double max) 
{
    for (int i = 0; i < matrix.size(); i++) 
    {
        for (int j = 0; j  < matrix[i].size(); j++)
        {
            // Formula de normalizacion
            if (matrix[i][j] == min -1) 
            {
                matrix[i][j] = min -1;
            }
            else 
            {
                // z i = (x i – mínimo (x)) / (máximo (x) – mínimo (x)) 
                matrix[i][j] = (matrix[i][j] - min) / (max - min); 
            }
        }
    }
}

void denormalizarMatrix(std::vector<std::vector<double>> &matrixNormalizada, double min, double max) 
{
    for (int i = 0; i < matrixNormalizada.size(); i++)
    {
        for (int j = 0; j < matrixNormalizada[i].size(); j++)
        {
            if (matrixNormalizada[i][j] == min -1) 
            {
                matrixNormalizada[i][j] = min -1;
            }
            else 
            {
                matrixNormalizada[i][j] = (matrixNormalizada[i][j] * (max - min)) + min;
            }
        }
    }
}

void Usage(int argc, char* argv[])
{
    if (argc == 2) 
    {
        std::string ayuda{argv[1]};
        if (ayuda == "--help") {
            std::cout << "Ejecución: ./sistemas_recomendacion -f <fichero> -m <metrica> -v <vecinos> -p <prediccion>" << std::endl;
            std::cout << "Metrica:\nElige entre: 1. Correlación de Pearson\n2. Distancia Coseno\n3. Distancia Euclidea" << std::endl;
            std::cout << "Vecinos: Elige la cantidad de vecinos con los que se va a comparar" << std::endl;
            std::cout << "Predicción:\nElige entre: 1. Diferencia con media\n2. Predicción Simple\n" << std::endl;
            exit(EXIT_SUCCESS);
        }
    }

    if (argc != 9) {
        std::cout << "¡Error en la ejecución del programa!" << std::endl;
        std::cout << "Para obtener más informacion ejecute " << argv[0] << " --help" << std::endl;
        exit(EXIT_SUCCESS);
    }
}

bool checkIfItsNum(char character_to_check) 
{
    // std::cout << character_to_check << "\n";
    // NO FUNCIONA PARA VALORES SUPERIORES A 9 DEBIDO A QUE SE EXAMINA DIGITO A DIGITO
    if (character_to_check == '0' || character_to_check == '1' || character_to_check == '2' || character_to_check == '3' || character_to_check == '4' || character_to_check == '5' || character_to_check == '6' || character_to_check == '7' || character_to_check == '8' || character_to_check == '9' )
    {
        return true;
    }

    return false;
}

std::vector<double> convertStringVec_Into_DoubleVec (std::string line, double min)
{
    std::vector<double> double_vec;
    for(int i = 0; i < line.size(); i++) 
    {
        std::string substr = "";
        if (checkIfItsNum(line[i]))
        {
            substr = line[i];
            substr += line[i + 1];
            substr += line[i + 2];
            substr += line[i + 3];
            substr += line[i + 4];
            i += 4;
            double_vec.emplace_back(std::stod(substr));
        }
        else if (line[i] == '-') 
        {
            double_vec.emplace_back(min -1 );
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
            //std::cout << std::setprecision(3) << Matrix[i][j] << " ";
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<double>> fillMatrix(std::vector<std::string> lines_vec, double min)
{
    std::vector<std::vector<double>> Matrix;
    for (int i= 0; i < lines_vec.size(); i++) 
    {
        Matrix.emplace_back(convertStringVec_Into_DoubleVec(lines_vec[i], min));
    }
    return Matrix;
}

double calcularMedia (std::vector<double> usu, std::vector<double> pivot_user, double min) {
    int numItems = 0;
    double media;
    for (int i = 0; i < pivot_user.size(); i++) {
        if (pivot_user[i] != min - 1 && usu[i] != min - 1) {
            numItems++;
            media += usu[i]; 
        }
    }

    return media/numItems;
}

void fillGap(std::vector<std::vector<double>> &Matrix, int usu , int item, double prediction, double max) 
{
    if (prediction > 1) 
    {
        Matrix[usu][item] = 1.000;
    } else {
        Matrix[usu][item] = prediction;
    }
}

void Start(std::vector<std::vector<double>>& matrix, int metodo, int vecinos, int prediccion, double min, double max) {
    std::vector<std::pair<int,int>> questions = FindAllQuestions(matrix, min);
    for (int i = 0; i < questions.size(); i++) 
    {
        int user = questions[i].first;
        int item = questions[i].second;

        // Obtengo las similitudes del usuario actual con los demas
        std::vector<std::pair<int,double>> all_similarity = GetAllSimilarity(matrix, metodo, user, min);
        
        std::cout << "----- RELLENANDO USUARIO " << user <<  " ---- ITEM ----" << item << std::endl; 

        for (int j = 0; j < all_similarity.size(); j++)
        {
            std::cout << "Similitud usuario: " << all_similarity[j].first << " = " << all_similarity[j].second << std::endl;
            // std::cout << "Media: " << calcularMedia(matrix[all_similarity[j].first], matrix[user], min) << std::endl;
        }
        
        // Guardo los vecinos que me interesan
        std::vector<std::pair<int,double>> similarity_neighbors = GetNHighest(vecinos, all_similarity);
        for (int j = 0; j < similarity_neighbors.size(); j++)
        {
            std::cout << "Similitud elegida usuario: " << similarity_neighbors[j].first << " = " << similarity_neighbors[j].second << std::endl;
            // std::cout << "Media: " << calcularMedia(matrix[all_similarity[j].first], matrix[user], min) << std::endl;
        }
        // Inicio la predicción para ese usuario
        double prediction_result = GetPrediction(matrix, item, similarity_neighbors, prediccion, user, min);
        std::cout << "Prediccion: " << prediction_result << std::endl;

        //* Rellenar la matrix
        fillGap(matrix, user, item, prediction_result, max);
        // printMatrix(matrix);
    }
    
}

double GetPrediction(std::vector<std::vector<double>> data, int item, std::vector<std::pair<int,double>> similarity_neighbors, int prediction, int user, int min)
{
    double result;
    switch (prediction)
    {
        case 1:
            result = SimplePrediction(data, item, similarity_neighbors);
            break;
        case 2:
            result = DifferenceWithAverage(data, item, user, similarity_neighbors, min);
            break;
    }
    return result;
}

std::vector<std::pair<int,double>> GetAllSimilarity(std::vector<std::vector<double>> matrix, int metodo, int inicio, double min) 
{
    std::vector<std::pair<int,double>> result;
    switch (metodo) {
        case 1: {
            if (inicio != 0) {
                for (int i = 0; i < inicio; i++)
                {
                    result.push_back(std::make_pair(i, coefCorrel(matrix[inicio], matrix[i], min)));
                }

                for (int i = inicio + 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, coefCorrel(matrix[inicio], matrix[i], min)));
                }
            } else {
                for (int i = 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, coefCorrel(matrix[0], matrix[i], min)));
                }
            }
            break;
        }
            
        case 2: {
            if (inicio != 0) {
                for (int i = 0; i < inicio; i++)
                {
                    result.push_back(std::make_pair(i, distCoseno(matrix[inicio], matrix[i], min)));
                }

                for (int i = inicio + 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, distCoseno(matrix[inicio], matrix[i], min)));
                }
            } else {
                for (int i = 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, distCoseno(matrix[0], matrix[i], min)));
                }
            }
            break;
        }

        case 3: {
            if (inicio != 0) {
                for (int i = 0; i < inicio; i++)
                {
                    result.push_back(std::make_pair(i, distEuclidea(matrix[inicio], matrix[i], min)));
                }

                for (int i = inicio + 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, distEuclidea(matrix[inicio], matrix[i], min)));
                }
            } else {
                for (int i = 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, distEuclidea(matrix[0], matrix[i], min)));
                }
            }
            break;
        }     
    }
    return result;
}

std::vector<std::pair<int,double>> GetNHighest(int vecinos, std::vector<std::pair<int,double>> pairs) 
{
    std::vector<std::pair<int,double>> similitud_vecinos;
    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        return a.second > b.second;
    });

    for (int i = 0; i < vecinos && i < pairs.size(); i++) {
        if (pairs[i].second != -2.000) {
            similitud_vecinos.push_back(pairs[i]);
        }
    }
    return similitud_vecinos;
}

std::vector<std::pair<int,int>> FindAllQuestions(std::vector<std::vector<double>> matrix, double min)
{
    std::vector<std::pair<int,int>> questions;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == min - 1)
            {
                questions.push_back(std::make_pair(i, j));
            }
        }
    }
    return questions;
}
