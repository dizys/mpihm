
#ifndef HM_MPI_HELPER_H
#define HM_MPI_HELPER_H

void mpi_helper_init();
int mpi_helper_is_master();
void mpi_helper_abort();
void mpi_helper_finalize();
void mpi_helper_sync_data();
void mpi_helper_gather_result();

#endif //HM_MPI_HELPER_H
