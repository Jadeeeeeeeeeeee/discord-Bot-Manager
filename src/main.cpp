#include "../include/backend.h"
#include "../include/customCommands.h"
#include <iostream>
#include <fstream>
#include <string>
#include <dpp/dpp.h>

int main() {
    //Backend BackendInstence;
    Customs CustomsInstence;
    std::cout << "welcome to my discord bot panel" << std::endl;
    std::cout << "the program should now check for earlier logins" << std::endl;
    system("pause");

    backendInstence.getFileInfo();
};
