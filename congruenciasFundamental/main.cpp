#include <stdlib.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    using namespace std;
    if (argc < 5) {
        cout << "Error: se debe ingresar dos semillas fijas, un modulo y una sucesion de numeros aleatorios." << endl;
        return 1;
    }
    int a, c;
    string argumento;
    for (c = 1; c < 4; c++) {
        argumento.assign(argv[c]);
        for (a = 0; a < argumento.length(); a++) {
            if ((argumento[a] < '0') || (argumento[a] > '9')) {
                argumento = (c == 3)
                    ? "Error: el modulo no es un numero natural."
                    : "Error: la semilla " + to_string(c) + " no es un numero natural.";
                cout << argumento << endl;
                return 1;
            }
        }
    }
    for (c = 4; c < argc; c++) {
        argumento.assign(argv[c]);
        for (a = 0; a < argumento.length(); a++) {
            if ((argumento[a] < '0') || (argumento[a] > '9')) {
                cout << "Error: el elemento " + to_string(c)
                    + " de la sucesion no es un numero natural." << endl;
                return 1;
            }
        }
    }
    int m;
    int v[argc - 4];
    for (c = 4; c < argc; c++) {
        v[c - 4] = atoi(argv[c]);
    }
    a = atoi(argv[1]);
    c = atoi(argv[2]);
    m = atoi(argv[3]);
    if (a >= m) {
        cout << "Error: el modulo es menor o igual a la primera semilla." << endl;
        return 1;
    }
    int i, y, z;
    for (i = 0; i < argc - 4; i++) {
        if (v[i] >= m) {
            cout << "Error: el elemento " + to_string(i)
                    + " de la sucesion es mayor o igual al modulo." << endl;
            return 1;
        }
        y = i + argc - 5;
        z = y % (argc - 4);
        y = v[z];
        z = (a * y + c * v[i]) % m;
        v[i] = z;
    }
    for (i = 0; i < argc - 4; i++) {
        cout << v[i] << endl;
    }
    return 0;
}
