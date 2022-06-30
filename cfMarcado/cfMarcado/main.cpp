#include <stdlib.h>
#include <climits>
#include <iomanip>
#include <iostream>
#include <string>
#include "congruenciasFundamental.hpp"
#include "monobits.hpp"
#include "chiCuadrado.hpp"

int main(int argc, char* argv[]) {
    using namespace std;
    // Primero, debe controlarse que los argumentos adicionales ingresados sean seis.
    if (argc != 9) {
        cout << "Error: se debe ingresar los ocho argumentos adicionales al programa." << endl;
        return 1;
    }
    unsigned int a, c, x;
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
    char* puntero;
    double infe, supe;
    for (x = 7; x < 9; x++) {
        // Se asigna el valor en string a double a la variable que corresponda
        (x == 7) ? (infe = strtod(argv[x], &puntero)) : (supe = strtod(argv[x], &puntero));
        // Para asegurar que los argumentos son números de coma flotante, se comprueba el puntero
        if (puntero[0] != 0) {
            argumento = (x == 7)
                ? "Error: el valor que representa el límite inferior no es válido."
                : "Error: el valor que representa el límite superior no es válido.";
            cout << argumento << endl;
            return 1;
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
    if (infe >= supe) {
        cout << "Error: el valor inferior no es menor que el superior." << endl;
        return 1;
    }
    a = (unsigned int)b; // Casteo seguro
    c = (unsigned int)d; // Casteo seguro
    unsigned int k = (unsigned int)e; // Casteo seguro
    unsigned int m = (unsigned int)f; // Casteo seguro
    unsigned int n = (unsigned int)g; // Casteo seguro
    x = (unsigned int)h; // Casteo seguro
    unsigned int i;
    unsigned int j = 1; // Contador de dígitos
    unsigned int p = 10; // 10 ^ j
    unsigned int q; // Almacena cada semilla nueva para conteo de dígitos
    unsigned int r; // Cantidad máxima de dígitos
    unsigned int* v = congruenciasFundamental(a, c, k, m, n, x);
    double dife = supe - infe;
    double res;
    for (i = 0; i < n; i++) {
        res = infe + (double(v[i]) * dife / 10.0);
        cout << setprecision(10) << res << endl;
    }
    argumento = (monobits(n,v))
        ? "Ha pasado la prueba de monobits."
        : "No ha pasado la prueba de monobits.";
    cout << argumento << endl;
    argumento = (chiCuadrado(n,v))
        ? "Ha pasado la prueba de chi cuadrado."
        : "No ha pasado la prueba de chi cuadrado.";
    cout << argumento << endl;
    return 0;
}
