#include <stdlib.h>
#include <climits>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include "vonNeumann.hpp"
#include "monobits.hpp"
#include "chiCuadrado.hpp"

int main(int argc, char* argv[]) {
    using namespace std;
    // Primero, debe controlarse que los argumentos adicionales ingresados sean dos.
    if (argc != 5) {
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
    char* puntero;
    double infe, supe;
    for (x = 3; x < 5; x++) {
        // Se asigna el valor en string a double a la variable que corresponda
        (x == 3) ? (infe = strtod(argv[x], &puntero)) : (supe = strtod(argv[x], &puntero));
        // Para asegurar que los argumentos son números de coma flotante, se comprueba el puntero
        if ((puntero[0] != 0) || (regex_match(puntero, regex("[+\-]?((0)*(\.)(0)+|(0)+)")))) {
            argumento = (x == 3)
                ? "Error: el valor que representa el límite inferior no es válido."
                : "Error: el valor que representa el límite superior no es válido.";
            cout << argumento << endl;
            return 1;
        }
    }
    if (infe >= supe) {
        cout << "Error: el valor inferior no es menor que el superior." << endl;
        return 1;
    }
    n = (unsigned int)d; // Casteo seguro
    x = (unsigned int)b; // Casteo seguro
    unsigned int i;
    unsigned int* v = vonNeumann(n, x); // Vector con los números aleatorios
    // En el bucle, se extrae todos los dígitos de v; poniéndolos en w
    unsigned int w[n];
    unsigned int y;
    for (i = 0; i < n; i++) {
        x = 10000;
        // Se imprimen cada uno de los dígitos de los números generados, excepto el último dígito
        // También existe un corte en caso de generar los números necesarios
        while ((x > 10) && (i < n)) {
            y = v[i/4] % x;
            y *= 10;
            y /= x;
            w[i] = y;
            i++;
            x /= 10;
        }
        // Si se llega al caso de corte, se imprime un salto de línea y se termina la impresión de dígitos
        if (i == n) break;
        // Como el último dígito se puede obtener con una operación sencilla, se pone fuera del bucle
        y = v[i/4] % 10;
        w[i] = y;
    }
    double dife = supe - infe;
    double res;
    for (i = 0; i < n; i++) {
        res = infe + (double(w[i]) * dife / 10.0);
        cout << setprecision(10) << res << endl;
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
