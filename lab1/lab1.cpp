#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>

struct Data {
    int key;
    char *string;
};

Data *InputData(int *size) {
    Data *array = (Data *)malloc(1 * sizeof(Data));
    int input_key;
    char input_string[2048];
    int capacity = 1;
    while (scanf("%d%s", &input_key, input_string) != EOF) {
        if (*size == capacity) {
            array = (Data  *)realloc(array, 2 * capacity * sizeof(Data));
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

void OutputData(Data *array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d\t%s\n", array[i].key, array[i].string);
    }
}

Data *Sort(Data *array, int size) {
    const int numbers = 65536;
    int counter[numbers] = {0};
    for (int i = 0; i < size; ++i) {
        ++counter[array[i].key];
    }
    for (int i = 1; i < numbers; ++i) {
        counter[i] += counter[i - 1];
    }
    Data *sorted_array = (Data *)malloc(size * sizeof(Data));
    for (int i = size - 1; i >= 0; --i) {
        sorted_array[counter[array[i].key] - 1] = array[i];
        --counter[array[i].key];
    }
    return sorted_array;
}

int main() {
    int size = 0;
    Data *array = InputData(&size);
    Data *result = Sort(array, size);
    OutputData(result, size);
    for (int i = 0; i < size; ++i) {
        free(array[i].string);
    }
    free(array);
    free(result);
    return 0;
}