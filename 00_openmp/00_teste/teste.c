#include <stdio.h>
# include <omp.h>


int main ()
{

    printf("\nNumero de processadores: %i\n\n", omp_get_num_procs());

}
