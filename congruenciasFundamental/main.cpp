#include <stdlib.h>
#include <iostream>
#include <string>
#include "vonNeumann.hpp"
#include "monobits.hpp"
#include "chiCuadrado.hpp"

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
    unsigned int* v = vonNeumann(k, x);
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
    unsigned int* y = NULL;
    unsigned int* z = NULL;
    a = 0; // Conserva la posición del array
    for (i = 0; i < n; i++) {
        c = 1; // Cantidad de dígitos de w[i]
        k = 10; // Representa 10 ^ c
        while (k <= w[i]) {
            k *= 10;
            c++;
        }
        // Para operar correctamente con realloc, debe alternarse los punteros
        if (i % 2) {
            z = (unsigned int*) realloc(y, (a + c) * sizeof(unsigned int));
        } else {
            y = (unsigned int*) realloc(z, (a + c) * sizeof(unsigned int));
        }
        // Se imprimen cada uno de los dígitos de los números generados, excepto el último dígito
        for (x = k; x > 10; x /= 10) {
            m = w[i] % x;
            m *= 10;
            m /= x;
            (i % 2) ? (z[a] = m) : (y[a] = m); // Se alterna la igualdad según si i es impar o no
            cout << m << ' ';
            a++;
        }
        // Como el último dígito se puede obtener con una operación sencilla, se pone fuera del bucle
        m = w[i] % 10;
        (i % 2) ? (z[a] = m) : (y[a] = m); // Se alterna la igualdad según si i es impar o no
        // Además, en este programa se realiza un salto de línea para distinguir los números generados
        cout << m << endl;
        a++;
    }
    if (n % 2) z = (unsigned int*) realloc(y, a * sizeof(unsigned int));
    argumento = (monobits(a,z))
        ? "Ha pasado la prueba de monobits."
        : "No ha pasado la prueba de monobits.";
    cout << argumento << endl;
    argumento = (chiCuadrado(a,z))
        ? "Ha pasado la prueba de chi cuadrado."
        : "No ha pasado la prueba de chi cuadrado.";
    cout << argumento << endl;
    free(z);
    return 0;
}
