#include <iostream>
#include "Client.h"
#include "Server.h"

int main() {
    std::cout << "Select mode:" << std::endl;
    std::cout << "1) Client" << std::endl;
    std::cout << "2) Server" << std::endl;
    std::cout << "Please, select mode" << std::endl;

    auto k = std::cin.get();

    switch (k)
    {
        case '1':
        {
            Client client;
            client.run();
            break;
        }
        case '2':
        {
            Server server;
            server.run();
            break;
        }
        default:
        {
            std::cout << "Извините, такого варианта не существует. Выходим..." << std::endl;
            break;
        }
    }
    return 0;
}