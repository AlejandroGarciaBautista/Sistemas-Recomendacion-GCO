#include "../includes/Metricas/Metricas.h"

/**
 * Calculamos la similitud entre dos usuarios haciendo uso de la Distancia Euclidea
*/
double distEuclidea(std::vector<double> usu1, std::vector<double> usu2, double min) {
    const double mediaUsu1 = calcularMedia(usu1, usu1, min);
    const double mediaUsu2 = calcularMedia(usu2, usu1, min);
    
    double sum = 0.0;
    double resultadoEuclid = 0.0;
    for (int i = 0; i < usu1.size(); i++) {
        if (usu1[i] == min -1 && usu2[i] == min - 1) {
            return -2;
        }
        if(usu1[i] != min - 1 && usu2[i] != min - 1) {
            sum += pow(usu1[i] - usu2[i],2);
        }
    }
    resultadoEuclid = sqrt(sum);
    return 1 / resultadoEuclid;
    // return (sqrt(sumDenominadorUsu1) * sqrt(sumDenominadorUsu2));
}
