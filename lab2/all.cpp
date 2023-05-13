#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


struct Node {
    int index;
    char* name;
    unsigned long long value;
    Node* left;
    Node* right;
};


int StringLower(char* string);
int AddVariant(Node** root, char* name, unsigned long long value);
bool RemoveVariant(Node** root, char* name);
void Convertation(char* bin, int dec);
int CheckIndex(char* name, int index);
int CompareNames(char* first, char* second);
Node* FindVariant(Node* root, char* name);
void PrintNode(Node* node);
void PrintPatricia(Node* root, int previous_index);
void Clear(Node* root, int previous_index);
void SaveInFile(Node* root, ofstream& file);
void LoadFromFile(Node** root, ifstream& file);


int main() {
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

            int result = AddVariant(&root, input_name, value);
            if (result == 0) {
                printf("OK\n");
            } else if (result == 1) {
                printf("ERROR: wrong name\n");
            } else if (result == 2) {
                printf("Exist\n");
            }
        }
        else if (input[0] == '-') {
            cin >> name;

            if(RemoveVariant(&root, name)) {
                printf("OK\n");
            } else {
                printf("NoSuchWord\n");
            }
        }
        else if (input[0] == '!') {
            char command[10];
            cin >> command;

            if (strcmp(command, "Save") == 0) {
                char filename[100];
                cin >> filename;

                ofstream file(filename, ios::binary);
                SaveInFile(root, file);
                file.close();
                printf("OK\n");
            }
            else if (strcmp(command, "Load") == 0) {
                char filename[100];
                cin >> filename;

                ifstream file(filename, ios::binary);
                LoadFromFile(&root, file);
                file.close();
                printf("OK\n");
            } 
            else {
                printf("ERROR ! cmd\n");
            }
        }
        else {
            Node* find = FindVariant(root, input);

            if (find != NULL && strcmp(find->name, input) == 0) {
                printf("OK: %llu\n", find->value);
            } else {
                printf("NoSuchWord\n");
            }
        }
        // PrintPatricia(root, -2);
    }
    Clear(root, -2);
    return 0;
}


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

int AddVariant(Node** root, char* name, unsigned long long value) {
    if (StringLower(name) == -1) {
        return 1;
    }

    if (*root == NULL) {
        *root = (Node*)malloc(sizeof(Node));
        (*root)->name = name;
        (*root)->index = -1;
        (*root)->value = value;
        (*root)->left = (*root);
        (*root)->right = (*root);
        return 0;
    } 
    else if ((*root)->left == *root) {
        if (strcmp((*root)->name, name) == 0) {
            return 2;
        }
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
        return 0;
    }
    else {
        Node* find = FindVariant(*root, name);

        if (strcmp(find->name, name) == 0) {
            return 2;
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

            return 0;
        }
    }
}


bool RemoveVariant(Node** root, char* name) {
    if (StringLower(name) == -1) {
        return false;
    }

    if (*root == NULL) {
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

    Node* previous = *root;
    Node* current = (*root)->left;
    Node* preprevious = NULL;
    
    while (current->index > previous->index) {
        preprevious = previous;
        previous = current;

        if (CheckIndex(name, current->index)) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    if (strcmp(current->name, name) != 0) {
        return false;
    } 

    if (previous == current) {
        if (preprevious->right == current) {
            if (current->right == current) {
                preprevious->right = current->left;
            } else {
                preprevious->right = current->right;
            }
        } else {
            if (current->right == current) {
                preprevious->left = current->left;
            } else {
                preprevious->left = current->right;
            }
        }
        free(current);
        current = NULL;
        return true;
    }
    
    Node* delete_node = previous;
    Node* back_delete_node = current;
    Node* parent_node = preprevious;
    Node* child_node = *root;
    current = (*root)->left;

    while (current->index > child_node->index) {
        child_node = current;
        if (CheckIndex(delete_node->name, current->index)) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    if (child_node->right == delete_node) {
        child_node->right = back_delete_node;
    } else {
        child_node->left = back_delete_node;
    }

    if (parent_node->right == delete_node) {
        if (CheckIndex(child_node->name, delete_node->index)) {
            parent_node->right = delete_node->right;
        } else {
            parent_node->right = delete_node->left;
        }
    } else {
        if (CheckIndex(child_node->name, delete_node->index)) {
            parent_node->left = delete_node->right;
        } else {
            parent_node->left = delete_node->left;
        }
    }

    back_delete_node->name = delete_node->name;
    back_delete_node->value = delete_node->value;

    free(delete_node);
    delete_node = NULL;

    return true;
}


int CheckIndex(char* name, int index) {
    if (index == -1) {
        return 0;
    }
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
    if (StringLower(name) == -1) {
        return NULL;
    }

    if (root == NULL) {
        return NULL;
    }

    Node* current = root->left;
    int previous_index = -1;

    while (current->index > previous_index) {
        previous_index = current->index;
        if(CheckIndex(name, current->index)) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return current;
}


void Clear(Node* root, int previous_index) {
    if (root == NULL) {
        return;
    }
    if (root->index > previous_index) {
        Clear(root->left, root->index);
        Clear(root->right, root->index);
        free(root->name);
        free(root);
    }
}


void SaveInFile(Node* current, ofstream& file) {
    if (!file) {
        return;
    }
    if (current == NULL) {
        return;
    }
    int size = strlen(current->name);

    file.write((char*)(&size), sizeof(int));
    file.write(current->name, size * sizeof(char)); 
    file.write((char*)(&current->value), sizeof(unsigned long long));

    if (current->left->index > current->index) {
        SaveInFile(current->left, file);
    }
    if (current->right->index > current->index) {
        SaveInFile(current->right, file);
    }
}


void LoadFromFile(Node** root, ifstream& file) {
    if (!file) {
        Clear(*root, -2);
        *root = NULL;
        return;
    }
    Clear(*root, -2);
    *root = NULL;
    
    int size;
    while(file.read((char*)(&size), sizeof(int))) {
        char* name = (char*)malloc(sizeof(char) * (size + 1));
        unsigned long long value;

        file.read(name, size);
        file.read((char*)(&value), sizeof(unsigned long long));
        name[size] = '\0';

        AddVariant(root, name, value);
    }
}


void Convertation(char* bin, int dec) {
    for (int n = 6; n >= 0; --n) {
        bin[n] = '0' + (dec >> (6 - n) & 1);
    }
    bin[7] = '\0';
}


void PrintNode(Node* node) {
    printf("name: %s \t", node->name);
    for (int i = 0; i < strlen(node->name); ++i) {
        char bin[7];
        Convertation(bin, node->name[i]);
        printf("%s", bin);
    }
    printf(" \t");
    printf("index: %d\tvalue: %llu\n", node->index, node->value);
    printf("\tleft: %s\t\tright: %s\n", node->left->name, node->right->name);
}


void PrintPatricia(Node* root, int previous_index) {
    if(root->index > previous_index) {
        PrintNode(root);
        PrintPatricia(root->left, root->index);
        PrintPatricia(root->right, root->index);
    }
}