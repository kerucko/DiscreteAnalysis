#include <iostream>
#include <cstring>

using namespace std;


class String {
    char* string = (char*)malloc(2 * sizeof(char));
    int capacity = 2;
    int size = 0;

public:
    char& operator[](int index) {
        return string[index];
    }

    void Add(char symbol) {
        if (size == capacity - 1) {
            capacity *= 2;
            string = (char*)realloc(string, capacity * sizeof(char));
        }
        string[size] = symbol;
        ++size;
    }

    void AddLine(char* line) {
        for (int i = 0; i < strlen(line); ++i) {
            Add(line[i]);
        }
    }

    int Size() {
        return size;
    }

    char* GetString() {
        return string;
    }

    void Print() {
        printf("%s", string);
    }
    
    friend ostream& operator<<(ostream& os, const String& line);
};

ostream& operator<<(ostream& os, const String& line) {
    os << line.string;
    return os;
}


class Vector {
    char** string = (char**)malloc(2 * sizeof(char*));
    int capacity = 2;
    int size = 0;
public:
    char*& operator[](int index) {
        return string[index];
    }

    void Add(char* symbol) {
        if (size == capacity - 1) {
            capacity *= 2;
            string = (char**)realloc(string, capacity * sizeof(char*));
        }
        string[size] = symbol;
        ++size;
    }

    int Size() {
        return size;
    }
};


class Trie {
private:
    struct Node {
        Node** next = NULL;
        Node* suffix_link = NULL;
        char* word = NULL;
        bool end = false;
        int capacity = 1;
        int next_size = 0;

        Node(const char* _word) {
            word = (char*)malloc(sizeof(char) * (strlen(_word) + 1));
            strcpy(word, _word);
            word[strlen(_word)] = '\0';
        }
    };
    
    Node* root;


    int FindNext(Node* node, char* word) {
        for (int i = 0; i < node->next_size; ++i) {
            if (node->next[i] != NULL && strcmp(node->next[i]->word, word) == 0) {
                return i;
            }
        }
        return -1;
    }


    void AddNext(Node*& node, char* word) {
        Node* new_next = new Node(word);

        if (node->next_size == node->capacity - 1) {
            node->capacity *= 2;
            node->next = (Node**)realloc(node->next, node->capacity * sizeof(Node*));
        }
        node->next[node->next_size] = new_next;
        ++(node->next_size);
    }


    void Print(Node* node, int deep) {
        printf("%d {%s}\n", deep, node->word);
        for (int i = 0; i < node->next_size; ++i) {
            Print(node->next[i], deep + 1);
        }
    }
public:

    Trie() {
        root = new Node("-");
    }


    void Add(const char* string) {
        printf("add {%s}\n", string);
        Node* current_node = root;
        char* add_string = (char*)malloc(sizeof(char) * strlen(string));
        strcpy(add_string, string);

        char* word = strtok(add_string, " \t\n");
        while (word != NULL) {
            printf("word: {%s}\n", word);
            int index = FindNext(current_node, word);
            if (index == -1) {
                AddNext(current_node, word);
                current_node = current_node->next[current_node->next_size - 1];
            } else {
                current_node = current_node->next[index];
            }

            word = strtok(NULL, " \t\n");
        }
        current_node->end = true;
    }


    bool Find(const char* string) {
        Node* current_node = root;
        char* add_string = (char*)malloc(sizeof(char) * strlen(string));
        strcpy(add_string, string);

        char* word = strtok(add_string, " \t\n");
        while (word != NULL) {
            printf("find curr: {%s}\n", word);
            int index = FindNext(current_node, word);
            if (index == -1) {
                return false;
            } else {
                current_node = current_node->next[index];
            }

            word = strtok(NULL, " \t\n");
        }
        if (current_node->end) {
            return true;
        } else {
            return false;
        }
    }


    void PrintTrie() {
        Print(root, 0);
    }
};


String Input() {
    char symbol = getchar();
    String result;

    while (symbol != EOF) {
        result.Add(symbol);
        symbol = getchar();
    }

    return result;
}


int Split(String input, int& count_lines) {
    for (int i = 1; i < input.Size(); ++i) {
        if (input[i] == '\n') {
            ++count_lines;
        }
        if (input[i] == '\n' && input[i + 1] == '\n') {
            return i + 1;
        }
    }
    return -1;
}


void ParseInput(String input, Vector& patterns, Vector& text) {
    int count_patterns = 0;
    int empty_string_index = Split(input, count_patterns);
    if (empty_string_index == -1) {
        count_patterns = 1;
    }

    char* input_string = input.GetString();
    char* current_pattern = strtok(input_string, "\n");
    patterns.Add(current_pattern);
    for (int i = 1; i < count_patterns; ++i) {
        current_pattern = strtok(NULL, "\n");
        patterns.Add(current_pattern);
    }

    char* current_word = strtok(NULL, " \t\n");
    while (current_word != NULL) {
        text.Add(current_word);
        current_word = strtok(NULL, " \t\n");
    }
}


int main() {
    String input = Input();
    Vector patterns;
    Vector text;
    ParseInput(input, patterns, text);

    // for (int i = 0; i < patterns.Size(); ++i) {
    //     printf("%d pattern: %s\n", i + 1, patterns[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < text.Size(); ++i) {
    //     printf("%d word: %s\n", i + 1, text[i]);
    // }
    // printf("\n");

    Trie trie;
    for (int i = 0; i < patterns.Size(); ++i) {
        printf("{PATTERN %d}\n", i + 1);
        char* current_pattern = patterns[i];
        char* string = strtok(current_pattern, "?");
        while (string != NULL) {
            printf("part of pattern: {%s}\n", string);
            char* add_string = (char*)malloc(sizeof(char) * strlen(string));
            strcpy(add_string, string);
            trie.Add(add_string);
            string = strtok(NULL, "?");
        }

        printf("TRIE:\n");
        trie.PrintTrie();

        // printf("%d\n", trie.Find(patterns[i]));
    }
    
    return 0;
}