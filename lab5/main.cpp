#include <iostream>
#include <string>
#include <vector>

class SuffixTree {
private:
    struct Node {
        vector<*Node> next;
        int start;
        int end;
    }

    Node* root;
    string pattern;
    int endIndex;
public:
    void AddWord(string word) {
        Node* currentNode = root;
        int wordIndex = 0;
        while wordIndex < word.size() {
            int nextIndex = 0;
            for (nextIndex = 0; nextIndex < currentNode.next.size(); nextIndex++) {
                if word[wordIndex] == pattern[currentNode.next[nextIndex].start] {
                    break;
                }
            }
            if nextIndex == currentNode.next.size() {
                Node* newNode = new Node()
                currentNode.next.push_back()
            } else {
                
            }
        }
    }

    void Print() {

    }
};

int main() {


    return 0;
}