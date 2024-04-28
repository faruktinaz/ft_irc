#include "../Server/Server.hpp"

// bir client disconnect attiginda bilgilerinin temizlenmesi lazim
void Server::User(int index, int id)
{
	if (commands[index + 1].empty() == 0 && commands[index + 3].empty() == 0)
	{
        clients[id].setUserName(commands[index + 1]);
        clients[id].setIp(commands[index + 3]);
	}
    else
		std::cout << "The format is 'USER username 0 realname'" << std::endl;
}