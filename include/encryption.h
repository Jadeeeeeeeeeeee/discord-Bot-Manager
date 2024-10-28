#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encrypt {
public:
    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& ciphertext);
};

#endif 
