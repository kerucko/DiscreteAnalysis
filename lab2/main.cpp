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
                char filename[100];
                cin >> filename;

                ofstream file(filename, ios::binary);
                SaveInFile(root, file);
                file.close();
            }
            else if (strcmp(command, "Load") == 0) {
                char filename[100];
                cin >> filename;

                ifstream file(filename, ios::binary);
                LoadFromFile(&root, file);
                file.close();
            } 
            else {
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