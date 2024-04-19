#include "../Server/Server.hpp"

void Server::Pass(int index, int id)
{
    if (commands[index + 1].empty() == 0)
        clients[id].setPass(commands[index + 1]);
    else
		std::cout << "The format is 'PASS pass'" << std::endl;
}