#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class vigenere {
    public:
    string plainKey;
    vigenere (string plainKey){
        for (char ch : plainKey) {
            if (ch >= 'a' && ch <= 'z') this->plainKey += ch + 'A' - 'a';
            else if (ch >= 'A' && ch <= 'Z') this->plainKey += ch; //ignores non-alphabetic characters
        }
    }
    string v_enc(string plain) {
        string encoded;
        int i, j;
        for (i = 0, j = 0; i < plain.length(); ++i) {
            char ch = plain[i];
            if (ch >= 'a' && ch <= 'z') ch += 'A' - 'a';
            if (ch < 'A' || ch > 'Z') continue;
            encoded += (ch + plainKey[j] - 2 * 'A') % 26 + 'A';
            j = (j + 1) % plainKey.length();
        }
        return encoded;
    }
    string v_dec(string encoded) {
        string decoded;
        int i, j;
        for (i = 0, j = 0; i < encoded.length(); ++i) {
            char ch = encoded[i];
            if (ch >= 'a' && ch <= 'z') ch += 'A' - 'a';
            if (ch < 'A' || ch > 'Z') continue;
            decoded += (ch - plainKey[j] + 26) % 26 + 'A';
            j = (j + 1) % plainKey.length();
        }
        return decoded;
    }

    string v_encf(vector<unsigned char>& original_cont) {
        string encoded_cont;
        int i, j;
        for (i = 0, j = 0; i < original_cont.size(); ++i) {
            char ch = original_cont[i];
            if (ch >= 'a' && ch <= 'z') ch += 'A' - 'a';
            if (ch < 'A' || ch > 'Z') continue;
            encoded_cont += (ch + plainKey[j] - 2 * 'A') % 26 + 'A';
            //each character from encoded_text is added by each iteration (1 to j) of plain_key to
            //decode it and convert output to all uppercase letters
            //2 * 65 (ASCII value of A) =  130
            //where 65 + 90 (A + Z) = 155, 26 - 1 = 25 (distance from A to Z), 155 - 25 = 130 (range)
            j = (j + 1) % plainKey.length();
        }
        return encoded_cont;
    }

    string v_decf(string encoded_cont) {
        string decoded_cont;
        int i, j;
        for (i = 0, j = 0; i < encoded_cont.size(); ++i) {
            char ch = encoded_cont[i];
            if (ch >= 'a' && ch <= 'z') ch += 'A' - 'a';
            if (ch < 'A' || ch > 'Z') continue;
            decoded_cont += (ch - plainKey[j] + 26) % 26 + 'A';
            j = (j + 1) % plainKey.length();
            //increase iteration of j that follows length of key, so there will be repeated index of iteration.
            //e.g. if plain_key.length() is 5, the iteration will be 0 to 4 repeatedly
        }
        return decoded_cont;
    }

    vector<unsigned char> readf(const string& fn) {
        ifstream file(fn, ios::binary);
        vector<unsigned char> temp_store ((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        //read every characters in every iteration and store it into vector temp_store
        return temp_store; 
    }

    void encf(const string& fn, const string& decoded_cont) {
        ofstream file(fn); //write filename into file
        file << decoded_cont; //write original contents into file
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
};

int main() {
    int choice;
    cout << "1) Encode file or plaintext\n";
    cout << "2) Decode file or plaintext\n";
    cin >> choice;
    cin.ignore();
   
    if (choice == 1) {
        int i_type;
        cout << "Encode file's content or message? ";
        cin >> i_type;
        if (i_type == 1) {
            string key;
            ifstream original_file;
            string file, fn;
            vector<string>file_ext = {".txt", ".csv", ".docx", ".rtf"};
            cout << "Enter key: ";
            cin.ignore();
            getline(cin, key);
            vigenere k(key);
            cout << "Enter file name with appropriate file extensions: ";
            cin >> fn;
            original_file.open(fn);
            if (k.fileExtCheck (fn, file_ext)) {
                if (original_file) {
                    vector<unsigned char> original_cont = k.readf(fn);
                    string encoded_cont = k.v_encf(original_cont);
                    string output_file = "encoded.txt";
                    k.encf(output_file, encoded_cont);
                    cout << "Finished encoding original file contents." << endl;
                } else {
                    cout << "ERROR: File does not exist.";
                    exit(-1);
                }
            } else {
                cout << "ERROR: Invalid file extension.";
                exit(-1);
            }
        } else if (i_type == 2) {
            string key;
            string plaintext;
            cout << "Enter key: ";
            cin.ignore();
            getline(cin, key);
            vigenere k(key);
            cout << "Enter original message: ";
            getline(cin, plaintext);
            string encode = k.v_enc(plaintext);
            cout << "Encoded message: " << encode << endl;
        } else {
            cout << "Invalid input.";
            exit(-1);
        }
    } else if (choice == 2) {
        int i_type;
        cout << "Decode file's content or message? ";
        cin >> i_type;
        if (i_type == 1) {
            string key;
            ifstream encoded_file;
            string file, fn;
            vector<string>file_ext = {".txt", ".csv", ".docx", ".rtf"};
            cout << "Enter key: ";
            cin.ignore();
            getline(cin, key);
            vigenere k(key);
            cout << "Enter file name with appropriate file extensions: ";
            cin >> fn;
            encoded_file.open(fn);
            if (k.fileExtCheck (fn, file_ext)) {
                if (encoded_file) {
                    vector<unsigned char> encoded_cont = k.readf(fn);
                    string decoded_cont = k.v_encf(encoded_cont);
                    string output_file = "decoded.txt";
                    k.encf(output_file, decoded_cont);
                    cout << "Finished decoding original file contents." << endl;
                } else {
                    cout << "ERROR: File does not exist.";
                    exit(-1);
                }
            } else {
                cout << "ERROR: Invalid file extension.";
                exit(-1);
            }
        }
        else if (i_type == 2) {
            string key;
            string encoded_message;
            cout << "Enter key: ";
            cin.ignore();
            getline(cin, key);
            vigenere k(key);
            cout << "Enter encoded text: ";
            getline(cin, encoded_message);
            string decode = k.v_dec(encoded_message);
            cout << "Decoded message: " << decode << endl;
        }
    }
    return 0;

}
