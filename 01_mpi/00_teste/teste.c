
# include <stdio.h>
# include <mpi.h>

# define STD_TAG 0

static long num_steps = 100000; // numero de passos
double step; // tamanho do passo

main(int argc, char **argv) {

    // VARIÁVEIS
    double vet[num_steps]; // vetor para armazenar as áreas
    double pi; // variavel para o valor final de pi
    double x; // valor de x para a função

    int i, my_rank, n_procs;

    step = 1.0/(double) num_steps; // tamanho do passo

    for (i=0;i< num_steps; i++){
            vet[i] = 0;
        }

    MPI_Status status;

    /*=========================================================*/

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

    if (my_rank != 0) {

        pi = 0;

        for (i=my_rank-1; i<num_steps; i+=n_procs-1) // laço do rank ate o numero de passos
            {
                x = (i + 0.5) * step;
                vet[i] = (4.0 / (1.0 + x*x))*step;
            }

        for(i=0;i<num_steps;i++)
            {
                pi = pi+vet[i];

            }

        MPI_Send(&pi, 8, MPI_DOUBLE, 0, STD_TAG, MPI_COMM_WORLD);

    } else {

        for (i = 1; i < n_procs; i++){
            MPI_Recv(&pi, 8, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            printf("%f\n", pi);
        }
    }

MPI_Finalize();

}
