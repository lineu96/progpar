/*-------------------------------------------------*/

/* Programação Paralela - Período Especial 2020/2  */
/* OBTENÇÃO DO VALOR DE PI VIA INTEGRAL DEFINIDA   */
/* SEM CONSTRUÇÃO omp for*/

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
    // tempo de execução

    double start;
    double end;
    start = omp_get_wtime();

    /*=========================================================*/

    // VARIÁVEIS
    double vet[num_steps]; // vetor para armazenar as áreas
    double pi; // variavel para o valor final de pi
    int i; // variavel de controle para laços
    int n_threads; // variavel para definir numero de threads;

    /*=========================================================*/

    step = 1.0/(double) num_steps; // tamanho do passo

    /*=========================================================*/

    // NUMERO DE THREADS
    n_threads = 4; // numero de threads
    omp_set_num_threads(n_threads); // define numero de threads em n_threads

    /*=========================================================*/

    // REGIÃO PARALELA

    # pragma omp parallel
    {
        int i; // variavel de controle para laços
        int id; // identificador de threads
        double x; // valor de x para a função

        id = omp_get_thread_num(); // identificando as threads

        // FOR PARALELO PARA OBTENÇÃO DAS 1000000 PARTES

        for (i=id; i<num_steps; i+=n_threads) // laço de id ate o numero de passos menos o last de cada thread
        {
            x = (i + 0.5) * step;
            vet[i] = (4.0 / (1.0 + x*x))*step;
        }
    } // fim da região paralela

    /*=========================================================*/

    // Soma de todas as partes (sequencial)
    for (i=0;i< num_steps; i++){
        pi = pi + vet[i]; // Sum += Área do retângulo
        }

    /*=========================================================*/

    printf("=======================================\n");
    printf("pi = %f\n", pi);
    printf("Numero de threads: %d\n", n_threads);
    end = omp_get_wtime();
    printf("Tempo de execução: %f sec. time.\n", end-start);
    printf("=======================================\n");

    /*=========================================================*/
}
