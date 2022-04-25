#include <stdlib.h>
#include "vonNeumann.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    using namespace std;
    // Primero, debe controlarse que los argumentos adicionales ingresados sean seis.
    if (argc != 7) {
        cout << "Error: se debe ingresar los seis argumentos adicionales al programa." << endl;
        return 1;
    }
    unsigned int a, c;
    string argumento;
    for (c = 1; c < 7; c++) {
        // Se prefiere el uso de assign antes que '=' para denotar que argv[x] es de un tipo distinto que argumento
        argumento.assign(argv[c]);
        for (a = 0; a < argumento.length(); a++) {
            // Para asegurar que los argumentos son números enteros no negativos, se comprueba que los caracteres sean [0;9]
            if ((argumento[a] < '0') || (argumento[a] > '9')) {
                switch (c) {
                    case 3:
                        argumento = "Error: la cantidad de números anteriores necesarios no es un numero natural.";
                        break;
                    case 4:
                        argumento = "Error: el modulo no es un numero natural.";
                        break;
                    case 5:
                        argumento = "Error: la cantidad de números aleatorios a generar no es un numero natural.";
                        break;
                    case 6:
                        argumento = "Error: la semilla para los números anteriores a generar no es un numero natural.";
                        break;
                    default:
                        argumento = "Error: la semilla " + to_string(c) + " no es un numero natural.";
                }
                cout << argumento << endl;
                return 1;
            }
        }
    }
    unsigned int k, m, n, x;
    a = atoi(argv[1]);
    c = atoi(argv[2]);
    k = atoi(argv[3]);
    m = atoi(argv[4]);
    n = atoi(argv[5]);
    x = atoi(argv[6]);
    if (!(a && c && k && m && n && x)) {
        cout << "Error: ninguno de los números puede ser igual a cero." << endl;
        return 1;
    }
    unsigned int* v = vonNeumann(k, x);
    if (a >= m) {
        cout << "Error: el modulo es menor o igual a la primera semilla." << endl;
        return 1;
    }
    if (k > n) {
        cout << "Error: la cantidad de números anteriores es mayor a los números aleatorios a generar." << endl;
        return 1;
    }
    if ((x < 1000) || (x > 9999)) {
        cout << "Error: la semilla para los números anteriores a generar no es un número natural de cuatro dígitos." << endl;
        return 1;
    }
    unsigned int w[n];
    // Lo siguiente no se realiza dentro del bucle porque obtiene valores distintos a los utilizados
    // Si bien, es posible ubicarlos dentro del bucle; lo haría menos óptimo al ejecutar
    if (v[0] >= m) {
        cout << "Error: el elemento 1 de la sucesion es mayor o igual al modulo." << endl;
        return 1;
    }
    // Se almacena el número generado dentro de un vector
    w[0] = (a * v[k] + c * v[0]) % m;
    // Después se realiza las mismas operaciones que se encuentran desde el comentario inmediato anterior
    // Este bucle trabaja con los k valores anteriores (después de la primera iteración)
    unsigned int i;
    for (i = 1; i < k; i++) {
        if (v[i] >= m) {
            cout << "Error: el elemento " + to_string(i+1)
                    + " de la sucesion es mayor o igual al modulo." << endl;
            return 1;
        }
        w[i] = (a * w[i-1] + c * v[i]) % m;
    }
    // Una vez utilizados los k valores anteriores, se utiliza el vector con los valores finales generados
    for (i = 0; i < n-k; i++) {
        if (w[k+i-1] >= m) {
            cout << "Error: el elemento " + to_string(k+i+1)
                    + " de la sucesion es mayor o igual al modulo." << endl;
            return 1;
        }
        w[k+i] = (a * w[k+i-1] + c * w[i]) % m;
    }
    // Por último, se imprimirán los valores aleatorios obtenidos (no cuentan los primeros k valores)
    // Actualmente, no se agregan ceros a la izquierda de los números enteros
    // Para esto último, se necesita obtener el número con mayor cantidad de dígitos en un recorrido del vector
    for (i = 0; i < n; i++) {
        k = 1;
        while (k < w[i]) {
            k *= 10;
        }
        for (x = k; x > 10; x /= 10) {
            m = w[i] % x;
            m *= 10;
            m /= x;
            cout << m << ' ';
        }
        m = w[i] % 10;
        cout << m << endl;
    }
    return 0;
}
