#include <stdlib.h>
#include <climits>
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
    unsigned long b = strtoul(argv[1], NULL, 10); // Esta función es más segura
    unsigned long d = strtoul(argv[2], NULL, 10); // Esta función es más segura
    if ((b < 1000) || (b > 9999)) { // Asegura también que b puede transformarse en unsigned int
        cout << "Error: la semilla no es un número natural de cuatro dígitos." << endl;
        return 1;
    }
    if (!(d)) {
        cout << "Error: la cantidad de números aleatorios a generar no puede ser cero." << endl;
        return 1;
    }
    if (d > UINT_MAX) { // Asegura que d puede transformarse en unsigned int
        cout << "Error: la cantidad de números aleatorios a generar es muy grande." << endl;
        return 1;
    }
    n = (unsigned int)d; // Casteo seguro
    x = (unsigned int)b; // Casteo seguro
    unsigned int i, y;
    unsigned int v[(n+(n%4))/4];
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
    unsigned int w[n];
    unsigned int z;
    for (i = 0; i < n; i++) {
        x = 10000;
        // Se imprimen cada uno de los dígitos de los números generados, excepto el último dígito
        // También existe un corte en caso de generar los números necesarios
        while ((x > 10) && (i < n)) {
            y = v[i/4] % x;
            y *= 10;
            y /= x;
            w[i] = y;
            cout << y << ' ';
            i++;
            x /= 10;
        }
        // Si se llega al caso de corte, se imprime un salto de línea y se termina la impresión de dígitos
        if (i == n) {
            cout << endl;
            break;
        }
        // Como el último dígito se puede obtener con una operación sencilla, se pone fuera del bucle
        y = v[i/4] % 10;
        w[i] = y;
        // Además, en este programa se realiza un salto de línea para distinguir las cifras cada 4 dígitos
        cout << y << endl;
    }
    argumento = (monobits(n,w))
        ? "Ha pasado la prueba de monobits."
        : "No ha pasado la prueba de monobits.";
    cout << argumento << endl;
    argumento = (chiCuadrado(n,w))
        ? "Ha pasado la prueba de chi cuadrado."
        : "No ha pasado la prueba de chi cuadrado.";
    cout << argumento << endl;
    return 0;
}
