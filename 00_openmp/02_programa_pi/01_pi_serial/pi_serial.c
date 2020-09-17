/*-------------------------------------------------*/

/* Programação Paralela - Período Especial 2020/2  */
/* OBTENÇÃO DO VALOR DE PI VIA INTEGRAL DEFINIDA   /*
/* VERSÃO SERIAL FORNECIDA PELO PROFESSOR*/

/*-------------------------------------------------*/

#include <stdio.h>

static long num_steps = 100000;
double step;

int main () {
    int i; double x, pi, sum = 0.0;

    step = 1.0/(double) num_steps;

    for (i=0;i< num_steps; i++){
        x = (i + 0.5) * step; // Largura do retângulo
        sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo
}
    pi = step * sum;

    printf("pi = %f", pi);
}
