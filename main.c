#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "input.h"
#include "mpi_helper.h"
#include "compute.h"
#include "output.h"

int main(int argc, char* argv[]){
    input_init(argc, argv);
    mpi_helper_init();
    if(mpi_helper_is_master())
        input_read_data();
    mpi_helper_sync_data();
    compute_quick_sort(0, g_part_size - 1);
    mpi_helper_gather_result();
    if(mpi_helper_is_master())
        output_result();
    g_free();
    mpi_helper_finalize();
    return 0;
}