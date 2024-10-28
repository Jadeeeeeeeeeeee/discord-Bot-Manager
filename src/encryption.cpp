#include "../include/encryption.h"
#include "../include/backend.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string base64_encode(const std::vector<uint8_t>& input) {
    if (input.empty()) return "";

    std::string encoded;
    encoded.reserve(((input.size() + 2) / 3) * 4);

    size_t i = 0;
    for (; i + 2 < input.size(); i += 3) {
        encoded.push_back(base64_chars[(input[i] >> 2) & 0x3F]);
        encoded.push_back(base64_chars[((input[i] & 0x3) << 4) | ((input[i + 1] & 0xF0) >> 4)]);
        encoded.push_back(base64_chars[((input[i + 1] & 0xF) << 2) | ((input[i + 2] & 0xC0) >> 6)]);
        encoded.push_back(base64_chars[input[i + 2] & 0x3F]);
    }

    if (i < input.size()) {
        encoded.push_back(base64_chars[(input[i] >> 2) & 0x3F]);
        if (i + 1 < input.size()) {
            encoded.push_back(base64_chars[((input[i] & 0x3) << 4) | ((input[i + 1] & 0xF0) >> 4)]);
            encoded.push_back(base64_chars[(input[i + 1] & 0xF) << 2]);
        }
        else {
            encoded.push_back(base64_chars[(input[i] & 0x3) << 4]);
            encoded.push_back('=');
        }
        encoded.push_back('=');
    }

    return encoded;
}

std::vector<uint8_t> base64_decode(const std::string& input) {
    if (input.empty()) return std::vector<uint8_t>();

    std::vector<uint8_t> decoded;
    decoded.reserve((input.size() * 3) / 4);

    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) {
        T[base64_chars[i]] = i;
    }

    uint32_t val = 0;
    int valb = -8;

    for (unsigned char c : input) {
        if (c == '=') break;
        if (T[c] == -1) continue;

        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            decoded.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }

    return decoded;
}

std::string Encrypt::encrypt(const std::string& plaintext) {
    if (plaintext.empty() || backendInstence.key.empty()) {
        std::cerr << "Error: Empty plaintext or key" << std::endl;
        return "";
    }

    std::vector<uint8_t> data(plaintext.begin(), plaintext.end());
    std::vector<uint8_t> key(backendInstence.key.begin(), backendInstence.key.end());

    if (key.size() != 72) {
        std::cerr << "Error: Invalid key length: " << key.size() << std::endl;
        return "";
    }

    std::vector<uint8_t> encrypted;
    encrypted.reserve(data.size());

    for (size_t i = 0; i < data.size(); i++) {
        encrypted.push_back(data[i] ^ key[i % key.size()]);
    }

    return base64_encode(encrypted);
}

std::string Encrypt::decrypt(const std::string& ciphertext) {
    if (ciphertext.empty() || backendInstence.key.empty()) {
        std::cerr << "Error: Empty ciphertext or key" << std::endl;
        return "";
    }

    std::vector<uint8_t> key(backendInstence.key.begin(), backendInstence.key.end());

    if (key.size() != 72) {
        std::cerr << "Error: Invalid key length: " << key.size() << std::endl;
        return "";
    }

    std::vector<uint8_t> decoded = base64_decode(ciphertext);
    if (decoded.empty()) {
        std::cerr << "Error: Base64 decoding failed" << std::endl;
        return "";
    }

    std::vector<uint8_t> decrypted;
    decrypted.reserve(decoded.size());

    for (size_t i = 0; i < decoded.size(); i++) {
        decrypted.push_back(decoded[i] ^ key[i % key.size()]);
    }

    return std::string(decrypted.begin(), decrypted.end());
}