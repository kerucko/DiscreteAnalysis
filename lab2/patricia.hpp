#include <stdlib.h>

struct Node {
    int index;
    char* name;
    unsigned long long value;
    Node* left;
    Node* right;
};


int StringLower(char* string);
void AddVariant(Node** root, char* name, unsigned long long value);
bool RemoveVariant(Node** root, char* name);
void Convertation(char* bin, int dec);
int CheckIndex(char* name, int index);
int CompareNames(char* first, char* second);
Node* FindVariant(Node* root, char* name);
void PrintNode(Node *node);
void PrintPatricia(Node* root, int previous_index);
void Clear(Node* root, int previous_index);
void SaveInFile(Node* root, char* filename);
void LoadFromFile(Node* root, char* filename);