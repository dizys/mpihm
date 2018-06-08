#include <string.h>
#include "compute.h"
#include "global.h"

int compute_tree_height(){
    int height = 0;
    int j = g_comm_size;
    for (int i = 0; i<g_comm_size; i++) {
        j = j / 2;
        if (j == 0)
            break;
        height++;
    }
    return height;
}

int compute_part_tree_height(){
    int height = 0;
    for (int i = 0; i < g_height; i++) {
        int parent = g_part_rank & ~(1 << i);
        if (parent != g_part_rank)
            break;
        height++;
    }
    return height;
}

void compute_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compute_partition(int low, int high)
{
    int key = g_part_left[high];
    int i = low - 1;
    for (int j = low; j<high; j++)
    {
        if (g_part_left[j] <= key)
        {
            i = i + 1;
            compute_swap(&g_part_left[i], &g_part_left[j]);
        }
    }
    compute_swap(&g_part_left[i + 1], &g_part_left[high]);
    return i + 1;
}

void compute_quick_sort(int low, int high){
    if (low >= high) return;
    int k = compute_partition(low, high);
    compute_quick_sort(low, k - 1);
    compute_quick_sort(k + 1, high);
}

void compute_merge_sort(int size){
    int lp = 0, rp = 0, mp = 0;
    for (int i = 0; i<2 * size; i++) {
        if (g_part_left[lp] <= g_part_right[rp]) {
            g_part_merge[mp] = g_part_left[lp];
            lp++;
        } else {
            g_part_merge[mp] = g_part_right[rp];
            rp++;
        }
        mp++;
        if (lp == size || rp == size)
            break;
    }
    if (lp == size)
        memcpy(&g_part_merge[mp], &g_part_right[rp], (size - rp) * sizeof(int));
    else
        memcpy(&g_part_merge[mp], &g_part_left[lp], (size - lp) * sizeof(int));
}