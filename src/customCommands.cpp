#include "../include/customCommands.h"
#include "../include/backend.h"
#include "../include/ActionManager.h"
#include "dpp/dpp.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>
#include <Windows.h>
Customs customInstence;

const std::string folderPath = (std::filesystem::path(getenv("APPDATA")) / "discordBotManagerData").string();
const std::string filePath = (std::filesystem::path(folderPath) / "Commands.txt").string();


std::vector<std::string> commandCalls;
std::vector<std::string> commandActions;
std::vector<std::string> commandTypes;

void Customs::Main() {
    system("cls");
    actionManager actionInstence;

    if (!std::filesystem::exists(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }

    if (!std::filesystem::exists(filePath)) {
        std::cout << "--no earlier commands creating files" << std::endl;
        customInstence.FileCreate();
    }

    std::cout << "hello what would you like to do?" << std::endl;
    std::cout << "1. add new command" << std::endl;
    std::cout << "2. Delete Command" << std::endl;
    std::cout << "3. go back" << std::endl;
    customInstence.ReadFile();
    int input = 0;
    bool isInput = true;
    while (isInput == true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number." << std::endl;
            continue;
        }
        if (input == 1) {
            isInput = false;
            customInstence.AddCommand();
        }
        else if (input == 2) {
            isInput = false;
            customInstence.deleteCommand();
        }
        else if (input == 3) {
            isInput = false;
            actionInstence.MainManager();
        }
        else {
            std::cout << "please enter a correct number" << std::endl;
        }
    }
}
void Customs::deleteCommand() {
    Customs customsInstence;
    customInstence.ReadFile();

    if (commandCalls.empty()) {
        std::cout << "No commands available to delete." << std::endl;
        return;
    }

    std::cout << "Which command do you want to delete (enter the number shown after the command name):" << std::endl;
    for (size_t i = 0; i < commandCalls.size(); i++) {
        std::cout << "CommandName " << i << ": " << commandCalls[i] << std::endl;
        std::cout << "CommandPurpose " << i << ": " << commandTypes[i] << std::endl;
        std::cout << "CommandAction " << i << ": " << commandActions[i] << std::endl;
    }

    size_t input = 0;
    bool IsInput = true;
    while (IsInput) {
        std::cin >> input;
        if (std::cin.fail() || input >= commandCalls.size()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a valid number." << std::endl;
        }
        else {
            IsInput = false;
        }
    }

    commandCalls.erase(commandCalls.begin() + input);
    commandTypes.erase(commandTypes.begin() + input);
    commandActions.erase(commandActions.begin() + input);

    std::ofstream CustomsWrite(filePath);
    if (CustomsWrite.is_open()) {
        CustomsWrite << "numOfCommands=" << commandCalls.size() << std::endl;

        for (size_t i = 0; i < commandCalls.size(); i++) {
            CustomsWrite << "CommandName " << i << ": " << commandCalls[i] << std::endl;
            CustomsWrite << "CommandPurpose " << i << ": " << commandTypes[i] << std::endl;
            CustomsWrite << "CommandCall " << i << ": " << commandCalls[i] << std::endl;
            CustomsWrite << "commandFunction " << i << ": " << commandActions[i] << std::endl;
        }

        std::cout << "Command deleted successfully." << std::endl;
        CustomsWrite.close();
    }
    else {
        std::cerr << "Unable to write to command file." << std::endl;
    }
}


void Customs::FileCreate() {
    std::cout << "--Attempting to create file at: " << std::filesystem::absolute(filePath) << std::endl;
    std::ofstream Customs(filePath);
    if (Customs.is_open()) {
        Customs << "numOfCommands=0\n";
        std::cout << "--Config for login txt created." << std::endl;
        Customs.close();
    }
    else {
        std::cerr << "Unable to create command file" << std::endl;
    }
}

