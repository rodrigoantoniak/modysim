#ifndef CONGRUENCIASFUNDAMENTAL_HPP_INCLUDED
#define CONGRUENCIASFUNDAMENTAL_HPP_INCLUDED

#include "vonNeumann.hpp"

unsigned int* congruenciasFundamental
    (unsigned int a, unsigned int c, unsigned int k, unsigned int m, unsigned int n, unsigned int x)
{
    using namespace std;
    unsigned int j = 1; // Contador de dígitos
    unsigned int p = 10; // 10 ^ j
    unsigned int q; // Almacena cada semilla nueva para conteo de dígitos
    unsigned int r; // Cantidad máxima de dígitos
    unsigned int* v = vonNeumann(k, x);
    // Lo siguiente no se realiza dentro del bucle porque obtiene valores distintos a los utilizados
    // Si bien, es posible ubicarlos dentro del bucle; lo haría menos óptimo al ejecutar
    if (v[0] >= m) {
        cout << "Error: el elemento 1 de la sucesion es mayor o igual al modulo." << endl;
        return NULL;
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
            return NULL;
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
            return NULL;
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
    unsigned int d, e, f;
    unsigned int b = 0; // Conserva la posición del array
    unsigned int* z = new unsigned int[n];
    for (d = 0; d < i-1; d++) {
        // Se imprimen cada uno de los dígitos de los números generados, excepto el último dígito
        for (f = p; f > 10; f /= 10) {
            e = w[d] % f;
            e *= 10;
            e /= f;
            z[b] = e;
            b++;
        }
        // Como el último dígito se puede obtener con una operación sencilla, se pone fuera del bucle
        e = w[d] % 10;
        z[b] = e;
        b++;
    }
    f = p;
    while (b < n) {
        e = w[i-1] % f;
        e *= 10;
        e /= f;
        z[b] = e;
        b++;
        f /= 10;
    }
    return z;
}

#endif // CONGRUENCIASFUNDAMENTAL_HPP_INCLUDED
