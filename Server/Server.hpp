#pragma once

#include "../Channel/Channel.hpp"
#include "../Client/Client.hpp"
#include <vector>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET_ERROR -1

class Server
{
    private:
	    struct sockaddr_in			server_address;

        std::vector<Channel>		channels;
        std::vector<Client>			clients;
        std::vector<std::string>	commands;
		std::vector<int>			connected_clients;

		int							sockfd;
		int							acceptFd;
		int 						port;
		std::string					serverIp;
		std::string					pass;
		fd_set 						readfds;

    public:
		Server(int port, std::string arg_pass);
		std::vector<Channel> 		getChannels();
		void						initilizeServer();
		std::vector<Client> 		getClients();
		int 						perr(std::string err, int sockfd);
		std::vector<std::string>	getCommands();
		int							checkCommands(Server &server, std::string buffer);
		int							getAcceptFd();
		int							getServerFd();
		int							getPort();
		~Server();
};
