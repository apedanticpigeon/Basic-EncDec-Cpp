#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#define MAX_LEN 1024
using namespace std;


int inverse (int n) {
    for (int i = 0; i < 26; i++) {
        int f = (n * i) % 26;
        if (f == 1) {
            return i;
        }
    }
    return -1;
}

string affine_encstr(const string& plain_text, int a, int b) {
    string encoded_text;
    int len_plain = plain_text.length();
    for (int i = 0; i < len_plain; i++) {
        if (plain_text[i] >= 'a' && plain_text[i] <= 'z') {
            encoded_text += char(((a * plain_text[i] - 'a') + b) % 26) + 'a';
        } if (plain_text[i] >= 'A' && plain_text[i] <= 'Z') {
            encoded_text += char(((a * plain_text[i] - 'A') + b) % 26) + 'A';
        }
    }
    return encoded_text;
}

string affine_decstr(const string& encoded_text, int a, int b) {
    string decoded_text;
    int inverse_a = inverse(a);
    if (inverse_a == -1) {
        cout << "Key invalid/does not exist.";
    }
    int len_enc = encoded_text.length();
    for (int i = 0; i < len_enc; i++) {
        if (encoded_text[i] >= 'a' && encoded_text[i] <= 'z') {
            decoded_text += char(inverse_a * (encoded_text[i] + 'a' - b) % 26) + 'a';
        } if (encoded_text[i] >= 'A' && encoded_text[i] <= 'Z') {
            decoded_text += char(inverse_a * (encoded_text[i] + 'A' - b) % 26) + 'A';
        }
    }
    return decoded_text;
}

string affine_encf(vector<unsigned char>& original_cont, int a, int b) {
    string encoded_cont;
    int len_plain = original_cont.size();
    for (int i = 0; i < len_plain; i++) {
        if (original_cont[i] >= 'a' && original_cont[i] <= 'z') {
            encoded_cont += char(((a * original_cont[i] - 'a') + b) % 26) + 'a';
        } if (original_cont[i] >= 'A' && original_cont[i] <= 'Z') {
            encoded_cont += char(((a * original_cont[i] - 'A') + b) % 26) + 'A';
        }
    }
    return encoded_cont;
}

string affine_decf(vector<unsigned char>& encoded_cont, int a, int b) {    
    string decoded_cont;
    int inverse_a = inverse(a);
    if (inverse_a == -1) {
        cout << "Key invalid/does not exist.";
    }
    int len_enc = encoded_cont.size();
    for (int i = 0; i < len_enc; i++) {
        if (encoded_cont[i] >= 'a' && encoded_cont[i] <= 'z') {
            decoded_cont += char(inverse_a * (encoded_cont[i] + 'a' - b) % 26) + 'a';
        } if (encoded_cont[i] >= 'A' && encoded_cont[i] <= 'Z') {
            decoded_cont += char(inverse_a * (encoded_cont[i] + 'A' - b) % 26) + 'A';
        }
    }
    return decoded_cont;
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
    int choice;
    cout << "1) Encode file or plaintext\n";
    cout << "2) Decode file or plaintext\n";
    cin >> choice;
    cin.ignore();
   
    if (choice == 1) {
        int enc_type;
        cout << "Encode file's content or message? ";
        cin >> enc_type;
        if (enc_type == 1) {
            ifstream original_file;
            string file, fn;
            vector<string>file_ext = {".txt", ".csv", ".docx", ".rtf"};
            cout << "Enter file name with appropriate file extensions: ";
            cin >> fn;
            if (fileExtCheck (fn, file_ext)) {
                if (original_file) {
                    vector<unsigned char> original_cont = readf(fn);
                    int x, y;
                    cout << "Enter key 1 (x): ";
                    cin >> x;
                    cout << "Enter key 2 (y): ";
                    cin >> y;
                    string encoded_cont = affine_encf(original_cont, x, y);
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
        } else if (enc_type == 2) {
            string plain_text;
            cout << "Enter plain text: ";
            cin >> plain_text; 
            int x, y;
            cout << "Enter key 1 (x): ";
            cin >> x;
            cout << "Enter key 2 (y): ";
            cin >> y;
            string encoded_text = affine_encstr(plain_text, x, y);
            cout << encoded_text << endl;
        } else {
            cout << "Invalid input. Try again.\n";
            return main();
        }
    }
    if (choice == 2) {
        int dec_type;
        cout << "Decode file or message? ";
        cin >> dec_type;
        if (dec_type == 1) {
            ifstream original_file;
            string file, fn;
            vector<string>file_ext = {".txt", ".csv", ".docx", ".rtf"};
            cout << "Enter file name with appropriate file extensions: ";
            cin >> fn;
            if (fileExtCheck (fn, file_ext)) {
                if (original_file) {
                    vector<unsigned char> original_cont = readf(fn);
                    int x, y;
                    cout << "Enter key 1 (x): ";
                    cin >> x;
                    cout << "Enter key 2 (y): ";
                    cin >> y;
                    string encoded_cont = affine_decf(original_cont, x, y);
                    string output_file = "decoded.txt";
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
        } else if (dec_type == 2) {
            string encoded_text;
            int x, y;
            cout << "Enter encoded text: ";
            cin >> encoded_text;
            cout << "Enter key 1 (x): ";
            cin >> x;
            cout << "Enter key 2 (y): ";
            cin >> y;
            string decoded_text = affine_decstr(encoded_text, x, y);
            cout << decoded_text << endl;
        }
    }
    return 0;
}
