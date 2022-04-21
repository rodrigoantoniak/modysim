#include <stdlib.h>
#include <iostream>
#include <string>

double atof(char*);

double itof(int);

int ftoi(double);

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
    double m;
    int w[argc - 4];
    double v[argc - 4];
    for (c = 4; c < argc; c++) {
        w[c - 4] = atoi(argv[c]);
        v[c - 4] = atof(argv[c]);
    }
    a = atoi(argv[1]);
    c = atoi(argv[2]);
    m = atof(argv[3]);
    if (a >= m) {
        cout << "Error: el modulo es menor o igual a la primera semilla." << endl;
        return 1;
    }
    int i, u, z;
    double d, y;
    for (i = 0; i < argc - 4; i++) {
        if (w[i] >= ftoi(m)) {
            cout << "Error: el elemento " + to_string(i)
                    + " de la sucesion es mayor o igual al modulo." << endl;
            return 1;
        }
        z = i + argc - 5;
        u = z % (argc - 4);
        y = itof(w[u]);
        w[i] = (a * w[u] + c * w[i]) % ftoi(m);
        d = (itof(a) * y + itof(c) * itof(w[i])) / m;
        while (d >= 1) {
            d -= 1;
        }
        v[i] = d;
    }
    for (i = 0; i < argc - 4; i++) {
        cout << v[i] << endl;
    }
    return 0;
}

double atof(char* entrada) {
    return static_cast<double>(atoi(entrada));
}

double itof(int entrada) {
    return static_cast<double>(entrada);
}

int ftoi(double entrada) {
    return static_cast<int>(entrada);
}
