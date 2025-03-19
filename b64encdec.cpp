//Code functions:
// - Encrypt and decrypt messages + files
// - Checks and informs user if file extension is valid
// (valid file extensions are .txt, .csv, .docx, and .rtf)
// How to use:
// (1) Download this program with the header.
// (2) Drop the file's content you want to encrypt or decrypt.

#include "b64head.h"
#include <cstring>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
#define SIZE 100000

const string b64_tb = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const vector<int> ascii_mapping {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, 
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, 
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1 
};
//includes all 128 characters, however invalid/exclusive ones are marked as -1


string b64_encstr(const string& plain_text) {
    string encrypted_text;
    int val = 0, b_val = -6;
    for (unsigned char ch : plain_text) {
        val = (val << 8) + ch;
        b_val += 8;
        while (b_val >= 0) {
            encrypted_text.push_back(b64_tb[(val >> b_val) & 63]);
            b_val -= 6;
        }
    }
    if (b_val > -6) {
        encrypted_text.push_back(b64_tb[(val << 8) >> (b_val + 8) & 63]);
    }
    while (encrypted_text.size() % 4 != 0) {
        encrypted_text.push_back('=');
    }
    return encrypted_text;
}

string b64_encf(vector<unsigned char>& original_cont) {
    string encrypted_cont;
    int val = 0, b_val = -6;
    for (unsigned char ch : original_cont) {
        val = (val << 8) + ch;
        b_val += 8;
        while (b_val >= 0) {
            encrypted_cont.push_back(b64_tb[(val >> b_val) & 63]); //val * [2^(b_val)] & 63
            b_val -= 6; //b_val = -4
        }
    }
    if (b_val > -6) {
        encrypted_cont.push_back(b64_tb[(val << 8) >> (b_val + 8) & 63]); //[val * 64] / 2^[b_val + 8] & 63
    }
    while (encrypted_cont.size() % 4 != 0) {
        encrypted_cont.push_back('=');
    }
    return encrypted_cont;
}

string b64_decstr(const string& encrypted_text) {
    string decrypted_string;
    vector<int> table(256, -1);
    for (int i = 0; i < 64; i++) table[b64_tb[i]] = i; 
    int val = 0, b_val = 8;
    for (char c : encrypted_text) {
        if (table[c] == -1) break;
        int i = (c < 128) ? ascii_mapping[c] : -1;
        if (i == -1) {
            throw runtime_error("Invalid B64 character.");
        }
        val = (val << 6) + table[c];
        b_val += 6; 
        if (b_val >= 0) {
            decrypted_string.push_back(char((val>>b_val)&255)); //0xFF = 255
            b_val -= 8;
        }
    }
    return decrypted_string;
}

string b64_decf(vector <unsigned char>& encrypted_cont) {
    string decrypted_cont;
    vector<int> table(256, -1);
    for (int i = 0; i < 64; i++) table[b64_tb[i]] = i;
    int val = 0, b_val = 8;
    for (char c : encrypted_cont) {
        if (table[c] == -1) break;
        val = (val << 6) + table[c];
        b_val += 6; 
        if (b_val >= 0) {
            decrypted_cont.push_back(char((val>>b_val)&255)); //0xFF = 255
            b_val -= 8;
        }
    }
    return decrypted_cont;
}

vector<unsigned char> readf(const string& fn) {
    ifstream file(fn, ios::binary);
    vector<unsigned char> temp_store((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return temp_store;
}

void encf(const string& fn, const string& decrypted_cont) {
    ofstream file(fn);
    file << decrypted_cont;
}

void decf(const string& fn, const string& encrypted_cont) {
    ofstream file(fn);
    file << encrypted_cont;
}

bool fileExtCheck (const string& fn, const vector<string>& file_ext) {
    for (const auto& e : file_ext) {
        if((fn).find(e) != string::npos) { //npos - until end of string
            return true;
        }
    }
    return false;
}

int main() {
    string inp_opt;
    cout << "1) Encrypt a file's content/message" << endl;
    cout << "2) Decrypt a file's content/message" << endl;
    cin >> inp_opt;
    if (inp_opt == "1") {
        string enc_opt;
        cout << "1) Encrypt a file's content" << endl;
        cout << "2) Encrypt a message" << endl;
        cin >> enc_opt;
        if (enc_opt == "1") {
            ifstream original_file;
            string file, fn;
            vector<string>file_ext = {".txt", ".csv", ".docx", ".rtf"};
            cout << "Enter file name with appropriate file extensions: ";
            cin >> fn;
            original_file.open(fn);
            if (fileExtCheck (fn, file_ext)) {
                if (original_file) {
                    vector<unsigned char> original_cont = readf(fn);
                    string encoded_cont = b64_encf(original_cont);
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
        } else if (enc_opt == "2") {
            string plain_text;
            cout << "Enter plain text: ";
            cin >> plain_text;
            string encoded_text = b64_encstr(plain_text);
            cout << encoded_text << endl;
        }
    }
    if (inp_opt == "2") {
        string enc_opt;
        cout << "1) Decrypt a file's content" << endl;
        cout << "2) Decrypt a message" << endl;
        cin >> enc_opt;
        if (enc_opt == "1") {
            ifstream encrypted_file;
            string file, fn;
            vector<string>file_ext = {".txt", ".csv", ".docx", ".rtf"};
            cout << "Enter file name with appropriate file extensions: ";
            cin >> fn;
            encrypted_file.open(fn);
            if (fileExtCheck (fn, file_ext)) {
                if (encrypted_file) {
                    vector<unsigned char> original_cont = readf(fn);
                    string decrypted_cont = b64_decf(original_cont);
                    string output_file = "decrypted.txt";
                    decf(output_file, decrypted_cont);
                    cout << "Finished decrypting original file contents." << endl;
                } else {
                    cout << "ERROR: File does not exist.";
                    exit(-1);
                }
            } else {
                cout << "ERROR: Invalid file extension.";
                exit(-1);
            }
        } else if (enc_opt == "2") {
            string encrypted_text;
            cout << "Enter encrypted text: ";
            cin >> encrypted_text;
            string decrypted_text = b64_decstr(encrypted_text);
            cout << decrypted_text << endl;
        }
    }
    return 0;
}
