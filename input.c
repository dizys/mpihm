#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "global.h"
#include "mpi_helper.h"

void input_get_file_paths(int argc, char* argv[]){
    g_argc = &argc;
    g_argv = &argv;
    if(argc > 1)
        g_input_file = argv[1];
    else
        g_input_file = "in.txt";
    if(argc > 2)
        g_output_file = argv[2];
    else
        g_output_file = "out.txt";
}

void input_init(int argc, char* argv[]){
    input_get_file_paths(argc, argv);
}

void input_read_data(){
    g_n = 0;
    FILE* input_file = fopen(g_input_file, "r");
    if(input_file == NULL){
        printf("\033[41;30m Fatal Error: %s file not found.\033[0m\n", g_input_file);
        mpi_helper_abort();
        return;
    }
    int tmp, count = 0;
    while (fscanf(input_file, "%d", &tmp) != EOF)
        count++;
    if(count % g_comm_size != 0){
        printf("\033[41;30m Fatal Error: The number of numbers must be a multiple of %d (the number of processes).\033[0m\n", g_comm_size);
        mpi_helper_abort();
        return;
    }
    g_n = count;
    count = 0;
    g_alloc_data(g_n);
    rewind(input_file);
    while (fscanf(input_file, "%d", &tmp) != EOF)
        g_data[count++] = tmp;
}