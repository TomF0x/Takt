#include <iostream>
#include <iomanip>
#include <fstream>
#include "modes.h"
#include "aes.h"
#include "filters.h"
#include "sstream"
#include "base64.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
using std::filesystem::recursive_directory_iterator;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    string path = "./";
    fstream fin, fout;
    char c;
    int nb_file =0;
    CryptoPP::byte key[32], iv[32];
    memset(key, 20, 32);
    memset(iv, 112584871684, 32);

    if (argc == 1) {
        string encoded;
        for (const auto& file : recursive_directory_iterator(path)) {
            string ciphertext, text;
            fin.open(fs::absolute(file), fstream::in);
            while (fin >> noskipws >> c) {
                text += c;
            }
            fin.close();
            CryptoPP::AES::Encryption aesEncryption(key, 32);
            CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
            CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
            stfEncryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.length());
            stfEncryptor.MessageEnd();
            std::string encoded = base64_encode(ciphertext);
            fout.open(std::filesystem::absolute(file), fstream::out);
            fout << encoded;
            fout.close();
            nb_file += 1;
        }
        cout << "Encrypted files: " << nb_file << endl;
        exit(0);
    }
    else if (argc == 2) {
        for (const auto& file : recursive_directory_iterator(path)) {
            string decryptedtext, text;
            try {
                fin.open(fs::absolute(file), fstream::in);
                while (fin >> noskipws >> c) {
                    text += c;
                }
                fin.close();
                std::string decoded = base64_decode(text);
                CryptoPP::AES::Decryption aesDecryption(key, 32);
                CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
                CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
                stfDecryptor.Put(reinterpret_cast<const unsigned char*>(decoded.c_str()), decoded.size());
                stfDecryptor.MessageEnd();
                fout.open(fs::absolute(file), fstream::out);
                fout << decryptedtext;
                fout.close();
                nb_file += 1;
            }
            catch (...){}
        }
        cout << "Decrypted files: " << nb_file << endl;
        exit(0);
    }
    return 0;
}