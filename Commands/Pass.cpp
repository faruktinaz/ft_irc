#include "../Server/Server.hpp"

void Server::Pass(int index, int id)
{
	if (commands[index + 1].empty() == 0 && strcmp(commands[index + 1].c_str(), pass.c_str()) != 0)
	{
		clients[id].print(":localhost 464 " + clients[id].getNickName() + "PASS : Password incorrect\r\n");
		return;	
	}
    if (commands[index + 1].empty() == 0)
        clients[id].setPass(commands[index + 1]);
    else
		std::cout << "The format is 'PASS pass'" << std::endl;
}