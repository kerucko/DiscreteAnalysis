#include <iostream>
#include <algorithm>
#include <string.h>

typedef struct data {
    int key;
    char *string;
} data;

bool comparator(data first, data second) {
    return first.key < second.key;
}

data *input_data(int *size) {
    data *array = (data *)malloc(1 * sizeof(data));
    int input_key;
    char input_string[2048];
    int capacity = 1;
    while (scanf("%d%s", &input_key, input_string) != EOF) {
        if (*size == capacity) {
            array = (data  *)realloc(array, 2 * capacity * sizeof(data));
            capacity *= 2;
        }
        array[*size].key = input_key;
        array[*size].string = (char *)malloc((strlen(input_string) + 1) * sizeof(char));
        for (int i = 0; i <= strlen(input_string); ++i) {
            array[*size].string[i] = input_string[i];
        }
        ++(*size);
    }   
    return array;
}

void output_data(data *array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d\t%s\n", array[i].key, array[i].string);
    }
}

int main() {
    int size = 0;
    data *array = input_data(&size);
    std::sort(array, array + size, comparator);
    output_data(array, size);
    for (int i = 0; i < size; ++i) {
        free(array[i].string);
    }
    free(array);
    return 0;
}