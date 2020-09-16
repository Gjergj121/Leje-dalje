#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int *start;
    start = (int*)malloc(3);

    for(int i = 0; i < 3; i++) {
        start[i] = 5;
    }

    for(int i = 0; i < 3; i++) {
        printf("%d", *(start + i));
    }

    return 1; 
}

