#include "patricia.hpp"
#include <iostream>
#include <cstring>

using namespace std;


int main() {
    Node* root = NULL;
    for (int i = 0; i < 5; ++i) {
        char* name = (char*)malloc(256*sizeof(char));
        int value;
        scanf("%s %d", name, &value);
        AddVariant(&root, name, value);
    }

    PrintPatricia(root, -2);
    // Node* a = (Node*)malloc(sizeof(Node));
    // a->name = (char*)malloc(20 * sizeof(char));
    // strcpy(a->name, "a");
    // a->name[1] = '\0';
    // a->value = 1;
    // a->index = -1;
    // Node *z = (Node*)malloc(sizeof(Node));
    // z->name = (char*)malloc(20 * sizeof(char));
    // strcpy(z->name, "z");
    // z->name[1] = '\0';
    // z->value = 2;
    // z->index = 2;
    // Node *d = (Node*)malloc(sizeof(Node));
    // d->name = (char*)malloc(20 * sizeof(char));
    // strcpy(d->name, "d");
    // d->name[1] = '\0';
    // d->value = 3;
    // d->index = 4;
    // Node *b = (Node*)malloc(sizeof(Node));
    // b->name = (char*)malloc(20 * sizeof(char));
    // strcpy(b->name, "b");
    // b->name[1] = '\0';
    // b->value = 4;
    // b->index = 5;
    // Node *f = (Node*)malloc(sizeof(Node));
    // f->name = (char*)malloc(20 * sizeof(char));
    // strcpy(f->name, "f");
    // f->name[1] = '\0';
    // f->value = 6;
    // f->index = 5;

    // a->left = z;
    // a->right = a;
    // z->left = d;
    // z->right = z;
    // d->left = b;
    // d->right = f;
    // b->left = a;
    // b->right = b;
    // f->left = d;
    // f->right = f;

    // PrintPatricia(a, -2);

    // Node* find = FindVariant(a, (char*)"d");
    // printf("find:\n");
    // PrintNode(find);
    
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


    // Node* root{-1};
    // char input;
    // char name[300];
    // unsigned long long value;
    // while(scanf("%c", &input) != 0) {
    //     if (input == '+') {
    //         scanf("%s %lld", name, &value);
    //     }
    //     else if (input == '-') {
    //         scanf("%s", name);
    //     }
    //     else if (input == '!') {
    //         char command[10];
    //         scanf("%s", command);
    //         if (strcmp(command, "Save") == 0) {

    //         }
    //         else if (strcmp(command, "Load") == 0) {

    //         } 
    //         else {
    //             //error
    //         }
    //     }
    //     else {
    //         //error
    //     }
    // }
    return 0;
}