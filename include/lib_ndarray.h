#ifndef __NDARRAY_H__
#define __NDARRAY_H__

typedef struct NDArray {
    double *offset;
    int *shape;
    int *map;
    int size;
    int dim;
} NDArray;

#define NO_OPTION  0x00
#define FREE_INDEXES_ARRAY 0x01

int *nd_shape(int dim, ...);
int *nd_indexes(int dim, ...);
int nd_2lin(NDArray *arr, int *indexes, char option);
NDArray *nd_empty(int dim, int *sizes);
int *nd_sizes_map(int dim, int *sizes);
void nd_for(NDArray *arr, int *indexes, char option, int axis, int start, int end, void (*func) (int index, double *item) );
double *nd_get(NDArray *arr, int *indexes, char option);
int *nd_2nd(NDArray *arr, int lin);

#endif
