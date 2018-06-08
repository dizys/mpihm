#include "global.h"

void g_alloc_data(int n){
    g_data = malloc(n * sizeof(int));
}

void g_alloc_part_receive(int size){
    g_part_receive = malloc(size * sizeof(int));
}

void g_alloc_block(){
    g_part_left = malloc((1 << g_part_height) * g_part_size * sizeof(int));
    g_part_right = malloc((1 << (g_part_height - 1)) * g_part_size * sizeof(int));
    g_part_merge = malloc((1 << g_part_height) * g_part_size * sizeof(int));
}

void g_free(){
    free(g_data);
    free(g_part_receive);
    free(g_part_left);
    free(g_part_right);
    free(g_part_merge);
}