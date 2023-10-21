#include "../includes/Metricas/Metricas.h"

/**
 * Function to calculate the similarity between two users using the Euclidean Distance
*/
double EuclideanDistance(std::vector<double> usu1, std::vector<double> usu2, double min) 
{
    double sum = 0.0;
    double result = 0.0;
    for (int i = 0; i < usu1.size(); i++) 
    {
        if (usu1[i] == min -1 && usu2[i] == min - 1) 
        {
            return -2;
        }
        if(usu1[i] != min - 1 && usu2[i] != min - 1) 
        {
            sum += pow(usu1[i] - usu2[i], 2);
        }
    }
    result = sqrt(sum);
    return 1 / result;
}
