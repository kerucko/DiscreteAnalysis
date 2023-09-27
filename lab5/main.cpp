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
                cout << pattern.substr(node->suffixLink->start, nodeSize(node->suffixLink)) << "[" << node->suffixLink->start << ", " << node->suffixLink->start + nodeSize(node->suffixLink) - 1 << "]; pl: " << prefixLength(node) << "\n";
            }
        } else {
            cout << "root\n";
        }
        for (auto& x: node->next) {
            PrintNode(x.second, length + 1);
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
    }

    vector<int> Find(string text) {
        /*
        Для первого символа просто ищем максимальный префикс в дереве и записываем длину.
        Откатываемся к ближайщей вершине, переходим по суффиксной ссылке и пропускаем
        символы которые мы уже проверили ранее и пытаемся найти новые.
        */
        text = "$" + text;
        vector<int> result(text.size(), 0);

        Node* currentNode = root;
        int compareIndex = 0;
        int wordIndex = 0;
        int shift = 0;
        bool back = false;

        for (int i = 1; i < text.size(); i++) {
            wordIndex = i;
            cout << "\n{NEXT " << i << " " << text[i] << "}";

            back = true;
            if (back) {
                currentNode = currentNode->previous;
                back = false;
                if (currentNode == root) {
                    cout << "\t{MOVE BACK: root}";
                } else {
                    cout << "\t{MOVE BACK: " << pattern.substr(currentNode->start, nodeSize(currentNode)) << "[" << currentNode->start << ", " << currentNode->start + nodeSize(currentNode) - 1 << "]}";
                }
            }

            if (currentNode != root) {
                currentNode = currentNode->suffixLink;
                if (currentNode == root) {
                    cout << "\t{MOVE SL: root}";
                } else {
                    cout << "\t{MOVE SL: " << pattern.substr(currentNode->start, nodeSize(currentNode)) << "[" << currentNode->start << ", " << currentNode->start + nodeSize(currentNode) - 1 << "]}";
                }

                if (currentNode != root) {
                    int delta = 0;
                    cout << "\n";
                    while (delta < compareIndex) {
                        if (compareIndex - delta <= nodeSize(currentNode)) {
                            shift = compareIndex - delta;
                            wordIndex += compareIndex;
                            delta = compareIndex;
                            cout << delta << " ci\n";
                        } else {
                            delta += nodeSize(currentNode);
                            cout << delta << " ns\n";
                            currentNode = currentNode->next[text[i + delta]];
                        }
                    }

                    bool flag = false;
                    result[i] = result[i - 1] - 1;
                    for (compareIndex = shift;  compareIndex + wordIndex < text.size() && compareIndex < nodeSize(currentNode); compareIndex++) {
                        if (text[compareIndex + wordIndex] != pattern[currentNode->start + compareIndex]) {
                            flag = true;
                            break;
                        } else {
                            result[i]++;
                        }
                    }
//                    result[i] += compareIndex;
                    if (flag) {
                        cout << "\t{BACK ci: " << compareIndex << "}";
                        back = true;
                        break;
                    } else {
                        if (compareIndex + wordIndex == text.size()) {
                            cout << "\t{END TEXT}";
                            if (compareIndex < nodeSize(currentNode)) {
                                back = true;
                            }
                            break;
                        }
                        if (compareIndex == nodeSize(currentNode)) {
                            cout << "\t{END NODE}";
                            wordIndex += compareIndex;
                        }
                    }
                }
            }

//            if (currentNode != root && result[i-1] > 1) {
//                wordIndex++;
//                result[i]++;
//                cout << "\n{wi++: " << wordIndex << " " << text[wordIndex] << "}";
//            }
            // compareIndex = result[i - 1] - 1;
            while (wordIndex < text.size()) {
                if (currentNode == root) {
                    cout << "\n{" << wordIndex << ", " << text[wordIndex] << "} [root]";
                } else {
                    cout << "\n{" << wordIndex << ", " << text[wordIndex] << "} " << pattern.substr(currentNode->start, nodeSize(currentNode)) << "[" << currentNode->start << ", " << currentNode->start + nodeSize(currentNode) - 1 << "]";
                }
                if (currentNode->next.find(text[wordIndex]) != currentNode->next.end()) {
                    currentNode = currentNode->next[text[wordIndex]];
                    cout << "\t{FOUND NEXT: " << pattern.substr(currentNode->start, nodeSize(currentNode)) << "[" << currentNode->start << ", " << currentNode->start + nodeSize(currentNode) - 1 << "]}";

                    bool flag = false;
//                    if (result[i-1] > 0) {
//                        compareIndex = result[i-1]-1;
//                    } else {
//                        compareIndex = 0;
//                    }
                    for (compareIndex = 0;  compareIndex + wordIndex < text.size() && compareIndex < nodeSize(currentNode); compareIndex++) {
                        if (text[compareIndex + wordIndex] != pattern[currentNode->start + compareIndex]) {
                            flag = true;
                            break;
                        }
                    }
                    result[i] += compareIndex;
                    if (flag) {
                        cout << "\t{BACK ci: " << compareIndex << "}";
                        back = true;
                        break;
                    } else {
                        if (compareIndex + wordIndex == text.size()) {
                            cout << "\t{END TEXT}";
                            if (compareIndex < nodeSize(currentNode)) {
                                back = true;
                            }
                            break;
                        } 
                        if (compareIndex == nodeSize(currentNode)) {
                            cout << "\t{END NODE}";
                            wordIndex += compareIndex;
                        }
                    }
                } else {
                    cout << "\t{NOT FOUND NEXT}";
                    break;
                }
            }
        }
        return result;
    }

    vector<int> Find1(string text) {
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
                    currentNode = currentNode->next[pattern[prevStart]];
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
                    if (text[compareIndex + wordIndex] != pattern[currentNode->start + compareIndex]) {
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
                        wordIndex += compareIndex;

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
//    text = "aobbaoababba";
//    pattern = "baobab";
    cin >> pattern >> text;
    cout << "text: " << text << "\npattern: " << pattern << "; size:" << pattern.size() << "\n";

    SuffixTree tree(pattern);
    tree.Print();
    vector<int> result = tree.Find1(text);
    cout << "\n";
    for (int i = 1; i < result.size(); i++) {
        cout << result[i] << " ";
//         if (result[i] == pattern.size()) {
//             cout << i << "\n";
//         }
    }
    cout << "\n";

    return 0;
}