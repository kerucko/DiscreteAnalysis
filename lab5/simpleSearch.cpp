#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

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

    string text;
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

            if (activeNode->next.find(text[activeEdge]) != activeNode->next.end()) {
                Node* nextNode = activeNode->next[text[activeEdge]];

                if (activeLength >= nodeSize(nextNode)) {
                    activeEdge += nodeSize(nextNode);
                    activeLength -= nodeSize(nextNode);
                    activeNode = nextNode;
                    continue;
                }

                if (text[nextNode->start + activeLength] == text[index]) {
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
                activeNode->next[text[activeEdge]] = newNode;
                nextNode->start += activeLength;

                newNode->next[text[nextNode->start]] = nextNode;
                nextNode->previous = newNode;
                newNode->next[text[index]] = new Node(index, globalEnd, true, root, newNode);
                if (lastAddedNode != nullptr) {
                    lastAddedNode->suffixLink = newNode;
                    lastAddedNode = nullptr;
                }
                lastAddedNode = newNode;
            } else {
                Node* newNode = new Node(index, globalEnd, true, root, activeNode);
                activeNode->next[text[activeEdge]] = newNode;
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
            cout << text.substr(node->start, nodeSize(node)) << "[" << node->start << ", " << node->start + nodeSize(node) - 1 << "] sl: ";
            if (node->suffixLink == root) {
                cout << "root; pl: " << prefixLength(node) << "\n";
            } else {
                cout << text.substr(node->suffixLink->start, nodeSize(node->suffixLink)) << "[" << node->suffixLink->start << ", ";
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

    void AddResult(vector<int>* result, Node* node) {
        if (node->next.size() == 0) {
            result->push_back(node->start - prefixLength(node->previous));
        }
        for (auto& x: node->next) {
            AddResult(result, x.second);
        }
    }
public:

    explicit SuffixTree(const string& inputText) {
        text = inputText + "$";
        root = new Node(0, 0, false, root, root);
        root->previous = root;
        root->suffixLink = root;
        activeNode = root;
        lastAddedNode = nullptr;
        for (int i = 0; i < text.size(); i++) {
            Add(i);
        }
        fixSuffixLink(root);
    }

    vector<int> Find(string pattern) {
        vector<int> result;

        Node* currentNode = root;
        int wordIndex = 0;
        int compareIndex = 0;
        bool flag = false;

        while (wordIndex < pattern.size()) {
            if (currentNode->next.find(pattern[wordIndex]) == currentNode->next.end()) {
                return result;
            } else {
                currentNode = currentNode->next[pattern[wordIndex]];
            }

            flag = false;
            for (compareIndex = 0; compareIndex + wordIndex < pattern.size() && compareIndex < nodeSize(currentNode); compareIndex++) {
                if (pattern[compareIndex + wordIndex] != text[currentNode->start + compareIndex]) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                return result;
            } else {
                if (compareIndex + wordIndex == pattern.size()) {
                    break;
                }
                if (compareIndex == nodeSize(currentNode)) {
                    wordIndex += compareIndex;
                }
            }
        }
        AddResult(&result, currentNode);
        sort(result.begin(), result.end());

        return result;
    }

    void Print() {
        PrintNode(root, 0);
        cout << "\n";
    }
};

int main() {
    string text, pattern;
    cin >> text;
    int n;
    cin >> n;

    SuffixTree tree(text);

    int count = 1;
    while (cin >> pattern) {
        vector<int> result =  tree.Find(pattern);
        if (result.size() > 0) {
            cout << count << ": ";
            for (int i = 0; i < result.size(); i++) {
                cout << result[i] + 1;
                if (i != result.size() - 1) {
                    cout << ", ";
                } else {
                    cout << "\n";
                }
            }
        }
        count++;
    }
    return 0;
}