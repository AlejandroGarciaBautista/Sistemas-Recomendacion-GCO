#include "./includes/Utils.h"
#include "./includes/Metricas/Metricas.h"
#include "./includes/Predicciones/Predicciones.h"
#include "./includes/color_text.h"

/**
 * Function that helps to check that the CLI app is used in the correct way and all the
 * arguments are provided
*/
void Usage(int argc, char *argv[], std::string& file_name, int& m, int& v, int& p)
{
    struct option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"fichero", required_argument, nullptr, 'f'},
        {"metrica", required_argument, nullptr, 'm'},
        {"vecinos", required_argument, nullptr, 'v'},
        {"prediccion", required_argument, nullptr, 'p'},
        {nullptr, 0, nullptr, 0}
    };

    int option, option_index = 0;

    while ((option = getopt_long(argc, argv, "h:f:m:v:p:", long_options, &option_index)) != -1) 
    {
        switch (option) 
        {
            case 'h':
                std::cout << "Uso: " << argv[0] << " y añadir las siguientes opciones" << std::endl;
                std::cout << "Opciones:" << std::endl;
                std::cout << "  -f, --fichero <nombre>   Especificar el fichero txt" << std::endl;
                std::cout << "  -m, --metrica <numero>   Elegir una métrica (1.Correlación de Pearson, 2.Distancia Coseno o 3.Distancia Euclidea)" << std::endl;
                std::cout << "  -v, --vecinos <numero>   Especificar la cantidad de vecinos" << std::endl;
                std::cout << "  -p, --prediccion <numero> Elegir predicción (1.Simple, 2.Diferencia con la media)" << std::endl;
                exit(EXIT_SUCCESS);
            case 'f': 
                file_name = optarg;
                break;
            case 'm': 
            {
                if (atoi(optarg) != 1 && atoi(optarg) != 2 && atoi(optarg) != 3)
                {
                    std::cout << "Error, opción para la métrica no valida. Ejecuta " << argv[0] << " --help para más ayuda" << std::endl;
                    exit(EXIT_FAILURE); 
                }
                m = atoi(optarg);
                break;
            }  
            case 'v': 
            {
                if (atoi(optarg) == 0)
                {
                    std::cout << "Error, los vecinos deben ser >= 1" << std::endl;
                    exit(EXIT_FAILURE);
                }
                v = atoi(optarg);
                break;
            }
                
            case 'p': 
            {
                if (atoi(optarg) != 1 && atoi(optarg) != 2)
                {
                    std::cout << "Error, opción para la predicción no valida. Ejecuta " << argv[0] << " --help para más ayuda" << std::endl;
                    exit(EXIT_FAILURE); 
                }
                p = atoi(optarg);
                break;
            }
            case '?':
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }

    if (file_name == "" || m == -1 || p == -1 || v == -1)
    {
        std::cout << "Error, faltan argumentos, ejecute " << argv[0] << " --help para más ayuda" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * Function to normalize the matrix, this function changes the range from [min, max]
 * to [0,1]
*/ 
void NormalizeMatrix(std::vector<std::vector<double>> &matrix, double min, double max) 
{
    for (int i = 0; i < matrix.size(); i++) 
    {
        for (int j = 0; j  < matrix[i].size(); j++)
        {
            if (matrix[i][j] == min -1) // If the position matches with a - it is not normalize
            {
                matrix[i][j] = min -1;
            }
            else 
            {
                // zi = (xi – min(x)) / (max(x) – min(x)) 
                matrix[i][j] = (matrix[i][j] - min) / (max - min); 
            }
        }
    }
}

/**
 * Function to denormalize the matrix, this function changes the range from [0, 1]
 * to the original range defined by [min,max]
*/
void DenormalizeMatrix(std::vector<std::vector<double>> &normalized_matrix, double min, double max) 
{
    for (int i = 0; i < normalized_matrix.size(); i++)
    {
        for (int j = 0; j < normalized_matrix[i].size(); j++)
        {
            if (normalized_matrix[i][j] == min -1) 
            {
                normalized_matrix[i][j] = min -1;
            }
            else 
            {
                normalized_matrix[i][j] = (normalized_matrix[i][j] * (max - min)) + min;
            }
        }
    }
}

/**
 * Funtion to know if a character is a number or no
*/
bool CheckIfItsNum(char character_to_check) 
{
    // It only checks the range of [0-9] because is only checking char by char
    if (character_to_check == '0' || character_to_check == '1' || character_to_check == '2' || character_to_check == '3' || character_to_check == '4' || character_to_check == '5' || character_to_check == '6' || character_to_check == '7' || character_to_check == '8' || character_to_check == '9' )
    {
        return true;
    }
    return false;
}

/**
 * Function that helps checking if a element of the matrix is on range
*/
void CheckCorrectMatrixElement(double checked_num, double min, double max)
{
    if (checked_num < min || checked_num > max) {
        std::cout << "El valor " << checked_num << " se encuentra fuera del rango de la matrix(" << min << "," << max << ")\n";
        exit(EXIT_FAILURE);
    }
}

/**
 * Function that converts a string into a vector of double
*/
std::vector<double> ConvertStringVec_Into_DoubleVec(std::string line, double min, double max)
{
    std::vector<double> double_vec;
    for(int i = 0; i < line.size(); i++) 
    {
        std::string substr = "";
        if (CheckIfItsNum(line[i]))
        {
            substr = line[i];
            substr += line[i + 1];
            substr += line[i + 2];
            substr += line[i + 3];
            substr += line[i + 4];
            i += 4;
            // gestion de errores
            CheckCorrectMatrixElement(std::stod(substr), min, max);
            double_vec.emplace_back(std::stod(substr));
        }
        else if (line[i] == '-') 
        {
            double_vec.emplace_back(min -1 );
        }
    }
    return double_vec;
}

/**
 * Function to print the matrix
*/
void PrintMatrix(std::vector<std::vector<double>> matrix) 
{
    // COLOR TEXT CLASS
    Color::Modifier blue = Color::FG_BLUE;
    Color::Modifier red = Color::FG_RED;
    Color::Modifier green = Color::FG_GREEN;
    Color::Modifier blueBG = Color::BG_BLUE;
    Color::Modifier redBG = Color::BG_RED;
    Color::Modifier greenBG = Color::BG_GREEN;
    Color::Modifier def = Color::BG_DEFAULT;

    std::cout << green << " --- MATRIZ DE UTILIDAD CON LAS PREDICCIONES RESULTANTES SUSTITUIDAS EN LOS '-' DE LA MATRIZ ORIGINAL ---" << def << "\n";

    for (int i = 0; i < matrix.size(); i++) 
    {
        for (int j = 0; j < matrix[i].size(); j++) 
        {
            std::string elemento_como_string = std::to_string(matrix[i][j]);
            if(elemento_como_string.size() == 5) {
                std::cout << blue << matrix[i][j] << def << " ";
            } else if (elemento_como_string.size() < 5) {
                while (elemento_como_string.size() < 5)
                {
                    elemento_como_string += "0";
                }
                std::cout << blue << elemento_como_string << def << " ";
            } else if (elemento_como_string.size() > 5) {
                std::string substr_ = elemento_como_string.substr(0,5);
                std::cout << blue << substr_ << def << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

/**
 * Function to fill the matrix with the file that has been read
*/
std::vector<std::vector<double>> FillMatrix(std::vector<std::string> lines_vec, double min, double max)
{
    std::vector<std::vector<double>> Matrix;
    for (int i= 0; i < lines_vec.size(); i++) 
    {
        Matrix.emplace_back(ConvertStringVec_Into_DoubleVec(lines_vec[i], min, max));
    }
    return Matrix;
}

/**
 * Function to calculate the arithmetic mean of the ratings of a user using another user who acts as a pivot since they must have rated the same items
*/
double ArithmeticMean(std::vector<double> usu, std::vector<double> pivot_user, double min) 
{
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

/**
 * Function to fill the gap (-) of the item x of the user y.
*/
void FillGap(std::vector<std::vector<double>> &matrix, int usu , int item, double prediction, double max) 
{
    if (prediction > 1) 
    {
        matrix[usu][item] = 1.000;
    } else {
        matrix[usu][item] = prediction;
    }
}

/**
 * Function that starts the algorithm till it fills all the gaps on the matrix
*/
void Start(std::vector<std::vector<double>>& matrix, int metric, int neighbors, int prediction, double min, double max) {
    // COLOR TEXT CLASS
    Color::Modifier blue = Color::FG_BLUE;
    Color::Modifier red = Color::FG_RED;
    Color::Modifier green = Color::FG_GREEN;
    Color::Modifier def = Color::BG_DEFAULT;
    // Getting all the gaps of the matrix
    std::vector<std::pair<int,int>> questions = FindAllQuestions(matrix, min);
    for (int i = 0; i < questions.size(); i++) 
    {
        int user = questions[i].first;
        int item = questions[i].second;

        // Getting all the similarities of the current user
        std::vector<std::pair<int,double>> all_similarity = GetAllSimilarity(matrix, metric, user, min);
        
        std::cout << green << "----- RELLENANDO USUARIO " << red << user << green <<  " ---- ITEM ----" <<  red << item << def <<std::endl; 

        for (int j = 0; j < all_similarity.size(); j++)
        {
            std::cout << blue << "Similitud usuario: " << red << all_similarity[j].first << blue << " = " << red << all_similarity[j].second <<  def << std::endl;
        }
        
        // Saving only the n neighbors that were indicated by the user
        std::vector<std::pair<int,double>> similarity_neighbors = GetNHighest(neighbors, all_similarity);
        for (int j = 0; j < similarity_neighbors.size(); j++)
        {
            std::cout << green << "Similitud elegida usuario: " << red << similarity_neighbors[j].first << green << " = " << red << similarity_neighbors[j].second << def << std::endl;
        }
        // Getting the resoult of the prediction
        double prediction_result = GetPrediction(matrix, item, similarity_neighbors, prediction, user, min);
        std::cout << blue << "Prediccion: " << red << prediction_result << def << "\n\n";

        // Filling the actual gap of the matrix
        FillGap(matrix, user, item, prediction_result, max);
    }
    
}

/**
 * Funtion that returns the prediction of the punctuation to the item selected of the user x using the
 * type of prediction given by the user on the terminal
*/
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

/**
 * Funtion that returns a vector of pairs that contains in the fist part the user selected at the moment that is being evaluated with our pivot user
 * and on the second part it has the similarity of the pivot user with the user selected.
 * The function evaluates all the users with out pivot user and calculates the similarity.
*/
std::vector<std::pair<int,double>> GetAllSimilarity(std::vector<std::vector<double>> matrix, int metric, int start_point, double min) 
{
    std::vector<std::pair<int,double>> result;
    switch(metric) 
    {
        case 1: 
        {
            if (start_point != 0) {
                for (int i = 0; i < start_point; i++)
                {
                    result.push_back(std::make_pair(i, Pearson(matrix[start_point], matrix[i], min)));
                }

                for (int i = start_point + 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, Pearson(matrix[start_point], matrix[i], min)));
                }
            } else 
            {
                for (int i = 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, Pearson(matrix[0], matrix[i], min)));
                }
            }
            break;
        }
            
        case 2: 
        {
            if (start_point != 0) 
            {
                for (int i = 0; i < start_point; i++)
                {
                    result.push_back(std::make_pair(i, CosineDistance(matrix[start_point], matrix[i], min)));
                }

                for (int i = start_point + 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, CosineDistance(matrix[start_point], matrix[i], min)));
                }
            } else 
            {
                for (int i = 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, CosineDistance(matrix[0], matrix[i], min)));
                }
            }
            break;
        }

        case 3: 
        {
            if (start_point != 0) 
            {
                for (int i = 0; i < start_point; i++)
                {
                    result.push_back(std::make_pair(i, EuclideanDistance(matrix[start_point], matrix[i], min)));
                }

                for (int i = start_point + 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, EuclideanDistance(matrix[start_point], matrix[i], min)));
                }
            } else 
            {
                for (int i = 1; i < matrix.size(); i++)
                {
                    result.push_back(std::make_pair(i, EuclideanDistance(matrix[0], matrix[i], min)));
                }
            }
            break;
        }     
    }
    return result;
}

/**
 * Funtion that returns the n highest pairs of similarities, ordered in descending order
*/
std::vector<std::pair<int,double>> GetNHighest(int neighbors, std::vector<std::pair<int,double>> pairs) 
{
    std::vector<std::pair<int,double>> similarity_neighbors;
    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        return a.second > b.second;
    });

    for (int i = 0; i < neighbors && i < pairs.size(); i++) {
        if (pairs[i].second != -2.000) {
            similarity_neighbors.push_back(pairs[i]);
        }
    }
    return similarity_neighbors;
}

/**
 * Function that returns all the gaps on the matrix
*/
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
