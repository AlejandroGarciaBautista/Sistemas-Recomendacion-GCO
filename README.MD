# ***Sistema de Recomendación. Métodos de de filtrado colaborativo***
## Práctica de Laboratorio para Gestión del Conocimiento en las Organizaciones
## _Autores_
- Adrián González Expósito (alu0101404813@ull.edu.es)
- Lucas Pérez Rosario (alu0101399928@ull.edu.es)
- Alejandro García Bautista (alu0101387604@ull.edu.es)

# Como esta organizado el código
El código esta organizad en los siguientes directorios:

```bash
.
├── build --> Aqui encontramos el ejecutable y los ficheros de prueba
└── src --> Aquí tendremos todo el codigo fuente del programa
    └── includes --> Aqui encontramos todos los ficheros .h de nuestro programa
        ├── Metricas
        └── Predicciones
    ├── Metricas --> Aquí tenemos todo los ficheros .cc de las metricas a usar
    ├── Predicciones --> Aquí tenemos todos los ficheros .cc de las predicciones a user

```

# ¿Qué se encontrará en el repositorio?
En el repositorio actual se encontrará todo el código fuente necesario así como el fichero Makefile para poder realizar la compilación haciendo uso unicamente del comando make, dentro del directorio build/ se enctraran varios ejemplos con lo que realizar la ejecución del programa

# Como se compila el programa
Para poder compilar el programa hay que estar situado en el directorio build/ y ejecutar el comando ***make***, con esto se generara un ejecutable que se llama _sistemas_recomendacion_, para conocer el uso del programa se puede ejecutar ***./sistemas_recomendacion --help*** aunque que su uso se explicara en el siguiente apartado.

# Como se usa el programa
Para poder hacer uso del programa debemos ejecutar el siguiente comando: __./sistemas_recomendacion -f <fichero> -m <metrica> -v <vecinos> -p <prediccion>__

Como se indicaba en el enunciado de la practica se nombra que los argumentos sean del tipo POSIX es por eso que el anterior ejemplo de tipo de uso del programa es solo un ejemplo de las posibles combinaciones que se pueden hacer ya que los argumentos se pueden indicar en el orden que se desee, así como usar su versión larga que serian --fichero/--metrica/--vecinos/--prediccion, asi como mezclar algunos argumentos en su forma larga y otro en su forma corta.

En la opción -f debemos indicar la ruta al fichero donde tenemos la matriz que queremos completar.
En la opción -m debemos indicar uno de las siguientes Métricas haciendo uso de su número identificativo:

    1. Correlación de Perason
    2. Distancia Coseno
    3. Distancia Euclidea

En la opción -v se debe indicar el número de vecinos con los que queremos trabajar, es importante que este número no sea mayor al los vecinos existentes.
En la opción -p se debe indicar una de los siguientes métodos de predicción haciendo uso de su número identificativo:

    1. Predicción Simple 
    2. Diferencia con la Media

Un ejemplo de uso de la aplicación puede ser la siguiente:

```bash
./sistemas_recomendacion --fichero utility-matrix-10-25-7.txt -m 1 --vecinos 5 -p 2
```

En el ejemplo estamos haciendo uso del fichero matriz_10X25-7.txt, la métrica para calcular la similitud usamos el Coeficiente de Correlación de Pearson, usamos 5 vecinos y el método de predicción es la Predicción con Diferencia con la media. 