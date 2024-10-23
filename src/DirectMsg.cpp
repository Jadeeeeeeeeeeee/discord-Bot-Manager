#include "../include/DirectMsg.h"
#include "../include/backend.h"
#include <iostream>
#include <string>
#include <dpp/dpp.h>
#include <dpp/guild.h>
#include <dpp/snowflake.h>



void Direct::SendDirect() {
    std::string token = backendInstence.LoginedbotToken;
    if (token.empty()) {
        std::cerr << "Error: No token found. Please ensure you are logged in." << std::endl;
        return;
    }
    std::string channelId;
    std::string messageContents;


    system("Cls");
    std::cout << "Please input channel ID: ";
    std::cin >> channelId;
    std::cin.ignore();
    std::cout << "Please input message contents: ";
    std::getline(std::cin, messageContents);
    std::cout << "Token: " << backendInstence.LoginedbotToken << std::endl;
    std::cout << "Channel ID: " << channelId << std::endl; 

    dpp::cluster bot(token);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot, messageContents, channelId](const dpp::ready_t& event) {
        std::cout << "Bot is ready, sending message..." << std::endl;
        bot.message_create(dpp::message(channelId, messageContents));
        });

    bot.start(dpp::st_return);  
}
