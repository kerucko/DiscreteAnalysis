#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class SuffixTree {
private:
    struct Node {
        map<char, Node*> next;
        Node* suffixLink;
        Node* previous;
        int start;
        int end;
        bool endFlag;

        Node(int newStart, int newEnd, bool newEndFlag, Node* newSuffixLink, Node* newPrevious) {
            start = newStart;
            end = newEnd;
            endFlag = newEndFlag;
            suffixLink = newSuffixLink;
            previous = newPrevious;
        }
    };

    string pattern;
    Node* root;
    Node* lastAddedNode;
    Node* activeNode;
    int globalEnd = 0;
    int activeEdge = 0;
    int activeLength = 0;
    int reminder = 0;

    int nodeSize(Node* node) const {
        if (node->endFlag) {
            return globalEnd - node->start;
        }
        return node->end - node->start + 1;
    }

    int prefixLength(Node* node) {
        if (node == root) {
            return  0;
        }
        return nodeSize(node) + prefixLength(node->previous);
    }

    void Add(int index) {
        lastAddedNode = nullptr;
        ++globalEnd;
        ++reminder;

        while (reminder > 0) {
            if (activeLength == 0) {
                activeEdge = index;
            }

            if (activeNode->next.find(pattern[activeEdge]) != activeNode->next.end()) {
                Node* nextNode = activeNode->next[pattern[activeEdge]];

                if (activeLength >= nodeSize(nextNode)) {
                    activeEdge += nodeSize(nextNode);
                    activeLength -= nodeSize(nextNode);
                    activeNode = nextNode;
                    continue;
                }

                if (pattern[nextNode->start + activeLength] == pattern[index]) {
                    if (activeNode != root) {
                        if (lastAddedNode != nullptr) {
                            lastAddedNode->suffixLink = activeNode;
                            lastAddedNode = nullptr;
                        }
                    }
                    ++activeLength;
                    break;
                }

                Node* newNode = new Node(nextNode->start, nextNode->start + activeLength - 1, false, root, activeNode);
                activeNode->next[pattern[activeEdge]] = newNode;
                nextNode->start += activeLength;

                newNode->next[pattern[nextNode->start]] = nextNode;
                nextNode->previous = newNode;
                newNode->next[pattern[index]] = new Node(index, globalEnd, true, root, newNode);
                if (lastAddedNode != nullptr) {
                    lastAddedNode->suffixLink = newNode;
                    lastAddedNode = nullptr;
                }
                lastAddedNode = newNode;
            } else {
                Node* newNode = new Node(index, globalEnd, true, root, activeNode);
                activeNode->next[pattern[activeEdge]] = newNode;
                if (lastAddedNode != nullptr) {
                    lastAddedNode->suffixLink = activeNode;
                    lastAddedNode = nullptr;
                }
            }

            --reminder;

            if (activeNode == root && activeLength > 0) {
                ++activeEdge;
                --activeLength;
            }
            if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }

    void PrintNode(Node* node, int length) {
        if (node != root) {
            for (int i = 0; i < length; i++) {
                cout << "\t|";
            }
            cout << pattern.substr(node->start, nodeSize(node)) << "[" << node->start << ", " << node->start + nodeSize(node) - 1 << "] sl: ";
            if (node->suffixLink == root) {
                cout << "root; pl: " << prefixLength(node) << "\n";
            } else {
                cout << pattern.substr(node->suffixLink->start, nodeSize(node->suffixLink)) << "[" << node->suffixLink->start << ", ";
                cout << node->suffixLink->start + nodeSize(node->suffixLink) - 1 << "]; l: " << prefixLength(node) << "\n";
            }
        } else {
            cout << "root\n";
        }
        for (auto& x: node->next) {
            PrintNode(x.second, length + 1);
        }
    }

    void fixSuffixLink(Node* node) {
        if (node->suffixLink == node->previous) {
            node->suffixLink = root;
        }
        for (auto& x: node->next) {
            fixSuffixLink(x.second);
        }
    }
public:

    explicit SuffixTree(const string& inputPattern) {
        pattern = inputPattern + "$";
        root = new Node(0, 0, false, root, root);
        root->previous = root;
        root->suffixLink = root;
        activeNode = root;
        lastAddedNode = nullptr;
        for (int i = 0; i < pattern.size(); i++) {
            Add(i);
        }
        fixSuffixLink(root);
    }

    vector<int> Find(string text) {
        text = "$" + text;
        vector<int> result(text.size(), 0);

        Node *currentNode = root;
        int prevStart = 0;
        int compareIndex = 0;
        int wordIndex = 0;

        for (int i = 1; i < text.size(); i++) {
            wordIndex = i;
            currentNode = currentNode->previous;

            if (currentNode != root) {
                currentNode = currentNode->suffixLink;
                if (compareIndex > 0) {
                    currentNode = currentNode->next[text[prevStart]];
                }
            } else {
                compareIndex = 0;
            }

            while (wordIndex < text.size()) {
                if (currentNode == root) {
                    if (currentNode->next.find(text[wordIndex]) != currentNode->next.end()) {
                        compareIndex = 0;
                        currentNode = currentNode->next[text[wordIndex]];
                    } else {
                        break;
                    }
                }

                bool flag = false;
                for (compareIndex; compareIndex + wordIndex < text.size() && compareIndex < nodeSize(currentNode); compareIndex++) {
                    if (text[compareIndex + wordIndex] != text[currentNode->start + compareIndex]) {
                        flag = true;
                        break;
                    }
                }

                prevStart = currentNode->start;
                if (flag) {
                    break;
                } else {
                    if (compareIndex + wordIndex >= text.size()) {
                        break;
                    }
                    if (compareIndex >= nodeSize(currentNode)) {
                        wordIndex += min(compareIndex, nodeSize(currentNode));

                        if (currentNode->next.find(text[wordIndex]) != currentNode->next.end()) {
                            compareIndex = 0;
                            currentNode = currentNode->next[text[wordIndex]];
                        } else {
                            break;
                        }
                    }
                }
            }
            result[i] += prefixLength(currentNode->previous) + compareIndex;
        }

        return result;
    }

    void Print() {
        PrintNode(root, 0);
        cout << "\n";
    }
};

int main() {
    string text, pattern;
    cin >> pattern >> text;

    SuffixTree tree(pattern);
//    tree.Print();
    vector<int> result = tree.Find(text);

    for (int i = 1; i < result.size(); i++) {
         if (result[i] == pattern.size()) {
             cout << i << "\n";
         }
    }

    return 0;
}