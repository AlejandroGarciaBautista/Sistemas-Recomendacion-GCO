#include "../includes/Utils.h"

/**
 * Function to calculate the similarity between two users using the Pearson's correlation coefficient 
*/
double Pearson(std::vector<double> usu1, std::vector<double> usu2, double min) 
{
    double user1_average_scores = ArithmeticMean(usu1, usu1, min);
    double user2_average_scores = ArithmeticMean(usu2, usu1, min);
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
            sum_upper_part += ((usu1[i]-user1_average_scores)*(usu2[i]-user2_average_scores));
            bottom_part_usu1 += pow(((usu1[i]-user1_average_scores)),2);
            bottom_part_usu2 += pow(((usu2[i]-user2_average_scores)),2);
        }
    }
    return (sum_upper_part / (sqrt(bottom_part_usu1) * sqrt(bottom_part_usu2)));
}