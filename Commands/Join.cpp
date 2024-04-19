#include "../Server/Server.hpp"


void    Server::Join(int index, int id)
{
    int is_exist = 0;

	for (int i = 0; i < channels.size(); i++)
	{
		if (channels[i].getChannelName() == commands[index + 1])
		{
            for (int j = 0; j < channels[i].getClients().size(); ++j)
            {
                if (channels[i].getClients()[j].getUserName() ==  clients[id].getUserName())
                {
                    std::cout << "You are already in this channel" << std::endl;
                    return;
                }
            }
		}
	}

    for (size_t i = 0; i < channels.size(); i++)
        if (commands[index + 1] == channels[i].getChannelName())
            is_exist = 1;
    if (is_exist == 0)
    {
        Channel channel(commands[index + 1]);

        channel.addClient(clients[index]);
        channels.push_back(channel);
    }
    clients[id].print(":" + clients[id].getUserName() + "!" + clients[id].getUserName() + "@" + clients[id].getIp() + " JOIN " + commands[index + 1] + "\r\n");
}