void Customs::AddCommand() {
    system("cls");
    std::string CommandName;
    std::string CommandPurpose;
    std::string CommandCall;
    std::string commandFunction;
    int numOfCommands = 0;
    bool isEmptyName = true;
    bool isEmptyPurpse = true;
    bool isEmptyCall = true;
    bool isEmptyFunction = true;
     while(isEmptyName == true) {
        std::cout << "Enter what will your command name be:" << std::endl;
        std::getline(std::cin, CommandName);
        if (CommandName.empty() == true) {
            std::cout << "dont empty a empty string" << std::endl;
        }
        else {
            isEmptyName = false;
        }
    }
     while(isEmptyPurpse == true) {
        std::cout << "Enter what will your command purpose be (select from gif, typeBack) with this exact spelling:" << std::endl;
        std::getline(std::cin, CommandPurpose);
        if (CommandPurpose.empty() == true) {
            std::cout << "dont empty a empty string" << std::endl;
        }
        else if (CommandPurpose != "gif" && CommandPurpose != "typeBack") {
            std::cout << "please enter a correct spelling" << std::endl;
        }
        else {
            isEmptyPurpse = false;
        }
    }
     while(isEmptyCall == true) {
        std::cout << "Enter what will your command call be (for example if you input Bob the command will be called with !Bob DO NOT TYPE ! DO NOT TYPE !):" << std::endl;
        std::getline(std::cin, CommandCall);
        if (CommandCall.empty() == true) {
            std::cout << "dont empty a empty string" << std::endl;
        }
        else {
            isEmptyCall = false;
        }
    }
     if (CommandPurpose == "gif") {
         while (isEmptyFunction == true) {
             std::cout << "enter the gif link" << std::endl;
             std::getline(std::cin, commandFunction);
             if (commandFunction.empty() == true) {
                 std::cout << "dont empty a empty string" << std::endl;
             }
             else {
                 isEmptyFunction = false;
             }
         }
    }else if (CommandPurpose == "typeBack") {
        while (isEmptyFunction == true) {
            std::cout << "enter the text the bot will type back" << std::endl;
            std::getline(std::cin, commandFunction);
            if (commandFunction.empty() == true) {
                std::cout << "dont empty a empty string" << std::endl;
            }
            else {
                isEmptyFunction = false;
            }
        }
    }

    std::cout << "--Attempting to edit file at: " << std::filesystem::absolute(filePath) << std::endl;


    std::vector<std::string> existingLines;
    std::ifstream CustomsRead(filePath);
    if (CustomsRead.is_open()) {
        std::string line;
        while (std::getline(CustomsRead, line)) {
            if (line.find("numOfCommands=") == std::string::npos) {
                existingLines.push_back(line);
            }
            else {
                std::istringstream iss(line);
                std::string temp;
                if (std::getline(iss, temp, '=')) {
                    iss >> numOfCommands; 
                }
            }
        }
        CustomsRead.close();
    }
    else {
        std::cerr << "Unable to read command file" << std::endl;
        return; 
    }

    std::ofstream CustomsWrite(filePath); 
    if (CustomsWrite.is_open()) {
        CustomsWrite << "numOfCommands=" << (numOfCommands + 1) << std::endl;
        for (const auto& line : existingLines) {
            CustomsWrite << line << std::endl;
        }
        CustomsWrite << "CommandName " << numOfCommands << ": " << CommandName << std::endl;
        CustomsWrite << "CommandPurpose " << numOfCommands << ":" << CommandPurpose << std::endl;
        CustomsWrite << "CommandCall " << numOfCommands << ":" << CommandCall << std::endl;
        CustomsWrite << "commandFunction " << numOfCommands << ":" << commandFunction << std::endl;
        std::cout << "Command saved. Total number of commands: " << (numOfCommands + 1) << std::endl;
        CustomsWrite.close();
    }
    else {
        std::cerr << "Unable to create command file" << std::endl;
    }
}


void Customs::ReadFile() {
    commandCalls = {};
    commandActions = {};
    commandTypes = {};
    std::ifstream CustomsRead(filePath);
    if (CustomsRead.is_open()) {
        std::string line;
        while (std::getline(CustomsRead, line)) {
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);

            if (line.find("CommandCall") != std::string::npos) {
                std::size_t colonPos = line.find(':');
                if (colonPos != std::string::npos) {
                    std::string commandName = line.substr(colonPos + 1);
                    commandCalls.push_back(commandName);  
                }
            }
            else if (line.find("commandFunction") != std::string::npos) {
                std::size_t colonPos = line.find(':');
                if (colonPos != std::string::npos) {
                    std::string commandAction = line.substr(colonPos + 1);
                    commandActions.push_back(commandAction); 
                }
            }
            else if (line.find("CommandPurpose") != std::string::npos) {
                std::size_t colonPos = line.find(':');
                if (colonPos != std::string::npos) {
                    std::string commandPurpose = line.substr(colonPos + 1);
                    commandTypes.push_back(commandPurpose); 
                }
            }
        }
        CustomsRead.close();
    }
    else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }

}


void Customs::DoCommand() {
    system("cls");
    std::string token = backendInstence.LoginedbotToken;
    if (token.empty()) {
        std::cerr << "Error: No token found. Please ensure you are logged in." << std::endl;
        return;
    }

    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.author.id == bot.me.id) return; 

        std::string content = event.msg.content;
        if (content.starts_with("!")) { 
            std::string command = content.substr(1); 
            if (command == "help") {
                std::ostringstream helpMessage;
                helpMessage << "Available commands:\n";
                for (const auto& cmd : commandCalls) {
                    helpMessage << "!" << cmd << "\n"; 
                }
                bot.message_create(dpp::message(event.msg.channel_id, helpMessage.str()));
            }else{
                auto it = std::find(commandCalls.begin(), commandCalls.end(), command);
                if (it != commandCalls.end()) {
                    std::size_t index = std::distance(commandCalls.begin(), it);
                    bot.message_create(dpp::message(event.msg.channel_id, commandActions[index]));
                }
                else {
                    bot.message_create(dpp::message(event.msg.channel_id, "Command not recognized."));
                }
            }
        }
        });


    bot.start(dpp::st_wait);
}