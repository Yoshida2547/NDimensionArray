#include "../include/lib_ndarray.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Helper function

int __ARRAY_MUL__(int n, int *arr) {
    int a = 1;
    for(int i = 0; i < n; i++) {
        a *= arr[i];
    }

    return a;
}

#define  CHECK_OPTION(x, y)  (x & y) == y

/* ------OPTION-------
 * BIT 0 free the indexes after using.
 *
 * */

int *nd_shape(int dim, ...) {
    int *arr = malloc(sizeof(int)*dim);

    va_list ptr;

    va_start(ptr, dim);

    for(int i = 0; i < dim; i++) {
        arr[i] = va_arg(ptr, int);
    }

    va_end(ptr);

    return arr;
}

int *nd_indexes(int dim, ...) {
    int *arr = malloc(sizeof(int)*dim);

    va_list ptr;

    va_start(ptr, dim);

    for(int i = 0; i < dim; i++) {
        arr[i] = va_arg(ptr, int);
    }

    va_end(ptr);

    return arr;
}

void nd_for(NDArray *arr, int *indexes, char option, int axis, int start, int end, void (*func) (int index, double *item) ) {
    
    int *temp = malloc(sizeof(int)*arr->dim);

    memcpy(temp, indexes, sizeof(int)*arr->dim);

    for(int i = start; i < end; i++) {
        
        temp[axis] = i;

        double *item = nd_get(arr, temp, NO_OPTION);

        func(i, item);
    }

    free(temp);

    if(CHECK_OPTION(option, FREE_INDEXES_ARRAY)) {
        free(indexes);
    }
}

double *nd_get(NDArray *arr, int *indexes, char option){
    return arr->offset + nd_2lin(arr, indexes, option);
}

int *nd_sizes_map(int dim, int *shape) {
    int *sizes_map = malloc(sizeof(int)*dim); 

    sizes_map[0] = 1;

    for(int i = 1; i < dim; i++) {
        sizes_map[i] = sizes_map[i-1]*shape[i-1];
    }

    return sizes_map;
}

NDArray *nd_empty(int dim, int *shape) {

    int size = __ARRAY_MUL__(dim, shape);
    
    double *offset = malloc(sizeof(double)*size);

    NDArray *ndarr = malloc(sizeof(NDArray));
    
    ndarr->offset = offset;
    ndarr->shape = shape;
    ndarr->map = nd_sizes_map(dim, shape);
    ndarr->dim = dim;
    ndarr->size = size;

    return ndarr;
}

int nd_2lin(NDArray *arr, int *indexes, char option) {

    int linear_index = 0;

    for(int i = 0; i < arr->dim; i++) {
        linear_index += indexes[i]*arr->map[i];
    }

    if(CHECK_OPTION(option, FREE_INDEXES_ARRAY)) {
        free(indexes);
    }

    return linear_index;
}

int *nd_2nd(NDArray *arr, int lin) {

    int *indexes = malloc(sizeof(int)*arr->dim);

    int temp = lin;

    for(int i = arr->dim-1; i >= 0; i--) {
        indexes[i] = temp/arr->map[i];
        temp = temp%arr->map[i];
    }

    return indexes;
}

NDArray *nd_slice(NDArray *arr, int *indexes_a, int *indexes_b, char option) {

}


