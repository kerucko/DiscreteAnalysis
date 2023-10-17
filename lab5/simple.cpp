#include <iostream>
#include <string>

using namespace std;

void findOccurrences(const string& text, const string& pattern) {
    int patternLength = pattern.length();
    int textLength = text.length();

    for(int i = 0; i <= textLength - patternLength; i++) {
        int j;
        for(j = 0; j < patternLength; j++) {
            if(text[i+j] != pattern[j])
                break;
        }
        if(j == patternLength)
            cout << i << endl;
    }
}

int main() {
    string text, pattern;
    cin >> text;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pattern;
        findOccurrences(text, pattern);
    }

    return 0;
}