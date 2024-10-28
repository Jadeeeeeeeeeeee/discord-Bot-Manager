#include <iostream>


#ifndef BACKEND_H
#define BACKEND_H


class Backend {
public:
    void RegisterNewBot();
    void VerifyLogin();
    void getFileInfo();
    void createFile();
    void SetFilePermissions(const std::string& filePath);
    std::string cutString(const std::string& a);
    std::string trim(const std::string& str);
    std::string LoginedInfo;
    std::string LoginedbotToken;
    std::string LoginedGuildId;
    std::string key;
};


extern Backend backendInstence;

#endif
