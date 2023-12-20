#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct encode {
    int position;
    int length;
    char symbol;

    encode(int position, int length, char symbol) {
        this->position = position;
        this->length = length;
        this->symbol = symbol;
    }
};


int maxSub(string text, int firstStart, int secondStart) {
    for (int i = 0; i + firstStart < text.size() && i + secondStart < text.size(); i++) {
        if (text[i + firstStart] != text[i + secondStart]) {
            return i;
        }
    }
    return text.size() - secondStart;
}

vector<encode> compress(string text) {
    vector<encode> result;
    map<char, vector<int> > dictionary;
    for (int i = 0; i < text.size(); i++) {
        if (dictionary.find(text[i]) == dictionary.end()) {
            result.push_back(encode(0, 0, text[i]));
            dictionary[text[i]] = vector<int>();
            dictionary[text[i]].push_back(i);
        } else {
            vector<int> positions = dictionary[text[i]];
            int mx = 0;
            int mx_pos = 0;
            for (int k = 0; k < positions.size(); k++) {
                int temp = maxSub(text, positions[k], i);
                if (temp >= mx) {
                    mx = temp;
                    mx_pos = positions[k];
                }
            }
            if (i + mx >= text.size()) {
                result.push_back(encode(i - mx_pos, mx, '\0'));
            } else {
                result.push_back(encode(i - mx_pos, mx, text[i + mx]));
            }
            for (int k = 0; k <= mx; k++) {
                if (dictionary.find(text[i + k]) == dictionary.end()) {
                    dictionary[text[i + k]] = vector<int>();
                }
                dictionary[text[i + k]].push_back(i + k);
            }
            i += mx;
        }
    }
    return result;
}

string decompress(vector<encode> code) {
    string text;

    for (int i = 0; i < code.size(); i++) {
        if (code[i].length > 0) {
            int start_position = text.length();
            for (int j = 0; j < code[i].length; j++) {
                text += text[start_position - code[i].position + j];
            }
        }
        if (code[i].symbol != '\0') {
            text += code[i].symbol;
        }
    }
    
    return text;
}


int main() {
    string mod;
    cin >> mod;
    if (mod == "compress") {
        string text;
        getchar();
        getline(cin, text);
        vector<encode> result = compress(text);
        for (int i = 0; i < result.size(); i++) {
            if (result[i].symbol > 'z' || result[i].symbol < 'a') {
                cout << result[i].position << " " << result[i].length << " \n";
            } else {
                cout << result[i].position << " " << result[i].length << " " << result[i].symbol << "\n";
            }
        }
    } else {
        vector<encode> code;
        int position, length;
        char symbol;
        while(cin >> position >> length) {
            cin >> symbol;
            code.push_back(encode(position, length, symbol));
        }
        if (code[code.size() - 1].symbol == code[code.size() - 2].symbol) {
            code[code.size() - 1].symbol = '\0';
        }

        string text = decompress(code);
        cout << text << endl;
    }
    return 0;
}