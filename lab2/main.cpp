#include "patricia.hpp"
#include <iostream>
#include <cstring>

using namespace std;


int main() {
    // Node* root = NULL;
    // for (int i = 0; i < 5; ++i) {
    //     char* name = (char*)malloc(256*sizeof(char));
    //     int value;
    //     scanf("%s %d", name, &value);
    //     AddVariant(&root, name, value);
    // }

    // PrintPatricia(root, -2);

    
    // char a[] = "abce";
    // char b[] = "abqer";
    // printf("%d\n", CompareNames(a, b));
    // printf("\n%s\n", a);
    // for (int i = 0; i < strlen(a); ++i) {
    //     char bin[10];
    //     Convertation(bin, (int)a[i]);
    //     printf("%c\t%s\n", a[i], bin);
    // }
    // printf("\n%s\n", b);
    // for (int i = 0; i < strlen(b); ++i) {
    //     char bin[10];
    //     Convertation(bin, (int)b[i]);
    //     printf("%c\t%s\n", b[i], bin);
    // }


    Node* root = NULL;
    char input[257];
    char name[257];
    unsigned long long value;
    while(cin >> input) {
        if (input[0] == '+') {
            cin >> name >> value;
            char* input_name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
            strcpy(input_name, name);
            input_name[strlen(name)] = '\0';
            AddVariant(&root, input_name, value);
        }
        else if (input[0] == '-') {
            cin >> name;
            RemoveVariant(&root, name);
        }
        else if (input[0] == '!') {
            char command[10];
            cin >> command;
            if (strcmp(command, "Save") == 0) {

            }
            else if (strcmp(command, "Load") == 0) {

            } 
            else {
                //error
                printf("ERROR ! cmd\n");
            }
        }
        else {
            Node* find = FindVariant(root, input);
            if (strcmp(find->name, input) == 0) {
                printf("%lld\n", find->value);
            } else {
                printf("dont find\n");
            }
        }
    }
    Clear(root, -2);
    return 0;
}