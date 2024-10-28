#include "../include/backend.h"
#include "../include/ActionManager.h"
#include "../include/encryption.h"
#include <dpp/dpp.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdlib> 
#include <windows.h>
#include <ctime>
#include <limits>
#include <random>
#include <sddl.h>


Backend backendInstence;

std::string getRandomNumber() {
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < 72; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

std::string getAppDataFolderPath() {
    char* appDataPath;
    size_t size;
    _dupenv_s(&appDataPath, &size, "APPDATA");
    std::string path(appDataPath);
    free(appDataPath);
    return path + "\\discordBotManagerData";  
}

std::string folderPath = getAppDataFolderPath(); 

std::string cutString(const std::string& a);

#include "../include/backend.h"
#include <fstream>
#include <filesystem>

std::string getKeyFilePath() {
    return getAppDataFolderPath() + "\\encryption.key";
}

void Backend::getFileInfo() {
    std::string keyPath = getKeyFilePath();
    bool keyLoaded = false;

    if (std::filesystem::exists(keyPath)) {
        std::ifstream keyFile(keyPath);
        if (keyFile.is_open()) {
            std::getline(keyFile, backendInstence.key);
            keyFile.close();

            if (backendInstence.key.length() == 72) {
                std::cout << "--Using existing key from file" << std::endl;
                SetEnvironmentVariable("DISCORD_BOT_KEY", backendInstence.key.c_str());
                keyLoaded = true;
            }
        }
    }

    if (!keyLoaded) {
        const char* envKey = std::getenv("DISCORD_BOT_KEY");
        if (envKey != nullptr && strlen(envKey) == 72) {
            backendInstence.key = std::string(envKey);
            std::cout << "--Using existing environment key" << std::endl;
        }
        else {
            std::string randomNumber = getRandomNumber();
            backendInstence.key = randomNumber;
            SetEnvironmentVariable("DISCORD_BOT_KEY", backendInstence.key.c_str());

            std::ofstream keyFile(keyPath);
            if (keyFile.is_open()) {
                keyFile << backendInstence.key;
                keyFile.close();
                std::cout << "--New key generated and saved" << std::endl;
            }
            else {
                std::cerr << "Warning: Could not save key to file" << std::endl;
            }
        }
    }

    if (!std::filesystem::exists(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }

    std::string loginFilePath = folderPath + "\\logins.txt";
    if (!std::filesystem::exists(loginFilePath)) {
        std::cout << "no earlier logins, creating save file" << std::endl;
        createFile();
    }
    else {
        bool isInput = true;
        while (isInput) {
            int input = 0;
            std::cout << "Choose action:" << std::endl;
            std::cout << "1. Login" << std::endl;
            std::cout << "2. Register" << std::endl;

            if (!(std::cin >> input)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a number." << std::endl;
                continue;
            }

            if (input == 1) {
                isInput = false;
                VerifyLogin();
            }
            else if (input == 2) {
                isInput = false;
                RegisterNewBot();
            }
            else {
                std::cout << "Please enter a correct choice." << std::endl;
            }
        }
    }
}


void Backend::VerifyLogin() {
    Encrypt encryptInstence;
    std::string filePath = folderPath + "\\logins.txt";
    std::vector<std::string> lines;
    std::ifstream loginsReadAgain(filePath);
    if (loginsReadAgain.is_open()) {
        std::string line;
        while (std::getline(loginsReadAgain, line)) {
            if (line.find("numOfLogs=") == std::string::npos) {
                lines.push_back(line);
            }
        }
        loginsReadAgain.close();
    }
    int input = 0;
    bool isLogin = true;
    while (isLogin) {
        std::cout << "please select login bot" << std::endl;
        for (size_t i = 0; i < lines.size(); i++) {
            if (lines[i].find("bot ") != std::string::npos) {
                std::cout << lines[i] << std::endl;
            }
        }
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number." << std::endl;
            continue;
        }
        if (input <= 0 || input > static_cast<int>(lines.size())) {
            std::cout << "Please input a correct bot number." << std::endl;
            continue;
        }
        else {
            isLogin = false;
        }
    }
    std::string searchTerm = "bot " + std::to_string(input);
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i].find(searchTerm) != std::string::npos) {
            backendInstence.LoginedInfo = cutString(lines[i]);
            std::string tokenPlacement = cutString(lines[i + 1]);
            backendInstence.LoginedbotToken = encryptInstence.decrypt(tokenPlacement);
            backendInstence.LoginedGuildId = cutString(lines[i + 2]);
            std::cout << "you have logged in into name: " << backendInstence.LoginedInfo << std::endl;
            actionManager actionInstence;
            actionInstence.MainManager();
        }
    }
}

