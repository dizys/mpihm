#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "mpi_helper.h"
#include "global.h"
#include "compute.h"

void mpi_helper_init(){
    MPI_Init(g_argc, g_argv);
    g_comm = MPI_COMM_WORLD;
    MPI_Comm_size(g_comm, &g_comm_size);
    MPI_Comm_rank(g_comm, &g_part_rank);
}

int mpi_helper_is_master(){
    return g_part_rank == 0;
}

void mpi_helper_abort(){
    MPI_Abort(g_comm, 1);
    MPI_Finalize();
}

void mpi_helper_finalize(){
    MPI_Finalize();
}

void mpi_helper_sync_data(){
    MPI_Bcast(&g_n, 1, MPI_INT, 0, g_comm);
    g_part_size = g_n / g_comm_size;
    g_alloc_part_receive(g_part_size);
    MPI_Scatter(g_data, g_part_size, MPI_INT, g_part_receive, g_part_size, MPI_INT, 0, g_comm);
    g_height = compute_tree_height();
    g_part_height = compute_part_tree_height();
    g_alloc_block();
    for (int i = 0; i<g_part_size; i++)
        g_part_left[i] = g_part_receive[i];
}

void mpi_helper_gather_result(){
    MPI_Gather(g_part_left, g_part_size, MPI_INT, g_data, g_part_size, MPI_INT, 0, g_comm);
    int size = g_part_size;
    for (int i = 0; i <= g_height - 1; i++) {
        int parent = g_part_rank & ~(1 << i);
        if (parent == g_part_rank) {
            int right_child = g_part_rank | (1 << i);
            MPI_Recv(g_part_right, size, MPI_INT, right_child, 0, g_comm, MPI_STATUS_IGNORE);
            compute_merge_sort(size);
            int* temp = g_part_left;
            g_part_left = g_part_merge;
            g_part_merge = temp;
            size *= 2;
        } else {
            MPI_Send(g_part_left, size, MPI_INT, parent, 0, g_comm);
            break;
        }
    }
}