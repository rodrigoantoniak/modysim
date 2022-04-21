#include <stdlib.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    using namespace std;
    if (argc != 3) {
        cout << "Error: se debe ingresar una semilla y la cantidad de numeros aleatorios a generar." << endl;
        return 1;
    }
    int n, x;
    string argumento;
    for (x = 1; x < 3; x++) {
        argumento.assign(argv[x]);
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
    argumento.assign(argv[1]);
    if (argumento.length() != 4) {
        cout << "Error: la semilla no es un número natural de cuatro dígitos." << endl;
        return 1;
    }
    x = atoi(argv[1]);
    n = atoi(argv[2]);
    int i, y, z;
    for (i = 0; i < n; i++) {
        while (x % 100 == 0) {
            y = i % 99;
            y += 1;
            x += y;
            z = x * x;
            z %= 100;
        }
        y = x * x;
        y %= 1000000;
        y /= 100;
        for (x = 10000; x > 10; x /= 10) {
            z = y % x;
            z *= 10;
            z /= x;
            cout << z << ' ';
        }
        z = y % 10;
        cout << z << endl;
        x = y;
    }
    return 0;
}
