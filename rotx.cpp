#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

string rotx_str(const string& plain_text, int x) {
    string encoded_text;
    int len_plain = plain_text.length();
    for (int i = 0; i < len_plain; i++) {
        if (plain_text[i] >= 'a' && plain_text[i] <= 'z') {
            encoded_text += char(plain_text[i] + x - 'a') % 26 + 'a';
        } if (plain_text[i] >= 'A' && plain_text[i] <= 'Z') {
            encoded_text += char(plain_text[i] + x - 'A') % 26 + 'A';
        }
    }
    return encoded_text;
}

string rotx_f(vector<unsigned char>& original_cont, int x) {
    string encoded_cont;
    int len_plain = original_cont.size();
    for (int i = 0; i < len_plain; i++) {
        if (original_cont[i] >= 'a' && original_cont[i] <= 'z') {
            encoded_cont += char(original_cont[i] + x - 'a') % 26 + 'a';
        } if (original_cont[i] >= 'A' && original_cont[i] <= 'Z') {
            encoded_cont += char(original_cont[i] + x - 'A') % 26 + 'A';
        }
    }
    return encoded_cont;
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
                int step;
                cout << "Enter key: ";
                cin >> step;
                string encoded_cont = rotx_f(original_cont, step);
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
        int step;
        cout << "Enter key: ";
        cin >> step;
        string encoded_text = rotx_str(plain_text, step);
        cout << encoded_text << endl;
    } else {
        cout << "Invalid input. Try again.\n";
        return main();
    }
    return 0;
}
