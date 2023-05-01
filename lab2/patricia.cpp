#include "patricia.hpp"
#include <iostream>
#include <cstring>

using namespace std;

int StringLower(char* string) {
    for (int i = 0; i < strlen(string); ++i) {
        if ((string[i] >= 'a' && string[i] <= 'z') ||(string[i] >= 'A' && string[i] <= 'Z')) {
            string[i] = tolower(string[i]);
        } else {
            return -1;
        }
    }
    return 0;
}

void AddVariant(Node** root, char* name, unsigned long long value) {
    if (StringLower(name) == -1) {
        printf("ERROR\n");
        return;
    }
    if (*root == NULL) {
        *root = (Node*)malloc(sizeof(Node));
        // root->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        (*root)->name = name;
        // root->name[strlen(name)] = '\0';
        (*root)->index = -1;
        (*root)->value = value;
        (*root)->left = (*root);
        (*root)->right = (*root);
    } 
    else if ((*root)->left == *root) {
        Node* insert_node = (Node*)malloc(sizeof(Node));
        insert_node->name = name;
        insert_node->value = value;
        insert_node->index = CompareNames(name, (*root)->name);
        if (CheckIndex(name, insert_node->index)) {
            insert_node->left = *root;
            insert_node->right = insert_node;
        } else {
            insert_node->right = *root;
            insert_node->left = insert_node;
        }
        (*root)->left = insert_node;
    }
    else {
        Node* find = FindVariant(*root, name);
        if (strcmp(find->name, name) == 0) {
            printf("already exist\n");
        }
        else {
            Node* insert_node = (Node*)malloc(sizeof(Node));
            insert_node->name = name;
            insert_node->value = value;
            insert_node->index = CompareNames(name, find->name);
            Node* current = (*root)->left;
            Node* previous = *root;
            while (current->index > previous->index && current->index < insert_node->index) {
                previous = current;
                if(CheckIndex(name, current->index)) {
                    current = current->right;
                } else {
                    current = current->left;
                }
            }

            if (CheckIndex(name, insert_node->index)) {
                insert_node->left = current;
                insert_node->right = insert_node;
            } else {
                insert_node->left = insert_node;
                insert_node->right = current;
            }

            if (previous->right == current) {
                previous->right = insert_node;
            } else {
                previous->left = insert_node;
            }
        }
    }
}


bool RemoveVariant(Node** root, char* name) {
    if (StringLower(name) == -1) {
        return false;
    }
    Node* find = FindVariant(*root, name);
    if (strcmp(find->name, name) != 0) {
        return false;
    }
    if ((*root)->left == *root) {
        if (strcmp((*root)->name, name) == 0) {
            free(*root);
            *root = NULL;
            return true;
        } else {
            return false;
        }
    } 

}


int CheckIndex(char* name, int index) {
    int symbol = name[index / 7];
    return (symbol >> (6 - index % 7)) & 1;
}


int CompareNames(char* first, char* second) {
    int size1 = strlen(first);
    int size2 = strlen(second);
    int index = 0; 

    while(CheckIndex(first, index) == CheckIndex(second, index) && index < size1 * 7 && index < size2 * 7) {
        ++index;
    }
    return index;
}


Node* FindVariant(Node* root, char* name) {
    Node* current = root->left;
    int previous_index = -1;
    while (current->index > previous_index) {
        // printf("current:\n");
        // PrintNode(current);
        previous_index = current->index;
        if(CheckIndex(name, current->index)) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    // printf("STOP: %d %d\n", previous_index, current->index);
    return current;
}


Node* FindValue(Node* root, unsigned long long value) {

}


void Convertation(char* bin, int dec) {
    for (int n = 6; n >= 0; --n) {
        bin[n] = '0' + (dec >> (6 - n) & 1);
    }
    bin[7] = '\0';
}


void PrintNode(Node* node) {
    printf("name: %s \t", node->name);
    char bin[7];
    Convertation(bin, node->name[0]);
    printf("%s \t", bin);
    printf("index: %d\tvalue: %lld\n", node->index, node->value);
    printf("\tleft: %s\t\tright: %s\n", node->left->name, node->right->name);
}


void PrintPatricia(Node* root, int previous_index) {
    if(root->index > previous_index) {
        PrintNode(root);
        PrintPatricia(root->left, root->index);
        PrintPatricia(root->right, root->index);
    }
}