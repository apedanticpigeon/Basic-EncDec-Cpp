#ifndef _B64HEAD_ //used to compile a section only if a particular expression has not been defined
#define _B64HEAD_

#include <vector>
#include <string>
using namespace std;
typedef unsigned char b;

string b64_encrypt(b const* buff, unsigned int buffLen);
vector<b> b64_decrypt(string const&);

#endif