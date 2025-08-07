#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <map>
using namespace std;

map<char, char>atbash_table = { {'A', 'Z'}, {'B', 'Y'}, {'C', 'X'}, {'D', 'W'}, {'E', 'V'}, {'F', 'U'}, {'G', 'T'}, {'H', 'S'}, {'I', 'R'}, {'J', 'Q'},
{'K', 'P'}, {'L', 'O'}, {'M', 'N'}, {'N', 'M'}, {'O', 'L'}, {'P', 'K'}, {'Q', 'J'}, {'R', 'I'}, {'S', 'H'}, {'T', 'G'}, {'U', 'F'}, {'V', 'E'}, 
{'W', 'D'}, {'X', 'C'}, {'Y', 'B'}, {'Z', 'A'}};

string atbash_str (const string& text) {
    string output_text;
    for (char ch : text) {
        if (ch != ' ') {
            if(ch >= 'a' && ch <= 'z') {
                output_text += atbash_table[(ch) - 32];
            } if (ch >= 'A' && ch <= 'z') {
                output_text += atbash_table[(ch)];
            } else {
                output_text += ' ';
            }
        }
    }
    return output_text;
}

string atbash_f (vector<unsigned char>& cont) {
    string output_cont;
    for (char ch : cont) {
        if (ch != ' ') {
            if(ch >= 'a' && ch <= 'z') {
                output_cont += atbash_table[(ch) - 32];
            } if (ch >= 'A' && ch <= 'z') {
                output_cont += atbash_table[(ch)];
            } else {
                output_cont += ' ';
            }
        }
    }
    return output_cont;
}

vector<unsigned char> readf(const string& fn) {
    ifstream file(fn, ios::binary);
    vector<unsigned char> temp_store((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return temp_store;
}

void encf(const string& fn, const string& decoded_cont) {
    ofstream file(fn);
    file << decoded_cont;
}
    
void decf(const string& fn, const string& encoded_cont) {
    ofstream file(fn);
    file << encoded_cont;
}

bool fileExtCheck(const string& fn, const vector<string>& file_ext) {
    for (const auto& e: file_ext) {
        if((fn).find(e) != string::npos) return true;
    }
    return false;
}

int main () {
    int input_type;
    cout << "Encode/Decode file's content or message? ";
    cin >> input_type;
    if (input_type == 1) {
        ifstream original_file;
        string file, fn;
        vector<string>file_ext = {".txt", ".csv", ".docx", ".rtf"};
        cout << "Enter file name with appropriate file extensions: ";
        cin >> fn;
        if (fileExtCheck (fn, file_ext)) {
            if (original_file) {
                vector<unsigned char> original_cont = readf(fn);
                string encoded_cont = atbash_f(original_cont);
                string output_file = "encoded.txt";
                encf(output_file, encoded_cont);
                cout << "Finished encoding original file contents." << endl;
            } else {
                cout << "ERROR: File does not exist.";
                exit(-1);
            }
        } else {
            cout << "ERROR: Invalid file extension.";
            exit(-1);
        }
    } else if (input_type == 2) {
        string plain_text;
        cout << "Enter plain text: ";
        cin >> plain_text;
        string encoded_text = atbash_str(plain_text);
        cout << encoded_text << endl;
    } else {
        cout << "Invalid input. Try again.\n";
        return main();
    }
    return 0;
}
