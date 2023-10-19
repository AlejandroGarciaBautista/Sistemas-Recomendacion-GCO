    // std::vector<double> primero = {5.0, 3.0, 4.0, 4.0};

    // std::vector<double> segundo = {3.0,1.0,2.0,3.0};
    // switch (metodo) {
    //     case 1:
    //         std::cout << "COEF CORREL: " << coefCorrel(primero, segundo, MIN) << "\n";
    //         break;
    //     case 2:
    //         std::cout << "Distancia Coseno: " << distCoseno(primero, segundo, MIN) << "\n";
    //         break;
    //     case 3:
    //         std::cout << "Distancia Euclidea: ";
    //         break;
    //     default:
    //         break;
    // }


// double MIN, MAX;

// void normalizarMatrix(std::vector<std::vector<double>> &matrix) 
// {
//     for (int i = 0; i < matrix.size(); i++) 
//     {
//         for (int j = 0; j  < matrix[i].size(); j++)
//         {
//             // Formula de normalizacion
//             if (matrix[i][j] == MIN -1) 
//             {
//                 matrix[i][j] = MIN -1;
//             }
//             else 
//             {
//                 // z i = (x i – mínimo (x)) / (máximo (x) – mínimo (x)) 
//                 matrix[i][j] = (matrix[i][j] - MIN) / (MAX - MIN); 
//             }
//         }
//     }
// }

// void denormalizarMatrix(std::vector<std::vector<double>> &matrixNormalizada) 
// {
//     for (int i = 0; i < matrixNormalizada.size(); i++)
//     {
//         for (int j = 0; j < matrixNormalizada[i].size(); j++)
//         {
//             if (matrixNormalizada[i][j] == MIN -1) 
//             {
//                 matrixNormalizada[i][j] = MIN -1;
//             }
//             else 
//             {
//                 matrixNormalizada[i][j] = (matrixNormalizada[i][j] * (MAX - MIN)) + MIN;
//             }
//         }
//     }
// }

// void Usage(int argc, char* argv[])
// {
//     if (argc == 2) 
//     {
//         std::string ayuda{argv[1]};
//         if (ayuda == "--help") {
//             std::cout << "Ejecución: ./sistemas_recomendacion -f <fichero> -m <metrica> -v <vecinos> -p <prediccion>" << std::endl;
//             std::cout << "Metrica:\nElige entre: 1. Correlación de Pearson\n2. Distancia Coseno\n3. Distancia Euclidea" << std::endl;
//             std::cout << "Vecinos: Elige la cantidad de vecinos con los que se va a comparar" << std::endl;
//             std::cout << "Predicción:\nElige entre: 1. Diferencia con media\n2. Predicción Simple\n" << std::endl;
//             exit(EXIT_SUCCESS);
//         }
//     }

//     if (argc != 9) {
//         std::cout << "¡Error en la ejecución del programa!" << std::endl;
//         std::cout << "Para obtener más informacion ejecute " << argv[0] << " --help" << std::endl;
//         exit(EXIT_SUCCESS);
//     }
// }

// bool checkIfItsNum(char character_to_check) 
// {
//     // std::cout << character_to_check << "\n";
//     // NO FUNCIONA PARA VALORES SUPERIORES A 9 DEBIDO A QUE SE EXAMINA DIGITO A DIGITO
//     if (character_to_check == '0' || character_to_check == '1' || character_to_check == '2' || character_to_check == '3' || character_to_check == '4' || character_to_check == '5' || character_to_check == '6' || character_to_check == '7' || character_to_check == '8' || character_to_check == '9' )
//     {
//         return true;
//     }

//     return false;
// }

// std::vector<double> convertStringVec_Into_DoubleVec (std::string line )
// {
//     std::vector<double> double_vec;
//     for(int i = 0; i < line.size(); i++) 
//     {
//         std::string substr = "";
//         if (checkIfItsNum(line[i]))
//         {
//             substr = line[i];
//             substr += line[i + 1];
//             substr += line[i + 2];
//             substr += line[i + 3];
//             substr += line[i + 4];
//             i += 4;
//             double_vec.emplace_back(std::stod(substr));
//         }
//         else if (line[i] == '-') 
//         {
//             double_vec.emplace_back(MIN -1 );
//         }
//     }
//     return double_vec;
// }

// void printMatrix(std::vector<std::vector<double>> Matrix) 
// {
//     for (int i = 0; i < Matrix.size(); i++) 
//     {
//         //std::cout << "entra\n";
//         for (int j = 0; j < Matrix[i].size(); j++) 
//         {
//             //std::cout << "entra\n";
//             std::cout << Matrix[i][j] << " ";
//         }
//         std::cout << "\n";
//     }
// }

// std::vector<std::vector<double>> fillMatrix(std::vector<std::string> lines_vec)
// {
//     std::vector<std::vector<double>> Matrix;
//     for (int i= 0; i < lines_vec.size(); i++) 
//     {
//         Matrix.emplace_back(convertStringVec_Into_DoubleVec(lines_vec[i]));
//     }
//     return Matrix;
// }