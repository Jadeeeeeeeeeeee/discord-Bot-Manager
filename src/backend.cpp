#include "../include/backend.h"
#include "../include/ActionManager.h"
#include <dpp/dpp.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <windows.h>

Backend backendInstence;

std::string getAppDataFolderPath() {
    char* appDataPath;
    size_t size;
    _dupenv_s(&appDataPath, &size, "APPDATA");
    std::string path(appDataPath);
    free(appDataPath);
    return path + "\\discordBotManagerData";  // Change this as needed
}

std::string folderPath = getAppDataFolderPath();  // Update folder path

std::string cutString(const std::string& a);

void Backend::getFileInfo() {
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
                Backend::VerifyLogin();
            }
            else if (input == 2) {
                isInput = false;
                Backend::RegisterNewBot();
            }
            else {
                std::cout << "Please enter a correct choice." << std::endl;
            }
        }
    }
}

void Backend::VerifyLogin() {
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
                if (i + 1 < lines.size()) {
                    std::cout << lines[i + 1] << std::endl;
                }
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
            backendInstence.LoginedbotToken = cutString(lines[i + 2]);
            backendInstence.LoginedGuildId = cutString(lines[i + 4]);
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
    }
    else {
        std::cerr << "Unable to create config file" << std::endl;
    }
    Backend::RegisterNewBot();
}

void Backend::RegisterNewBot() {
    std::string filePath = folderPath + "\\logins.txt";
    std::string name;
    std::string botToken;
    std::string guildId;
    std::cout << "--register new bot please" << std::endl;
    std::cout << "--enter a name for the bot and its token by order" << std::endl;
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
            if (line.find("numOfLogs=") == std::string::npos) {
                existingLines.push_back(line);
            }
        }
        loginsReadAgain.close();
    }
    std::ofstream loginsWrite(filePath);
    if (loginsWrite.is_open()) {
        loginsWrite << "numOfLogs=" << numOfLogs << std::endl << "\n";
        for (const auto& existingLine : existingLines) {
            loginsWrite << existingLine << std::endl;
        }
        loginsWrite << "bot " << numOfLogs << ": " << name << std::endl << "\n";
        loginsWrite << "botToken " << numOfLogs << ":" << botToken << std::endl << "\n";
        loginsWrite << "guildId " << numOfLogs << ":" << guildId << std::endl << "\n";
        std::cout << "Login saved. Total number of logs: " << numOfLogs << std::endl;
        loginsWrite.close();
    }
    else {
        std::cerr << "Unable to edit file." << std::endl;
    }
}
