/*-------------------------------------------------*/

/* Programação Paralela - Período Especial 2020/2  */
/* OBTENÇÃO DO VALOR DE PI VIA INTEGRAL DEFINIDA   */
/* COM CONSTRUÇÃO omp for*/

/*-------------------------------------------------*/
/* Lineu Alberto Cavazani de Freitas*/
/*-------------------------------------------------*/

/*=========================================================*/

# include <stdio.h>
# include <omp.h>

/*=========================================================*/

static long num_steps = 100000; // numero de passos
double step; // tamanho do passo

/*=========================================================*/

int main () {

    /*=========================================================*/

    // VARIÁVEIS
    double pi;
    double sum = 0.0;
    int n_threads;
    double start;
    double end;

    /*=========================================================*/


    start = omp_get_wtime(); // Início do tempo de execução

    step = 1.0/(double) num_steps; // Tamanho do passo

    n_threads = 4; // numero de threads desejadas

    omp_set_num_threads(n_threads); // define numero de threads em n_threads

    /*=========================================================*/

    // REGIÃO PARALELA

    # pragma omp parallel num_threads(n_threads)
    {
        // Variáveis privadas
        int i;
        double x;

        // construção for com reduction
        # pragma omp for reduction (+:sum)

        for (i=0;i< num_steps; i++){
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x*x);
            }
    } // fim da região paralela

    /*=========================================================*/

    pi = step * sum; // obtenção de pi

    /*=========================================================*/

    // Resultados

    printf("=======================================\n");
    printf("pi = %f\n", pi);
    printf("Numero de threads: %d\n", n_threads);
    end = omp_get_wtime();
    printf("Tempo de execução: %f sec. time.\n", end-start);
    printf("=======================================\n");

    /*=========================================================*/
}
