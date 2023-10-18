#include <vector>
#include <cmath>

double calcularMedia (std::vector<double> usu, double MIN) {
    int calificados = 0;
    double suma_calificaciones = 0.0;
    for(int i = 0; i < usu.size(); i++) {
        if (usu[i] != MIN - 1) {
            calificados++;
            suma_calificaciones += usu[i];
        }
    }
    return calificados = 0 ? 0 : suma_calificaciones/calificados;
};


double coefCorrel(std::vector<double> usu1, std::vector<double> usu2, double MIN) {
    double mediaUsu1 = calcularMedia(usu1,MIN);
    double mediaUsu2 = calcularMedia(usu2,MIN);
    double sumNumerador = 0.0;
    double sumDenominadorUsu1 = 0.0;
    double sumDenominadorUsu2 = 0.0;
    double resultado = 0.0;
    for (int i = 0; i < usu1.size(); i++) {
        if(usu1[i] != MIN - 1 && usu2[i] != MIN - 1) {
            sumNumerador += ((usu1[i]-mediaUsu1)*(usu2[i]-mediaUsu2));
            sumDenominadorUsu1 += pow(((usu1[i]-mediaUsu1)),2);
            sumDenominadorUsu2 += pow(((usu2[i]-mediaUsu2)),2);
        }
    }
    return (sumNumerador / (sqrt(sumDenominadorUsu1) * sqrt(sumDenominadorUsu2)));
};

