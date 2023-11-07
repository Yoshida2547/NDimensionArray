#include <stdio.h>
#include <stdlib.h>

#include "../include/lib_ndarray.h"

void two(int index, double *item);
void test01();
void test02();

int main(void) {

    return 0;
}

void two(int i, double *u) {
    *u = 2;
}

void test02() {
    //create a empty array

    NDArray *arr1 = nd_empty(3, nd_shape(3, 3,3,3));    

    //asign some valuse

    for(int k = 0; k < arr1->shape[2]; k++) {
        for(int j = 0; j < arr1->shape[1]; j++) {
            for(int i = 0; i < arr1->shape[0]; i++) {
                double *item = nd_get(arr1, nd_indexes(3, i,j,k), FREE_INDEXES_ARRAY);

                *item = i+j*k;
            }
        }
    }

    //print
    
    for(int k = 0; k < arr1->shape[2]; k++) {
        for(int j = 0; j < arr1->shape[1]; j++) {
            for(int i = 0; i < arr1->shape[0]; i++) {
                printf("(%d) (%d, %d, %d) -> %f \n", i*arr1->map[0]+j*arr1->map[1]+k*arr1->map[2], i, j, k, *nd_get(arr1, nd_indexes(3, i,j,k), FREE_INDEXES_ARRAY));
            }
        }
    }

    putchar('\n');

    int lin = 18;
    int *indexes = nd_2nd(arr1, lin);

    printf("lin: %d -> (%d, %d, %d) \n", lin, indexes[0], indexes[1], indexes[2]);
}

void test01() {
    //create a empty array

    NDArray *arr1 = nd_empty(3, nd_shape(3, 27,27,3));    

    //asign some valuse

    for(int k = 0; k < arr1->shape[2]; k++) {
        for(int j = 0; j < arr1->shape[1]; j++) {
            for(int i = 0; i < arr1->shape[0]; i++) {
                double *item = nd_get(arr1, nd_indexes(3, i,j,k), FREE_INDEXES_ARRAY);

                *item = i+j*k;
            }
        }
    }

    //print
    
    for(int k = 0; k < arr1->shape[2]; k++) {
        for(int j = 0; j < arr1->shape[1]; j++) {
            for(int i = 0; i < arr1->shape[0]; i++) {
                printf("(%d, %d, %d) -> %f \n", i, j, k, *nd_get(arr1, nd_indexes(3, i,j,k), FREE_INDEXES_ARRAY));
            }
        }
    }

    //slicing keep dim

    NDArray *arr2 = malloc(sizeof(NDArray));

    arr2->dim = 3;
    arr2->shape = nd_shape(3, 27,1,3);
    arr2->map = arr1->map;
    arr2->offset = nd_get(arr1, nd_indexes(3, 0,0,0), FREE_INDEXES_ARRAY);

    for(int k = 0; k < arr2->shape[2]; k++) {
        for(int j = 0; j < arr2->shape[1]; j++) {
            for(int i = 0; i < arr2->shape[0]; i++) {
                printf("(%d, %d, %d) -> %f \n", i, j, k, *nd_get(arr2, nd_indexes(3, i,j,k), FREE_INDEXES_ARRAY));
            }
        }
    }

    putchar('\n');
    putchar('\n');

    //flatten
    
    NDArray *arr3 = malloc(sizeof(NDArray));

    arr3->dim = 1;
    arr3->shape = nd_indexes(1, 2187);
    arr3->map = nd_sizes_map(1, nd_indexes(1, 2187));
    arr3->offset = nd_get(arr1, nd_indexes(3, 0,0,0), FREE_INDEXES_ARRAY);

    for(int i = 0; i < arr3->shape[0]; i++) {
        printf("(%d) -> %f \n", i, *nd_get(arr3, nd_indexes(1, i), FREE_INDEXES_ARRAY));
    }

    putchar('\n');
    putchar('\n');

    //reshape

    NDArray *arr4 = malloc(sizeof(NDArray));

    arr4->dim = 2;
    arr4->shape = nd_shape(2, 3,729);
    arr4->map = nd_sizes_map(2, nd_indexes(2, 3,729));
    arr4->offset = nd_get(arr1, nd_indexes(3, 0,0,0), FREE_INDEXES_ARRAY);

    for(int j = 0; j < arr4->shape[1]; j++) {
        for(int i = 0; i < arr4->shape[0]; i++) {
            printf("(%d, %d) -> %f \n", i, j, *nd_get(arr4, nd_indexes(2, i,j), FREE_INDEXES_ARRAY));
        }
    }
}

