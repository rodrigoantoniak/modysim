#ifndef VONNEUMANN_HPP_INCLUDED
#define VONNEUMANN_HPP_INCLUDED

unsigned int* vonNeumann(unsigned int n, unsigned int x) {
    unsigned int* aleatorios = new unsigned int[(n+(n%4))/4];
    unsigned int i, y;
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
        // Aquí se comprueba que la semilla no termine en 00
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
        // Se guarda el número obtenido dentro de los resultados
        aleatorios[i] = y;
        // Por último, el número generado es la nueva semilla
        x = y;
    }
    return aleatorios;
}

#endif // VONNEUMANN_HPP_INCLUDED
