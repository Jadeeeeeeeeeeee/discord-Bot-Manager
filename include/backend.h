#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>


class Backend {
public:
    void RegisterNewBot();
    void VerifyLogin();
    void getFileInfo();
    void createFile();
    std::string cutString(const std::string& a);
    std::string trim(const std::string& str);
    std::string LoginedInfo;
    std::string LoginedbotToken;
    std::string LoginedGuildId;
};


extern Backend backendInstence;

#endif
