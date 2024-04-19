#include "../Server/Server.hpp"

void Server::Nick(int index, int id)
{
    if (commands[index + 1].empty() == 0)
        clients[id].setNickName(commands[index + 1]);
    else
		std::cout << "The format is 'NICK nickname'" << std::endl;
}