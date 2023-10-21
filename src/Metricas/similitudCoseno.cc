#include "../includes/Metricas/Metricas.h"

/**
 * Funtion to calculate the similarity between two users using the Cosine Distance
*/
double CosineDistance(std::vector<double> usu1, std::vector<double> usu2, double min) 
{
    double sum_upper_part = 0.0;
    double bottom_part_usu1 = 0.0;
    double bottom_part_usu2 = 0.0;
    for (int i = 0; i < usu1.size(); i++) 
    {
        if (usu1[i] == min -1 && usu2[i] == min - 1) 
        {
            return -2;
        }
        if(usu1[i] != min - 1 && usu2[i] != min - 1) 
        {
            sum_upper_part += (usu1[i]*usu2[i]);
            bottom_part_usu1 += pow(usu1[i],2);
            bottom_part_usu2 += pow(usu2[i],2);
        }
    }
    return (sum_upper_part / (sqrt(bottom_part_usu1) * sqrt(bottom_part_usu2)));
}
