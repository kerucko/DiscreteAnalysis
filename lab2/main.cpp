#include "patricia.hpp"
#include <iostream>
#include <cstring>

using namespace std;


int main() {
    Node *root{0};
    char input;
    char name[300];
    unsigned long long value;
    while(scanf("%c", &input) != 0) {
        if (input == '+') {
            scanf("%s %lld", name, &value);
        }
        else if (input == '-') {
            scanf("%s", name);
        }
        else if (input == '!') {
            char command[10];
            scanf("%s", command);
            if (strcmp(command, "Save") == 0) {

            }
            else if (strcmp(command, "Load") == 0) {

            } 
            else {
                //error
            }
        }
        else {
            //error
        }
    }
    return 0;
}