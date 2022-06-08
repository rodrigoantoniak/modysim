#include <stdlib.h>
#include <climits>
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
    unsigned long b = strtoul(argv[1], NULL, 10); // Esta función es más segura
    unsigned long d = strtoul(argv[2], NULL, 10); // Esta función es más segura
    unsigned long e = strtoul(argv[3], NULL, 10); // Esta función es más segura
    unsigned long f = strtoul(argv[4], NULL, 10); // Esta función es más segura
    unsigned long g = strtoul(argv[5], NULL, 10); // Esta función es más segura
    unsigned long h = strtoul(argv[6], NULL, 10); // Esta función es más segura
    if (!(b && d && e && f && g && h)) {
        cout << "Error: ninguno de los números puede ser igual a cero." << endl;
        return 1;
    }
    if (b >= f) {
        cout << "Error: el modulo es menor o igual a la primera semilla." << endl;
        return 1;
    }
    if (e > g) {
        cout << "Error: la cantidad de números anteriores es mayor a los números aleatorios a generar." << endl;
        return 1;
    }
    if ((h < 1000) || (h > 9999)) {
        cout << "Error: la semilla para los números anteriores a generar no es un número natural de cuatro dígitos." << endl;
        return 1;
    }
    if (d > UINT_MAX) { // Asegura que d puede transformarse en unsigned int
        cout << "Error: la cantidad de números aleatorios a generar es muy grande." << endl;
        return 1;
    }
    if (f > UINT_MAX) { // Asegura que f puede transformarse en unsigned int
        cout << "Error: la cantidad de números aleatorios a generar es muy grande." << endl;
        return 1;
    }
    if (g > UINT_MAX) { // Asegura que g puede transformarse en unsigned int
        cout << "Error: la cantidad de números aleatorios a generar es muy grande." << endl;
        return 1;
    }
    a = (unsigned int)b; // Casteo seguro
    c = (unsigned int)d; // Casteo seguro
    unsigned int k = (unsigned int)e; // Casteo seguro
    unsigned int m = (unsigned int)f; // Casteo seguro
    unsigned int n = (unsigned int)g; // Casteo seguro
    unsigned int x = (unsigned int)h; // Casteo seguro
    unsigned int j = 1; // Contador de dígitos
    unsigned int p = 10; // 10 ^ j
    unsigned int q; // Almacena cada semilla nueva para conteo de dígitos
    unsigned int r; // Cantidad máxima de dígitos
    unsigned int* v = vonNeumann(k, x);
    // Lo siguiente no se realiza dentro del bucle porque obtiene valores distintos a los utilizados
    // Si bien, es posible ubicarlos dentro del bucle; lo haría menos óptimo al ejecutar
    if (v[0] >= m) {
        cout << "Error: el elemento 1 de la sucesion es mayor o igual al modulo." << endl;
        return 1;
    }
    // Se almacena el número generado dentro de q
    q = (a * v[(k+(k%4))/4] + c * v[0]) % m;
    while (p <= q) {
        p *= 10;
        j++;
    }
    unsigned int* y = (unsigned int*) malloc(sizeof(unsigned int));
    y[0] = q;
    unsigned int* w = NULL; // w se usará como puntero alternativo a y
    // Después se realiza las mismas operaciones que se encuentran desde el comentario inmediato anterior
    // Este bucle trabaja con los k valores anteriores (después de la primera iteración)
    unsigned int i = 1; // Contador de semillas
    while ((i < (k+(k%4))/4) && (i*j < n)) {
        if (v[i] >= m) {
            cout << "Error: el elemento " + to_string(i+1)
                    + " de la sucesion es mayor o igual al modulo." << endl;
            return 1;
        }
        // Se almacena el número generado dentro de q
        q = (i % 2)
            ? (a * y[i-1] + c * v[i]) % m
            : (a * w[i-1] + c * v[i]) % m;
        while (p <= q) {
            p *= 10;
            j++;
        }
        // Para operar correctamente con realloc, debe alternarse los punteros
        if (i % 2) {
            w = (unsigned int*) realloc(y, (i+1) * sizeof(unsigned int));
            w[i] = q;
        } else {
            y = (unsigned int*) realloc(w, (i+1) * sizeof(unsigned int));
            y[i] = q;
        }
        i++;
    }
    // Una vez utilizados los k valores anteriores, se utiliza el vector con los valores finales generados
    while (i*j < n) {
        if (w[i-((k+(k%4))/4)] >= m) {
            cout << "Error: el elemento " + to_string(i+1)
                    + " de la sucesion es mayor o igual al modulo." << endl;
            return 1;
        }
        // Se almacena el número generado dentro de q
        q = (i % 2)
            ? (a * y[i-1] + c * w[i-((k+(k%4))/4)]) % m
            : (a * w[i-1] + c * w[i-((k+(k%4))/4)]) % m;
        while (p <= q) {
            p *= 10;
            j++;
        }
        // Para operar correctamente con realloc, debe alternarse los punteros
        if (i % 2) {
            w = (unsigned int*) realloc(y, (i+1) * sizeof(unsigned int));
            w[i] = q;
        } else {
            y = (unsigned int*) realloc(w, (i+1) * sizeof(unsigned int));
            y[i] = q;
        }
        i++;
    }
    if (n % 2) w = (unsigned int*) realloc(y, i * sizeof(unsigned int));
    unsigned int z[n];
    a = 0; // Conserva la posición del array
    for (c = 0; c < i-1; c++) {
        // Se imprimen cada uno de los dígitos de los números generados, excepto el último dígito
        for (x = p; x > 10; x /= 10) {
            m = w[c] % x;
            m *= 10;
            m /= x;
            z[a] = m;
            cout << m << ' ';
            a++;
        }
        // Como el último dígito se puede obtener con una operación sencilla, se pone fuera del bucle
        m = w[c] % 10;
        z[a] = m;
        // Además, en este programa se realiza un salto de línea para distinguir los números generados
        cout << m << endl;
        a++;
    }
    x = p;
    while (a < n) {
        m = w[i-1] % x;
        m *= 10;
        m /= x;
        z[a] = m;
        cout << m << ' ';
        a++;
        x /= 10;
    }
    cout << endl;
    argumento = (monobits(a,z))
        ? "Ha pasado la prueba de monobits."
        : "No ha pasado la prueba de monobits.";
    cout << argumento << endl;
    argumento = (chiCuadrado(a,z))
        ? "Ha pasado la prueba de chi cuadrado."
        : "No ha pasado la prueba de chi cuadrado.";
    cout << argumento << endl;
    free(w); // Con esto, y se libera también
    return 0;
}
