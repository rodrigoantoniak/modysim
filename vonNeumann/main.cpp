#include <stdlib.h>
#include <iostream>
#include <string>
#include "monobits.hpp"
#include "chiCuadrado.hpp"

int main(int argc, char* argv[]) {
    using namespace std;
    // Primero, debe controlarse que los argumentos adicionales ingresados sean dos.
    if (argc != 3) {
        cout << "Error: se debe ingresar una semilla y la cantidad de numeros aleatorios a generar." << endl;
        return 1;
    }
    unsigned int n, x;
    string argumento;
    for (x = 1; x < 3; x++) {
        // Se prefiere el uso de assign antes que '=' para denotar que argv[x] es de un tipo distinto que argumento
        argumento.assign(argv[x]);
        // Para asegurar que los argumentos son números enteros no negativos, se comprueba que los caracteres sean [0;9]
        for (n = 0; n < argumento.length(); n++) {
            if ((argumento[n] < '0') || (argumento[n] > '9')) {
                argumento = (x == 1)
                    ? "Error: la semilla no es no es un numero natural."
                    : "Error: la cantidad de numeros aleatorios a generar no es un numero natural.";
                cout << argumento << endl;
                return 1;
            }
        }
    }
    x = atoi(argv[1]);
    n = atoi(argv[2]);
    if ((x < 1000) || (x > 9999)) {
        cout << "Error: la semilla no es un número natural de cuatro dígitos." << endl;
        return 1;
    }
    if (!(n)) {
        cout << "Error: la cantidad de números aleatorios a generar no puede ser cero." << endl;
        return 1;
    }
    unsigned int i, y;
    unsigned int v[n];
    for (i = 0; i < n; i++) {
        // Aquí se comprueba que la semilla no termine en 00
        // Si es un número entre 0 y 99, se adiciona un número entre 1 y 99 (multiplicado por 100) para más aleatoriedad
        if (x / 100 == 0) {
            // El número a sumar depende de la iteración en que se halle la búsqueda de números pseudoaleatorios
            y = 50 - (i % 49);
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
    unsigned int w[n*4];
    unsigned int z;
    for (i = 0; i < n; i++) {
        // Se imprimen cada uno de los dígitos de los números generados, excepto el último dígito
        z = 0;
        for (x = 10000; x > 10; x /= 10) {
            y = v[i] % x;
            y *= 10;
            y /= x;
            w[(i*4)+z] = y;
            cout << y << ' ';
            z++;
        }
        // Como el último dígito se puede obtener con una operación sencilla, se pone fuera del bucle
        y = v[i] % 10;
        w[(i*4)+3] = y;
        // Además, en este programa se realiza un salto de línea para distinguir las cifras cada 4 dígitos
        cout << y << endl;
    }
    argumento = (monobits(n*4,w))
        ? "Ha pasado la prueba de monobits."
        : "No ha pasado la prueba de monobits.";
    cout << argumento << endl;
    argumento = (chiCuadrado(n*4,w))
        ? "Ha pasado la prueba de chi cuadrado."
        : "No ha pasado la prueba de chi cuadrado.";
    cout << argumento << endl;
    return 0;
}
