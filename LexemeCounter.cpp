#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
using namespace std;

bool isValidIdentifier(const string &word) {
    if (isalpha(word[0]) || word[0] == '_') {
        for (size_t i = 1; i < word.length(); ++i) {
            char c = word[i];
            if (!(isalnum(c) || c == '_')) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int countLines(const string &filename) {
    ifstream file(filename.c_str()); 
    if (!file.is_open()) {
        cerr << "Unable to open the file: " << filename << endl;
        return -1; 
    }

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        lineCount++;
    }

    file.close();
    return lineCount;
}

int main() {
    const char* reservedWords[] = {"if", "else", "for", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "sizeof", "volatile", "typedef", "enum", "const", "union", "extern", "bool"};
    const char operators[] = {'+', '-', '*', '/', '%', '=', '>', '<', '&', '|', '!', '(', '{', '['};
    
    int reservedWordsCount[28] = {0};
    int operatorsCount[14] = {0};
    vector<string> identifiers;
    vector<int> identifierCount;

    string file_path;
    cout << "Enter the file path: ";
    getline(cin, file_path);

    ifstream file(file_path.c_str());

    if (file.is_open()) {
        string word;
        while (file >> word) {
            bool isReserved = false;
            for (int i = 0; i < 28; ++i) {
                if (word == reservedWords[i]) {
                    reservedWordsCount[i]++;
                    isReserved = true;
                    break;
                }
            }
            if (!isReserved) {
                bool isOperator = false;
                for (int i = 0; i < 14; ++i) {
                    for (size_t j = 0; j < word.length(); ++j) {
                        if (word[j] == operators[i]) {
                            operatorsCount[i]++;
                            isOperator = true;
                            break;
                        }
                    }
                }
                if (!isOperator && isValidIdentifier(word)) {
                    bool found = false;
                    for (size_t i = 0; i < identifiers.size(); ++i) {
                        if (identifiers[i] == word) {
                            identifierCount[i]++;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        identifiers.push_back(word);
                        identifierCount.push_back(1);
                    }
                }
            }
        }
        file.close();

        cout << "\nReserved Words: " << endl;
        int reservedWordsSubtotal = 0;
        for (int i = 0; i < 28; ++i) {
            if (reservedWordsCount[i] > 0) {
                cout << reservedWords[i] << ": " << reservedWordsCount[i] << endl;
                reservedWordsSubtotal += reservedWordsCount[i];
            }
        }
        cout << "\nReserved Words Subtotal: " << reservedWordsSubtotal << endl;

        cout << "\nOperators: " << endl;
        int operatorsSubtotal = 0;
        for (int i = 0; i < 14; ++i) {
            if (operatorsCount[i] > 0) {
                cout << operators[i] << ": " << operatorsCount[i] << endl;
                operatorsSubtotal += operatorsCount[i];
            }
        }
        cout << "\nOperators Subtotal: " << operatorsSubtotal << endl;

        cout << "\nIdentifiers: " << endl;
        int identifiersSubtotal = 0;
        for (size_t i = 0; i < identifiers.size(); ++i) {
            cout << identifiers[i] << ": " << identifierCount[i] << endl;
            identifiersSubtotal += identifierCount[i];
        }
        cout << "\nIdentifiers Subtotal: " << identifiersSubtotal << endl;
        cout<<"\nTotal Number of Lines: "<<countLines(file_path)<<endl;
        cout<<"Lexemes Grand Total: "<<reservedWordsSubtotal+operatorsSubtotal+identifiersSubtotal<<endl;
        
    } else {
        cout << "Unable to open file." << endl;
    }

    return 0;
}
