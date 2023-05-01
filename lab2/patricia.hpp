#include <stdlib.h>

struct Node {
    int index;
    char* name = nullptr;
    unsigned long long value;
    Node* left = nullptr;
    Node* right = nullptr;
};


int StringLower(char* string);
void AddVariant(Node** root, char* name, unsigned long long value);
bool RemoveVariant(Node* root, char* name);
void Convertation(char* bin, int dec);
int CheckIndex(char* name, int index);
int CompareNames(char* first, char* second);
Node* FindVariant(Node* root,char* name);
Node* FindValue(Node* root, unsigned long long value);
void PrintNode(Node *node);
void PrintPatricia(Node* root, int previous_index);