#include "../Server/Server.hpp"

void    Server::Part2(int index, int id, Channel& channel, int flag)
{
	std::vector<Client> c_clients = channel.getClients();   
	for (size_t i = 0; i < c_clients.size(); i++)
		c_clients[i].print(":" + clients[id].getNickName() + "!" + clients[id].getUserName() + '@' + clients[id].getIp() + " PART " + channel.getChannelName() + "\r\n");

	c_clients.erase(c_clients.begin()+isInChannel(channel.getClients(), clients[id].getNickName()));
	channel.setClients(c_clients);
}

void Server::Quit(int index, int id)
{
	std::cout << "quit sinyali geldi" << std::endl;
	std::cout << "quit atan kisi user = " << clients[id].getUserName() << std::endl;
	for (size_t i = 0; i < channels.size(); i++)
		if (isInChannel(channels[i].getClients(), clients[id].getNickName()) != -1)
			Part2(index, id, channels[i], 0);

	close(clients[id].getSocket());
	clients.erase(clients.begin()+id);
	close(connected_clients[id]);
	connected_clients.erase(connected_clients.begin()+id);

	for (int i = 0; i < clients.size(); i++)
		std::cout << clients[i].getUserName() << std::endl;
}