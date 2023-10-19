#include "../includes/Utils.h"

/**
 * Calculamos la similitud entre dos usuarios haciendo uso del Coefficiente de Correlación de Pearson
*/
// double coefCorrel(std::vector<double> usu1, std::vector<double> usu2, double min) {
//     double mediaUsu1 = calcularMedia(usu1,min);
//     double mediaUsu2 = calcularMedia(usu2,min);
//     double sumNumerador = 0.0;
//     double sumDenominadorUsu1 = 0.0;
//     double sumDenominadorUsu2 = 0.0;
//     double resultado = 0.0;
//     for (int i = 0; i < usu1.size(); i++) {
//         if(usu1[i] != min - 1 && usu2[i] != min - 1) {
//             sumNumerador += ((usu1[i]-mediaUsu1)*(usu2[i]-mediaUsu2));
//             sumDenominadorUsu1 += pow(((usu1[i]-mediaUsu1)),2);
//             sumDenominadorUsu2 += pow(((usu2[i]-mediaUsu2)),2);
//         }
//     }
//     return (sumNumerador / (sqrt(sumDenominadorUsu1) * sqrt(sumDenominadorUsu2)));
// }

double coefCorrel(std::vector<double> usu1, std::vector<double> usu2, double min) {
    double mediaUsu1 = calcularMedia(usu1, usu1, min);
    double mediaUsu2 = calcularMedia(usu2, usu1, min);
    double sumNumerador = 0.0;
    double sumDenominadorUsu1 = 0.0;
    double sumDenominadorUsu2 = 0.0;
    double resultado = 0.0;
    for (int i = 0; i < usu1.size(); i++) {
        if(usu1[i] != min - 1 && usu2[i] != min - 1) {
            sumNumerador += ((usu1[i]-mediaUsu1)*(usu2[i]-mediaUsu2));
            sumDenominadorUsu1 += pow(((usu1[i]-mediaUsu1)),2);
            sumDenominadorUsu2 += pow(((usu2[i]-mediaUsu2)),2);
        }
    }
    return (sumNumerador / (sqrt(sumDenominadorUsu1) * sqrt(sumDenominadorUsu2)));
}