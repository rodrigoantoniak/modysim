#ifndef MONOBITS_HPP_INCLUDED
#define MONOBITS_HPP_INCLUDED

#include <math.h>

bool monobits(unsigned int n, unsigned int* x) {
    unsigned int i;
    int u = 0;
    for(i = 0; i < n; i++) {
        (x[i] / 5) ? u++ : u--; // Suma si el número está entre 5 y 9, sino resta
    }
    double mb = (double)(u * u) / (double)(n * 2); // Este resultado está garantizado de ser positivo
    // Por último, se utiliza la función de error complementario de la raíz cuadrada de mb
    // Como mb representa el cuadrado de z, se realiza la raíz cuadrada para obtener z
    return (erfc(sqrt(mb)) >= 0.01) ? true : false;
}

#endif // MONOBITS_HPP_INCLUDED
