#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

// Defining some functions to be used later on for calculations
#define rightRotate(num, rot) ((num >> rot) | (num << (32 - rot)))
#define W1(num) (rightRotate(num, 7) ^ rightRotate(num, 18) ^ (num >> 3))
#define W2(num) (rightRotate(num, 17) ^ rightRotate(num, 19) ^ (num >> 10))
#define S0(num) (rightRotate(num, 2) ^ rightRotate(num, 13) ^ rightRotate(num, 22))
#define S1(num) (rightRotate(num, 6) ^ rightRotate(num, 11) ^ rightRotate(num, 25))
#define Ch(x, y, z) ((x & y) ^ ((~x) & z))
#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

// Convert each character of string to binary and concatenating it
vector<unsigned long> convertToBinary(string message)
{
    vector<unsigned long> blocks;
    for (int i = 0; i < message.length(); i++)
    {
        bitset<8> b(message.c_str()[i]);
        blocks.push_back(b.to_ulong());
    }
    return blocks;
}

// Pads message to the nearest larger multiple of 512 bits
vector<unsigned long> padTo512Bits(vector<unsigned long> blocks)
{
    int len = blocks.size() * 8;
    string bigEndian;

    // Padding string to 512-64=448 bits
    int l = 447 - len;
    unsigned long t1 = 0x80;
    blocks.push_back(t1);
    l -= 7;
    for (int i = 0; i < l / 8; i++)
    {
        blocks.push_back(0x00000000);
    }

    // Pushing blocks to blocks array
    bitset<64> bigEndianBits(len);
    string bigEndianStr = bigEndianBits.to_string();
    for (int i = 0; i < 63; i += 8)
    {
        bitset<8> bigEndian8Block(bigEndianStr.substr(i, 8));
        blocks.push_back(bigEndian8Block.to_ulong());
    }
    return blocks;
}

// Convert 8-bit numbers to 32-bit blocks
vector<unsigned long> bit8To32(vector<unsigned long> blocks)
{
    vector<unsigned long> v(16);
    for (int i = 0; i < 64; i += 4)
    {
        bitset<32> temp(0);
        temp = (unsigned long)blocks[i] << 24;
        temp |= (unsigned long)blocks[i + 1] << 16;
        temp |= (unsigned long)blocks[i + 2] << 8;
        temp |= (unsigned long)blocks[i + 3];
        v[i / 4] = temp.to_ulong();
    }
    return v;
}

// Main hashing function
string computeHash(vector<unsigned long> blocks)
{
    // Initializing round constants
    vector<unsigned long> k = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
        0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
        0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
        0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
        0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

    // Initializing hash values
    vector<unsigned long> H = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    vector<unsigned long> W(64);

    for (int i = 0; i < 16; i++)
    {
        W[i] = blocks[i] & 0xFFFFFFFF;
    }

    // Modifying the zero elements W[16] and onwards
    for (int i = 16; i < 64; i++)
    {
        W[i] = W[i - 16] + W1(W[i - 15]) + W[i - 7] + W2(W[i - 2]);
        W[i] = W[i] & 0xFFFFFFFF; // Ensuring that the numbers are still 32-bit
    }

    // Starting compression
    unsigned long temp1;
    unsigned long temp2;
    unsigned long a = H[0];
    unsigned long b = H[1];
    unsigned long c = H[2];
    unsigned long d = H[3];
    unsigned long e = H[4];
    unsigned long f = H[5];
    unsigned long g = H[6];
    unsigned long h = H[7];

    // Main compression function
    for (int i = 0; i < 64; i++)
    {
        temp1 = h + S1(e) + Ch(e, f, g) + k[i] + W[i];
        temp2 = S0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = (d + temp1) & 0xFFFFFFFF; // Ensuring that number is still 32-bit
        d = c;
        c = b;
        b = a;
        a = (temp1 + temp2) & 0xFFFFFFFF; // Ensuring that number is still 32-bit
    }

    // Modifying the hash values
    H[0] = (H[0] + a) & 0xFFFFFFFF;
    H[1] = (H[1] + b) & 0xFFFFFFFF;
    H[2] = (H[2] + c) & 0xFFFFFFFF;
    H[3] = (H[3] + d) & 0xFFFFFFFF;
    H[4] = (H[4] + e) & 0xFFFFFFFF;
    H[5] = (H[5] + f) & 0xFFFFFFFF;
    H[6] = (H[6] + g) & 0xFFFFFFFF;
    H[7] = (H[7] + h) & 0xFFFFFFFF;

    // Preparing the final hash value to be returned
    stringstream ss;
    string ans;
    for (int i = 0; i < 8; i++)
    {
        ss << hex << setw(8) << setfill('0') << H[i];
    }
    ss >> ans;
    return ans;
}

// Wrapper function
string hashMessage(string message)
{
    vector<unsigned long> blocks;
    blocks = convertToBinary(message);
    blocks = padTo512Bits(blocks);
    blocks = bit8To32(blocks);
    string hashedMessage = computeHash(blocks);
    return hashedMessage;
}

int main()
{
    string message;

    // For debugging purpose
    cout << "Enter message to be hashed: ";
    getline(cin, message);
    cout << "Hashed message: " << hashMessage(message);

    // fstream inputfile, outputfile;
    // inputfile.open("input.txt", ios::in);
    // outputfile.open("output.txt");
    // if (inputfile.is_open())
    // {
    //     while (getline(inputfile, message))
    //     {
    //         outputfile << hashMessage(message) << "\n";
    //     }
    // }
    // inputfile.close();
    // outputfile.close();
}