std::string Backend::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

std::string Backend::cutString(const std::string& a) {
    auto cutPoint = a.find(':');
    if (cutPoint != std::string::npos) {
        return trim(a.substr(cutPoint + 1));
    }
    return trim(a);
}

void Backend::createFile() {
    std::string filePath = folderPath + "\\logins.txt";
    std::cout << "--Attempting to create file at: " << std::filesystem::absolute(filePath) << std::endl;

    std::ofstream logins(filePath);
    if (logins.is_open()) {
        logins << "numOfLogs=0\n";
        std::cout << "--Config for login txt created." << std::endl;
        logins.close();
        SetFilePermissions(filePath);
    }
    else {
        std::cerr << "Unable to create config file" << std::endl;
    }
    Backend::RegisterNewBot();
}

void Backend::RegisterNewBot() {
    Encrypt encryptInstence;
    std::string filePath = folderPath + "\\logins.txt";
    std::string name;
    std::string botToken;
    std::string guildId;
    std::cout << "--register new bot please" << std::endl;
    bool isEmptyName = true;
    bool isBotToken = true;
    bool isGuildId = true;

    while (isEmptyName) {
        std::cout << "name: ";
        std::getline(std::cin, name);
        if (name.empty()) {
            std::cerr << "please enter a name, not an empty string" << std::endl;
        }
        else {
            isEmptyName = false;
        }
    }
    while (isGuildId) {
        std::cout << "guild id: ";
        std::getline(std::cin, guildId);
        if (guildId.empty()) {
            std::cerr << "please enter a guild id, not an empty string" << std::endl;
        }
        else {
            isGuildId = false;
        }
    }
    while (isBotToken) {
        std::cout << "token: ";
        std::getline(std::cin, botToken);
        if (botToken.empty()) {
            std::cerr << "please enter a bot token, not an empty string" << std::endl;
        }
        else {
            isBotToken = false;
        }
    }

    int numOfLogs = 0;
    std::ifstream loginsRead(filePath);
    if (loginsRead.is_open()) {
        std::string line;
        while (std::getline(loginsRead, line)) {
            if (line.find("numOfLogs=") != std::string::npos) {
                numOfLogs = std::stoi(line.substr(line.find('=') + 1));
                std::cout << "--incremented logins num" << std::endl;
                break;
            }
        }
        loginsRead.close();
    }
    else {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }
    numOfLogs++;

    std::ifstream loginsReadAgain(filePath);
    std::vector<std::string> existingLines;
    if (loginsReadAgain.is_open()) {
        std::string line;
        while (std::getline(loginsReadAgain, line)) {
            if (line.find("numOfLogs=") == std::string::npos && !line.empty()) {  
                existingLines.push_back(line);
            }
        }
        loginsReadAgain.close();
    }

    std::ofstream loginsWrite(filePath);
    if (loginsWrite.is_open()) {
        loginsWrite << "numOfLogs=" << numOfLogs << std::endl;

        for (const auto& existingLine : existingLines) {
            loginsWrite << existingLine << std::endl;
        }

        loginsWrite << "bot " << numOfLogs << ": " << name << std::endl;
        loginsWrite << "botToken " << numOfLogs << ": " << encryptInstence.encrypt(botToken) << std::endl;
        loginsWrite << "guildId " << numOfLogs << ": " << guildId << std::endl;

        std::cout << "Login saved. Total number of logs: " << numOfLogs << std::endl;
        loginsWrite.close();
    }
    else {
        std::cerr << "Unable to edit file." << std::endl;
    }

    VerifyLogin();
}

void Backend::SetFilePermissions(const std::string& filePath) {
    std::string sddlString = "D:P(A;;FA;;;WD)"; 

    PSECURITY_DESCRIPTOR pSD = NULL;
    if (ConvertStringSecurityDescriptorToSecurityDescriptorA(sddlString.c_str(), SDDL_REVISION_1, &pSD, NULL)) {
        if (SetFileSecurityA(filePath.c_str(), DACL_SECURITY_INFORMATION, pSD)) {
            std::cout << "Permissions set successfully for " << filePath << std::endl;
        }
        else {
            std::cerr << "Failed to set file permissions. Error: " << GetLastError() << std::endl;
        }
        LocalFree(pSD);
    }
    else {
        std::cerr << "Failed to create security descriptor. Error: " << GetLastError() << std::endl;
    }
}