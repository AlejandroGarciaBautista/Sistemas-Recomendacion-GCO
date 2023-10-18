#include "../includes/Metricas/Metricas.h"

/**
 * Calculamos la similitud entre dos usuarios haciendo uso de la Distancia Coseno
*/
double distCoseno(std::vector<double> usu1, std::vector<double> usu2, double MIN) {
    double sumNumerador = 0.0;
    double sumDenominadorUsu1 = 0.0;
    double sumDenominadorUsu2 = 0.0;
    double resultado = 0.0;
    for (int i = 0; i < usu1.size(); i++) {
        if(usu1[i] != MIN - 1 && usu2[i] != MIN - 1) {
            sumNumerador += (usu1[i]*usu2[i]);
            sumDenominadorUsu1 += pow(usu1[i],2);
            sumDenominadorUsu2 += pow(usu2[i],2);
        }
    }
    return (sumNumerador / (sqrt(sumDenominadorUsu1) * sqrt(sumDenominadorUsu2)));
}
