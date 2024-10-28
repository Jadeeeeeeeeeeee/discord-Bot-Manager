#include "../include/ActionManager.h"
#include "../include/backend.h"
#include "../include/customCommands.h"
#include "../include/DirectMsg.h"
#include <dpp/dpp.h>
#include <thread>  
#include <iostream>


void actionManager::MainManager() {
	system("cls");
	Direct DirectInstence;
	Customs CustomsInstence;
	int input = 0;
	bool action = true;
	std::cout << "Welcome to Jades discord bot manager" << std::endl;
	while (action == true) {
		std::cout << " " << std::endl;
		std::cout << "please select an action" << std::endl;
		std::cout << "1. direct message, send a message through the bot" << std::endl;
		std::cout << "2. manage Command's" << std::endl;
		std::cout << "3. local host" << std::endl;
		std::cout << "4. exit" << std::endl;;
		std::cin >> input;
		if (std::cin.fail()){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "--Invalid input, please enter a valid number." << std::endl;
		}
		if (input == 1) {
			DirectInstence.SendDirect();
		}
		else if (input == 2) {
			CustomsInstence.Main();
		}
		else if (input == 3) {
			system("cls");
			CustomsInstence.ReadFile();
			system("cls");
			std::thread backgroundThread(&Customs::DoCommand, &CustomsInstence);
			backgroundThread.detach();
		}
		else if (input == 4) {
			std::cout << "thank you for using my program" << std::endl;
			action = false;
			exit(0);
		}
		else {
			std::cout << "--input incorrect" << std::endl;
			continue;
		}
	}
}