#include "patricia.hpp"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


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