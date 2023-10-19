#include "../includes/Predicciones/Predicciones.h"

double DifferenceWithAverage(std::vector<std::vector<double>> data, int item, int user, std::vector<std::pair<int,double>> similarity_neighbors, int min)
{
  double average_user = calcularMedia(data[user], min);
  double result = average_user, sum_of_items = 0, sum_of_similarities = 0;

  for (int i = 0; i < similarity_neighbors.size(); i++) {
    double average_actual_user = calcularMedia(data[similarity_neighbors[i].first], min);
    double aux = similarity_neighbors[i].second;
    sum_of_items += (aux * (data[similarity_neighbors[i].first][item] - average_actual_user));
    sum_of_similarities += fabs(similarity_neighbors[i].second);
  }
  result += sum_of_items / sum_of_similarities;

  return result;
}
