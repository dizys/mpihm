#include <stdlib.h>
#include <stdio.h>
#include "output.h"
#include "global.h"

void output_result(){
    FILE* output_file = fopen(g_output_file, "w");
    for (int i = 0; i < g_comm_size; i++) {
        fprintf(output_file, "Process %d's result part(%d):", i, g_part_size);
        printf("Process %d's result part(%d):", i, g_part_size);
        for (int j = 0; j < g_part_size; j++) {
            fprintf(output_file, "%d ", g_data[g_part_size*i + j]);
            printf("%d ", g_data[g_part_size*i + j]);
        }
        fprintf(output_file, "\n");
        printf("\n");
    }
    fprintf(output_file, "\nOverall sorting result(%d):\n", g_n);
    printf("\nOverall sorting result(%d):\n", g_n);
    if (g_height % 2 != 0)
        for (int i = 0; i < g_n; i++) {
            fprintf(output_file, "%d  ", g_part_merge[i]);
            printf("%d    ", g_part_merge[i]);
        }
    else
        for (int i = 0; i < g_n; i++) {
            fprintf(output_file, "%d    ", g_part_left[i]);
            printf("%d  ", g_part_left[i]);
        }
    fprintf(output_file, "\n");
    printf("\nOutput file: %s\n", g_output_file);
}