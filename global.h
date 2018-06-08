#include <stdlib.h>
#include <mpi.h>
#ifndef HM_GLOBAL_H
#define HM_GLOBAL_H

int* g_argc;
char*** g_argv;

char* g_input_file;
char* g_output_file;

int g_n;

MPI_Comm g_comm;
int g_comm_size;

int* g_data;
int g_height;

int g_part_size;
int* g_part_receive;
int g_part_rank;
int* g_part_left;
int* g_part_right;
int g_part_height;
int* g_part_merge;

void g_alloc_data(int n);
void g_alloc_part_receive(int size);
void g_alloc_block();
void g_free();

#endif //HM_GLOBAL_H
