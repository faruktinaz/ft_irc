#include "../Server/Server.hpp"

int	Server::isInChannel(std::vector<Client> c_clients, std::string name)
{
	for (size_t i = 0; i < c_clients.size(); i++)
		if (strcmp(c_clients[i].getNickName().c_str(),name.c_str()) == 0)
			return i;
	return -1;
}

void    Server::Privmsg(int index, int id)
{
    std::string message = "";
	size_t i;
	static int flag = 0;
	if (commands.size() < 3)
	{
		std::cout << "You should use like this: PRIVMSG userName message";
		clients[id].print("You should use like this: PRIVMSG userName message\n");
	}

    for (i = 2; i < this->commands.size(); i++)
    {
        message += commands[i];
        message += " ";
    }

    for (i = 0; i < clients.size(); i++)
    {
        if (channels.size() > i && strcmp(commands[1].c_str(), channels[i].getChannelName().c_str()) == 0 && isInChannel(channels[i].getClients(), clients[id].getNickName()) != -1)
        {
            std::vector<Client> tmp_client = channels[i].getClients();
            for (size_t j = 0; j < tmp_client.size(); j++)
			{
                if (tmp_client[j].getNickName() != clients[id].getNickName())
                    tmp_client[j].print(":" + clients[id].getNickName() + "!" + clients[id].getUserName() + '@' + clients[id].getIp() + " PRIVMSG " + channels[i].getChannelName() + " :"+ message + "\r\n");
			}
			return;
        }
        else if (strcmp(clients[i].getNickName().c_str(),commands[1].c_str()) == 0)
		{
			clients[i].print(":" + clients[id].getNickName() + "!" + clients[id].getUserName() + "@localhost"+ " PRIVMSG " + clients[i].getNickName() + " :"+ message + "\r\n");
			return;
		}
    }

}