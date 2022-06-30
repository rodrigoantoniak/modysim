#include <stdlib.h>
#include <climits>
#include <iostream>
#include <string>
#include "vonNeumann.hpp"
#include "monobits.hpp"
#include "chiCuadrado.hpp"

int main(int argc, char* argv[]) {
    using namespace std;
    // Primero, debe controlarse que los argumentos adicionales ingresados sean dos.
    if (argc != 2) {
        cout << "Error: se debe ingresar la cantidad de numeros aleatorios a generar." << endl;
        return 1;
    }
    unsigned int n;
    string argumento;
    argumento.assign(argv[1]);
        // Para asegurar que los argumentos son números enteros no negativos, se comprueba que los caracteres sean [0;9]
        for (n = 0; n < argumento.length(); n++) {
            if ((argumento[n] < '0') || (argumento[n] > '9')) {
                cout << "Error: la cantidad de numeros aleatorios a generar no es un numero natural." << endl;
                return 1;
            }
        }
    unsigned long d = strtoul(argv[1], NULL, 10); // Esta función es más segura
    if (!(d)) {
        cout << "Error: la cantidad de números aleatorios a generar no puede ser cero." << endl;
        return 1;
    }
    if (d > UINT_MAX) { // Asegura que d puede transformarse en unsigned int
        cout << "Error: la cantidad de números aleatorios a generar es muy grande." << endl;
        return 1;
    }
    n = (unsigned int)d; // Casteo seguro
    unsigned int i, x, y, z;
    unsigned int* v;
    unsigned int w[n];
    bool mono, chi;
    for (z = 1000; z < 10000; z++) {
        v = vonNeumann(n, z);
        x = z;
        for (i = 0; i < (n+(n%4))/4; i++) {
            // Aquí se comprueba que la semilla no termine en 00
            // Si es un número entre 0 y 99, se adiciona un número entre 1 y 99 (multiplicado por 100) para más aleatoriedad
            if (x / 100 == 0) {
                // El número a sumar depende de la iteración en que se halle la búsqueda de números pseudoaleatorios
                y = 100 - (i % 99);
                y -= 1;
                y *= 100;
                x += y;
            }
            // Si es múltiplo de 100, se adiciona un número entre 1 y 99 para cumplir la condición de la semilla
            if (x % 100 == 0) {
                // El número a sumar depende de la iteración en que se halle la búsqueda de números pseudoaleatorios
                y = i % 99;
                y += 1;
                x += y;
            }
            y = x * x;
            y %= 1000000;
            y /= 100;
            // Se almacena el número generado dentro de un vector
            v[i] = y;
            // Por último, el número generado es la nueva semilla
            x = y;
        }
        for (i = 0; i < n; i++) {
            x = 10000;
            // También existe un corte en caso de generar los números necesarios
            while ((x > 10) && (i < n)) {
                y = v[i/4] % x;
                y *= 10;
                y /= x;
                w[i] = y;
                i++;
                x /= 10;
            }
            // Si se llega al caso de corte, se termina la impresión de dígitos
            if (i == n) break;
            // Como el último dígito se puede obtener con una operación sencilla, se pone fuera del bucle
            y = v[i/4] % 10;
            w[i] = y;
        }
        mono = monobits(n,w);
        chi = chiCuadrado(n,w);
        if ((mono) && (chi)) cout << z << endl;
    }
    return 0;
}
