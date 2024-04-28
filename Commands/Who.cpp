#include "../Server/Server.hpp"

int Server::getChannelIndex(std::string channel)
{
    for (size_t i = 0; i < this->channels.size(); i++)
    {
        if (this->channels[i].getChannelName() == channel)
            return (int)i;
	}
    return -1;
}

void	Server::Who(int index, int id)
{
	std::cout << commands[index + 1] << std::endl;
	if(this->commands[1][0] == '#')
	{
		for (size_t j = 0; j < this->channels[getChannelIndex(this->commands[1])].getClients().size(); j++)
        {
            clients[id].print("Nick: " + this->clients[j].getNickName() + "\n");
        }
        clients[id].print(":" + clients[id].getIp() + " 315 " +  this->commands[1] + ": End of WHO list\r\n");
        return ;
	}
}

void Server::List(int index, int id)
{
    std::string list;
    for(size_t i = 0; i < this->channels.size(); i++)
    {
        list += this->channels[i].getChannelName() + " ";
    }
    clients[id].print(":" + clients[id].getIp() + " " + list + "\r\n");
}