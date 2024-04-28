#include "../Server/Server.hpp"

void    Server::Part(int index, int id)
{
    int is_exist = 0;
    if (commands[index + 1][0] != '#')
		clients[id].print("PART: There is no # in the first character.\n");

    std::string message = "";
	size_t i;
    for (i = 2; i < this->commands.size(); i++)
    {
        message += commands[i];
        message += " ";
    }

    for (int j = 0; j < channels.size(); j++)
    {
        if (commands[index + 1] == channels[j].getChannelName() && isInChannel(channels[j].getClients(), clients[id].getNickName()) != -1)
        {
            is_exist = 1;
            std::vector<Client> c_clients = channels[j].getClients();   
            for (size_t i = 0; i < c_clients.size(); i++)
                c_clients[i].print(":" + clients[id].getNickName() + "!" + clients[id].getUserName() + '@' + clients[id].getIp() + " PART " + commands[index + 1] + " " + message + "\r\n");
            c_clients.erase(c_clients.begin() + id);
            channels[j].setClients(c_clients);     
        }
    }
    if (is_exist == 0)
        clients[id].print("PART: You may not in channel or not found.\n");
}