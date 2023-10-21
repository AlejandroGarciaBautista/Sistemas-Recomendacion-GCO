#include "../includes/Predicciones/Predicciones.h"

/**
 * Function that performs the simple prediction
*/
double SimplePrediction(std::vector<std::vector<double>> data, int item, std::vector<std::pair<int,double>> similarity_neighbors)
{
  double result, sum_of_items = 0, sum_of_similarities = 0;

  for (int i = 0; i < similarity_neighbors.size(); i++) 
  {
    double aux = (similarity_neighbors[i].second * data[similarity_neighbors[i].first][item]);
    sum_of_items += aux;
    sum_of_similarities += fabs(similarity_neighbors[i].second);
  }
  
  result = sum_of_items / sum_of_similarities;
  return result;
}
