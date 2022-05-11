#ifndef CHICUADRADO_HPP_INCLUDED
#define CHICUADRADO_HPP_INCLUDED

bool chiCuadrado(unsigned int n, unsigned int* x) {
    unsigned int v[10] = {0};
    unsigned int i;
    for(i = 0; i < n; i++) {
        v[x[i]]++; // Suma la cantidad del dígito que aparece
    }
    double mb = 0;
    for(i = 0; i < 10; i++) {
        // Esta variable sólo sumará valores positivos
        mb += (double(v[i]) - double(n) / double(10)) * (double(v[i]) - double(n) / double(10));
    }
    // Esto es lo mismo que dividir 10 veces sobre (n * 0.1)
    mb /= n;
    // Por último, se compara con la probabilidad de 0.01 para 9 grados de libertad en distribución chi cuadrado
    return (mb < 21.666) ? true : false;
}

#endif // CHICUADRADO_HPP_INCLUDED
