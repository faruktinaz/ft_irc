#include "../Server/Server.hpp"


// kick Pragma Go coding in Pascal!
// kick #a museker
void    Server::Kick(int index, int id)
{
	if (commands.size() != 3)
	{
		std::cout << "You should use like this: KICK #channelName nickName" << std::endl;
		clients[id].print("You should use like this: KICK #channelName nickName\n");
		return;
	}

	int	channel_index = getChannelIndex(commands[1]);
	int	client_index = getClientIndex(commands[2]);
    std::string message = "";

    if (client_index == -1 || channel_index == -1)
		clients[id].print("KICK: There is no one or channel for this name.\n");
    else
	{
		for (size_t i = 3; i < this->commands.size(); i++)
    	{
        	message += commands[i];
        	message += " ";
    	}
		std::vector<Client> c_clients = channels[channel_index].getClients();
		for (size_t i = 0; i < c_clients.size(); i++)
			c_clients[i].print("KICK " + channels[channel_index].getChannelName() + " " + clients[client_index].getNickName() + " " +  message + "\r\n");
		c_clients.erase(c_clients.begin() + client_index);
		channels[channel_index].setClients(c_clients);
	}
		
}
